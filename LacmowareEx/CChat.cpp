#include "pch.h"
#include "CChat.h"
#include "CSendHook.h"
#include "CRecvHook.h"
#include "CPlayerListElement.h"

#define CHAT_SIG "mclilwagner"
#define CHAT_XOR_KEY "nazi_huesos_zelenskij_swinger"

std::deque<CChat::Message> CChat::m_lastMessages{};
std::mutex CChat::m_mutex{};
int CChat::m_maxMessages = 13;

void xorString(char *data, const char *key)
{
	for (size_t i = 0; i < strlen(data); ++i)
	{
		data[i] ^= i ^ key[i % strlen(key)];
	}
}

CChat::CChat()
	: CFeature("Chat", CHotkey(), Tab::Chat)
{
	for (int i = 0; i < m_maxMessages; ++i)
	{
		m_lastMessages.push_back(Message{ .pid = 0 });
	}

	CRecvHook::addPacketModifier(Network::M_VOICE,
		[](char *buf, int len)
		{
			int datalen = len - 3;
			char *data = new char[datalen];
			memcpy(data, buf + 2, datalen);

			if (!memcmp(data, CHAT_SIG, strlen(CHAT_SIG)) && data[datalen - 1] == '\0')
			{
				char *text = data + strlen(CHAT_SIG);
				xorString(text, CHAT_XOR_KEY);
				Message message{ .pid = buf[1], .text = text };

				CPlayerListElement::foreach(
					[&](CPlayerListElement *el)
					{
						CPlayer *player = *el->m_COplayer;
						if (player->m_id == message.pid)
						{
							message.pname = player->getName();
						}
					});

				m_mutex.lock();
				m_lastMessages.push_back(message);
				if (m_lastMessages.size() > m_maxMessages)
				{
					m_lastMessages.pop_front();
				}
				m_mutex.unlock();
			}

			delete[] data;
		});
}

void CChat::fnDraw(unsigned int &uElementId)
{
	m_mutex.lock();
	for (const auto &message : m_lastMessages)
	{
		if (message.pid)
		{
			ImGui::Text("%s", std::format("{} > {}", message.pid == CSendHook::m_lastPlayerId ?
				"You" : std::format("({}) {}", message.pid, message.pname), message.text).c_str());
		}
		else
		{
			ImGui::Text("");
		}
	}
	m_mutex.unlock();

	ImGui::Separator();

	static char s_text[1024]{};
	bool enterPressed = ImGui::InputText(std::format("##{}", uElementId++).c_str(), s_text, sizeof s_text, ImGuiInputTextFlags_EnterReturnsTrue);
	
	ImGui::SameLine();
	if ((ImGui::Button(std::format("Send##{}", uElementId++).c_str()) || enterPressed) &&
		s_text[0] != '\0')
	{
		int buflen = 2 + strlen(CHAT_SIG) + strlen(s_text) + 1;
		char *buf = new char[buflen] { (char)Network::M_VOICE, CSendHook::m_lastPlayerId };
		memcpy(buf + 2, CHAT_SIG, strlen(CHAT_SIG));
		xorString(s_text, CHAT_XOR_KEY);
		strcpy(buf + 2 + strlen(CHAT_SIG), s_text);

		CSendHook::m_oSendto(CSendHook::m_lastSocket, buf, buflen, 0, CSendHook::m_lastTo, CSendHook::m_lastTolen);
		delete[] buf;

		s_text[0] = '\0';
	}
}

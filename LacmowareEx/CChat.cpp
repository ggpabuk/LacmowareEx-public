#include "pch.h"
#include "CChat.h"
#include "CSendHook.h"
#include "CRecvHook.h"

#define CHAT_SIG "mclilwagner"

std::deque<CChat::Message> CChat::m_lastMessages{};
std::mutex CChat::m_mutex{};
int CChat::m_maxMessages = 10;

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
				Message message{ .pid = buf[1], .text = data + strlen(CHAT_SIG) };
				
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
			ImGui::Text(std::format("{} > {}", message.pid == CSendHook::m_lastPlayerId ?
				"You" : std::to_string(message.pid), message.text).c_str());
		}
		else
		{
			ImGui::Text("");
		}
	}
	m_mutex.unlock();

	ImGui::Separator();

	static char s_text[1024]{};
	ImGui::InputText(std::format("##{}", uElementId++).c_str(), s_text, sizeof s_text);

	ImGui::SameLine();
	if (ImGui::Button(std::format("Send##{}", uElementId++).c_str()))
	{
		int buflen = 2 + strlen(CHAT_SIG) + strlen(s_text) + 1;
		char *buf = new char[buflen] { (char)Network::M_VOICE, CSendHook::m_lastPlayerId };
		memcpy(buf + 2, CHAT_SIG, strlen(CHAT_SIG));
		strcpy(buf + 2 + strlen(CHAT_SIG), s_text);

		CSendHook::m_oSendto(CSendHook::m_lastSocket, buf, buflen, 0, CSendHook::m_lastTo, CSendHook::m_lastTolen);
		delete[] buf;
	}
}

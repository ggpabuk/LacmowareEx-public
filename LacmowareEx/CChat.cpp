#include "pch.h"
#include "CChat.h"
#include "CSendHook.h"
#include "CRecvHook.h"
#include "CPlayerListElement.h"

#define CHAT_SIG "mclilwagner"
#define CHAT_XOR_KEY "nazi_huesos_zelenskij_swinger"

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}

void CChat::sendMessage(const char *text)
{
	int buflen = 2 + strlen(CHAT_SIG) + strlen(text) + 1;
	char *buf = new char[buflen] { (char)Network::M_VOICE, CSendHook::m_lastPlayerId };
	memcpy(buf + 2, CHAT_SIG, strlen(CHAT_SIG));
	char *buftext = buf + 2 + strlen(CHAT_SIG);
	strcpy(buftext, text);
	memory::xorString(buftext, CHAT_XOR_KEY);
	CSendHook::m_oSendto(CSendHook::m_lastSocket, buf, buflen, 0, CSendHook::m_lastTo, CSendHook::m_lastTolen);
	delete[] buf;
}

CChat::CChat()
	: CFeature("Chat", CHotkey(), Tab::Chat)
{
	m_maxMessages = 13;
	m_ignorePing = true;

	for (int i = 0; i < m_maxMessages; ++i)
	{
		m_lastMessages.push_back(Message{ .pid = 0 });
	}

	CRecvHook::addPacketModifier(Network::M_VOICE,
		[this](char *buf, int len)
		{
			int datalen = len - 3;
			char *data = new char[datalen];
			memcpy(data, buf + 2, datalen);

			if (!memcmp(data, CHAT_SIG, strlen(CHAT_SIG)) && data[datalen - 1] == '\0')
			{
				char *text = data + strlen(CHAT_SIG);
				memory::xorString(text, CHAT_XOR_KEY);
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

				if (message.text.starts_with('/'))
				{
					std::vector<std::string> args = split(message.text.substr(1), ' ');
					if (!args[0].compare("ping") && message.pid != CSendHook::m_lastPlayerId && !m_ignorePing)
					{
						sendMessage(std::format("/pong {}", message.pid).c_str());
					}
					else if (!args[0].compare("pong") && args.size() >= 2 && stoi(args[1]) == CSendHook::m_lastPlayerId)
					{
						printf("%i ponged!\n", message.pid);
					}

					delete[] data;
					return;
				}
		
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
		m_ignorePing = false;
		sendMessage(s_text);
		sendMessage("/ping");
		s_text[0] = '\0';
	}

	ImGui::Checkbox(std::format("Ignore ping##{}", uElementId++).c_str(), &m_ignorePing);
}

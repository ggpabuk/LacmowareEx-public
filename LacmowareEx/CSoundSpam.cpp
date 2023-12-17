#include "pch.h"
#include "CSoundSpam.h"
#include "CSendHook.h"
#include "CRecvHook.h"

CSoundSpam::CSoundSpam()
	: CFeature("Sound spam", CHotkey(), Tab::Fun)
{
	CRecvHook::addPacketModifier(Network::M_VOICE,
		[this](char *buf, int len)
		{
			std::vector<char> data{ buf + 2, buf + len - 1 };
			if (!memcmp(data.data(), "mclilwagner", strlen("mclilwagner")))
			{
				printf("%s\n", data.data() + strlen("mclilwagner"));
			}
		});
}

void CSoundSpam::fnDraw(unsigned int &uElementId)
{
	CFeature::fnDraw(uElementId);

	if (ImGui::Button(std::format("test##{}", uElementId++).c_str()))
	{
		char buf[30 + 2] = { (char)Network::M_VOICE, CSendHook::m_lastPlayerId };
		strcpy(buf + 2, "mclilwagner" "hello from ggpabuk");
		CSendHook::m_oSendto(CSendHook::m_lastSocket, buf, sizeof buf, 0, CSendHook::m_lastTo, CSendHook::m_lastTolen);
	}
}

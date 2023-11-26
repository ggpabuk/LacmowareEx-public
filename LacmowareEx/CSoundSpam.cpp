#include "pch.h"
#include "CSoundSpam.h"
#include "CSendHook.h"

CSoundSpam::CSoundSpam()
	: CFeature("Sound spam", CHotkey(), Tab::Fun)
{
}

void CSoundSpam::fnDraw(unsigned int &uElementId)
{
	CFeature::fnDraw(uElementId);

	if (ImGui::Button(std::format("test##{}", uElementId++).c_str()))
	{

	}
}

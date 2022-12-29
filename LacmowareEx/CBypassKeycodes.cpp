#include "pch.h"
#include "CBypassKeycodes.h"

CBypassKeycodes::CBypassKeycodes() :
    CFeature("Bypass Keycodes", CHotkey(), Tab::Fun)
{
}

void CBypassKeycodes::fnDraw(unsigned int &uElementId)
{
    if (!SDK::g_piMaynardKeycode)
    {
        return;
    }

    ImGui::Text("Maynard key: %i", *SDK::g_piMaynardKeycode);

    int maintenanceKey = (*SDK::g_piMaynardKeycode * 3) % 10000;
    ImGui::Text("Maintenance tunnel key: %i", maintenanceKey);
}

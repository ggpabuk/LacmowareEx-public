#include "pch.h"
#include "CFeature.h"

CFeature::CFeature(
    const char *szName,
    CHotkey COHotkey,
    Tab tab,
    bool bDefaultEnabled
)
{
    m_szName = szName;
    m_COHotkey = COHotkey;
    m_tab = tab;
    m_bIsEnabled = bDefaultEnabled;
}

CFeature::~CFeature()
{

}

void CFeature::fnEnable()
{
    m_bIsEnabled = true;
}

void CFeature::fnDisable()
{
    m_bIsEnabled = false;
}

void CFeature::fnToggle()
{
    m_bIsEnabled ? fnDisable() : fnEnable();
}

void CFeature::fnReload()
{
    if (!m_bIsEnabled) return;
    fnDisable();
    fnEnable();
}

void CFeature::fnDraw(unsigned int &uElementId)
{
    ImGui::Text("%s", m_szName);

    // Manual toggle checkbox
    if (!m_COHotkey.m_bHoldToUse)
    {
        std::string enabledLabel = std::string("Enabled") + "##" +
            std::to_string(uElementId++);

        bool bIsEnabled = m_bIsEnabled;
        ImGui::Checkbox(enabledLabel.c_str(), &bIsEnabled);

        if (bIsEnabled != m_bIsEnabled)
        {
            fnToggle();
        }
    }

    // Change hotkey button
    std::string hotkeyLabel = std::string(g_aKeyNames[m_COHotkey.m_iVKey]) + "##" +
        std::to_string(uElementId++);

    bool bWaitingForKey = ImGui::Button(hotkeyLabel.c_str(), ImVec2(70, 18));
    while (bWaitingForKey)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        for (size_t keyIndex = 0; keyIndex <= LENGTH(g_aKeyNames); ++keyIndex)
        {
            if (~GetAsyncKeyState(keyIndex) & 0x8000) continue;
            
            // 27 = ESC
            m_COHotkey.m_iVKey = keyIndex == 27 ? 0 : keyIndex;
            bWaitingForKey = false;
            break;
        }
    }
}

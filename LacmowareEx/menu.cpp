#include "pch.h"
#include "menu.h"

typedef std::unique_ptr<CFeature> featureUnique_t;

namespace menu
{
    static std::vector<featureUnique_t> g_features{};
    static HWND g_hWnd;

    void fnInit(HWND hWnd)
    {
        g_hWnd = hWnd;
        
        LONG wndStyle = GetWindowLong(g_hWnd, GWL_STYLE);
        wndStyle &= ~WS_MINIMIZEBOX;
        wndStyle &= ~WS_MAXIMIZEBOX;
        wndStyle &= ~WS_SYSMENU;
        SetWindowLong(g_hWnd, GWL_STYLE, wndStyle);

        CHotkey CONoneHotkey(0, false);
        g_features.push_back(std::make_unique<CNoclip>(CHotkey('F', true)));
        g_features.push_back(std::make_unique<CVomit>(CHotkey(NULL, true)));
        //g_features.push_back(std::make_unique<CTeleportNext>(CHotkey('M', false)));
        g_features.push_back(std::make_unique<CNoBlink>(CONoneHotkey));
        g_features.push_back(std::make_unique<CWallhack>(CONoneHotkey));
        g_features.push_back(std::make_unique<CNoFilters>(CONoneHotkey));
        g_features.push_back(std::make_unique<CWireframe>(CONoneHotkey));
        g_features.push_back(std::make_unique<CInfAmmo>(CONoneHotkey));
        g_features.push_back(std::make_unique<CMaxShootSpeed>(CONoneHotkey));
        g_features.push_back(std::make_unique<CNoRecoil>(CONoneHotkey));
        g_features.push_back(std::make_unique<CInfStamina>(CONoneHotkey));
        g_features.push_back(std::make_unique<CSpeedhack>(CONoneHotkey));
        g_features.push_back(std::make_unique<CForceVoice>(CONoneHotkey));
        g_features.push_back(std::make_unique<CBypassKeycodes>(CONoneHotkey));

        std::thread(fnCatchHotkeys).detach();
    }

    void fnDrawMenu()
    {
        static bool s_bMenuActive = true;

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            SetWindowPos(
                g_hWnd,
                HWND_TOPMOST,
                NULL,
                NULL,
                NULL,
                NULL,
                SWP_NOMOVE | SWP_NOSIZE | (s_bMenuActive ? SWP_HIDEWINDOW : SWP_SHOWWINDOW)
            );

            s_bMenuActive ^= 1;
        }

        if (!s_bMenuActive)
        {
            return;
        }

        ImGui::SetNextWindowPos(ImVec2(0, 0), 0);
        ImGui::SetNextWindowSize(ImVec2(iWidth, iHeight));

        ImGui::Begin("LacmowareEx", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        unsigned int uElementId = 0;
        
        // Tabs
        static Tab s_iCurrentTab = Tab::Combat;

        const auto tabsButtonSize = ImVec2(90, 18);
        if (ImGui::Button("Combat", tabsButtonSize))
        {
            s_iCurrentTab = Tab::Combat;
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Visuals", tabsButtonSize))
        {
            s_iCurrentTab = Tab::Visuals;
        }

        ImGui::SameLine();
        if (ImGui::Button("Movement", tabsButtonSize))
        {
            s_iCurrentTab = Tab::Movement;
        }

        ImGui::SameLine();
        if (ImGui::Button("Fun", tabsButtonSize))
        {
            s_iCurrentTab = Tab::Fun;
        }

        for (const auto &feature : g_features)
        {
            if (s_iCurrentTab != feature->m_tab) continue;
            feature->fnDraw(uElementId);
            ImGui::Separator();
        }

        ImGui::End();
    }

    void fnCatchHotkeys()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            for (const auto &feature : g_features)
            {
                const short nKeyState = GetAsyncKeyState(feature->m_COHotkey.m_iVKey);

                if (feature->m_COHotkey.m_bHoldToUse)
                {
                    if (nKeyState & 0x8000)
                    {
                        feature->fnEnable();
                    }
                    else if (feature->m_bIsEnabled)
                    {
                        feature->fnDisable();
                    }

                    continue;
                }

                if (nKeyState & 1)
                {
                    feature->fnToggle();
                }
            }
        }
    }
}

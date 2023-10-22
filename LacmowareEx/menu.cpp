#include "pch.h"
#include "menu.h"
#include "CCameraFix.h"

typedef std::unique_ptr<CFeature> featureUnique_t;

namespace menu
{
    static std::vector<featureUnique_t> g_features{};
    static HWND g_hWnd;
    static ImFont *g_pFont;

    std::mutex hotkeysMutex;

    void fnInit(HWND hWnd)
    {
        ImGui::GetIO().IniFilename = NULL;

        fnSetTheme();

        g_hWnd = hWnd;
        
        LONG wndStyle = GetWindowLong(g_hWnd, GWL_STYLE);
        wndStyle &= ~WS_MINIMIZEBOX;
        wndStyle &= ~WS_MAXIMIZEBOX;
        wndStyle &= ~WS_SYSMENU;
        SetWindowLong(g_hWnd, GWL_STYLE, wndStyle);

        CHotkey CONoneHotkey(0, false);
        g_features.push_back(std::make_unique<CNoclip>(CHotkey('F', true)));
        g_features.push_back(std::make_unique<CVomit>(CHotkey(NULL, true)));
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
        g_features.push_back(std::make_unique<CBypassPeanut>(CONoneHotkey));
        g_features.push_back(std::make_unique<CFovChanger>(CONoneHotkey));

        g_features.push_back(std::make_unique<CPlayers>());
        g_features.push_back(std::make_unique<CBypassKeycodes>());
        g_features.push_back(std::make_unique<CCameraFix>());

        std::thread(fnCatchHotkeys).detach();
    }

    void fnSetTheme()
    {
        g_pFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void *)FiraCode, FiraCode_len, 16);

        /*
        * https://github.com/ocornut/imgui/issues/707#issuecomment-917151020
        */

        ImVec4 *colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(8.00f, 8.00f);
        style.FramePadding = ImVec2(5.00f, 2.00f);
        style.CellPadding = ImVec2(6.00f, 6.00f);
        style.ItemSpacing = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
        style.IndentSpacing = 25;
        style.ScrollbarSize = 15;
        style.GrabMinSize = 10;
        style.WindowBorderSize = 1;
        style.ChildBorderSize = 1;
        style.PopupBorderSize = 1;
        style.FrameBorderSize = 1;
        style.TabBorderSize = 1;
        //style.WindowRounding = 7;
        style.ChildRounding = 4;
        style.FrameRounding = 3;
        style.PopupRounding = 4;
        style.ScrollbarRounding = 9;
        style.GrabRounding = 3;
        style.LogSliderDeadzone = 4;
        style.TabRounding = 4;
    }

    void fnDrawMenu()
    {
        static bool s_bMenuActive = true;
       
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            SetWindowPos(g_hWnd, HWND_TOPMOST, NULL, NULL, NULL, NULL,
                SWP_NOMOVE | SWP_NOSIZE | (s_bMenuActive ? SWP_HIDEWINDOW : SWP_SHOWWINDOW));

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

        if (g_pFont)
        {
            ImGui::PushFont(g_pFont);
        }

        if (*SDK::pppCOServerInfo && **SDK::pppCOServerInfo && (**SDK::pppCOServerInfo)->isProtected())
        {
            ImGui::Text("You cannot use hacks on a protected server.");

            ImGui::PopFont();
            ImGui::End();
            return;
        }

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

        ImGui::SameLine();
        if (ImGui::Button("Players", tabsButtonSize))
        {
            s_iCurrentTab = Tab::Players;
        }
        
        bool bFirst = true;
        for (const auto &feature : g_features)
        {
            if (s_iCurrentTab != feature->m_tab) continue;
            
            if (bFirst)
            {
                bFirst = false;
            }
            else
            {
                ImGui::Separator();
            }

            feature->fnDraw(uElementId);
        }

        ImGui::NewLine(); // slider fix
        ImGui::NewLine(); // dont judge me please

        ImGui::PopFont();
        ImGui::End();
    }

    void fnCatchHotkeys()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            hotkeysMutex.lock();

            for (const auto &feature : g_features)
            {
                if (*SDK::pppCOServerInfo && **SDK::pppCOServerInfo && (**SDK::pppCOServerInfo)->isProtected())
                {
                    if (feature->m_bIsEnabled)
                    {
                        feature->fnDisable();
                    }

                    continue;
                }

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

            hotkeysMutex.unlock();
        }
    }
}

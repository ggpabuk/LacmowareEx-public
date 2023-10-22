#include "pch.h"
#include "CPlayers.h"
#include "CNoclip.h"
#include "menu.h"

CPlayers::CPlayers() :
    CFeature("Players", CHotkey(), Tab::Players)
{
}

void CPlayers::fnDraw(unsigned int &uElementId)
{
    static bool s_hideDead = false;
    ImGui::Checkbox("Hide dead", &s_hideDead);

    auto renderPlayer = [&](CPlayerListElement *pElement)
    {
        CPlayer *pPlayer = *pElement->m_COplayer;

        if (!s_hideDead || !pPlayer->m_isDead)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, pPlayer->getRoleColor());
            ImGui::Text("[%d] %s", pPlayer->m_id, g_breachType[pPlayer->m_breachType]);
            ImGui::PopStyleColor();

#if !_DEBUG
            if (pElement != SDK::pCOPlayerList && !pPlayer->m_isDead) // != localplayer
#endif
            {
                CVector3 *positionWritable = SDK::getPositionWritable();

                ImGui::SameLine();
                ImGui::Text("(%.1fm)", positionWritable->distance(&pPlayer->m_position));

                std::string btnlabel = std::string("TP##") + std::to_string(uElementId++);
                ImGui::SameLine();
                if (ImGui::SmallButton(btnlabel.c_str()) && positionWritable)
                {
                    menu::hotkeysMutex.lock();

                    if (!CNoclip::m_pCOInstance->m_bIsEnabled)
                    {
                        CNoclip::m_pCOInstance->fnEnable();
                    }

                    memcpy(positionWritable, &pPlayer->m_position, sizeof(CVector3));

                    CNoclip::m_pCOInstance->m_COHotkey.m_bHoldToUse = false;

                    menu::hotkeysMutex.unlock();
                }
            }
        }
    };

    CPlayerListElement::foreach(renderPlayer);

    if (ImGui::SmallButton("SCP-1499 Warp"))
    {
        CVector3 *positionWritable = SDK::getPositionWritable();
        if (positionWritable)
        {
            menu::hotkeysMutex.lock();

            if (!CNoclip::m_pCOInstance->m_bIsEnabled)
            {
                CNoclip::m_pCOInstance->fnEnable();
            }

            positionWritable->m_x = 10.0f;
            positionWritable->m_y = 806.0f;
            positionWritable->m_z = 10.0f;

            CNoclip::m_pCOInstance->m_COHotkey.m_bHoldToUse = false;

            menu::hotkeysMutex.unlock();
        }
    }
}

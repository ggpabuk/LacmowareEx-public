#include "pch.h"
#include "CPlayers.h"
#include "CNoclip.h"

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

            if (!pPlayer->m_isDead)
            {
                //ImGui::SameLine();
                //ImGui::Text("%.f hp", pPlayer->m_health);
                
                if (pElement != SDK::pCOPlayerList) // != localplayer
                {
                    CVector3 *positionWritable = SDK::getPositionWritable();
                    
                    ImGui::SameLine();
                    ImGui::Text("(%.1fm)", positionWritable->distance(&pPlayer->m_position));
                    
                    std::string btnlabel = std::string("TP##") + std::to_string(uElementId++);
                    ImGui::SameLine();
                    if (ImGui::SmallButton(btnlabel.c_str()) && positionWritable)
                    {
                        if (!CNoclip::m_pCOInstance->m_bIsEnabled)
                        {
                            CNoclip::m_pCOInstance->fnEnable();
                            std::this_thread::sleep_for(std::chrono::milliseconds(300));
                        }

                        memcpy(positionWritable, &pPlayer->m_position, sizeof(CVector3));
                    }
                }
            }
        }
    };

    CPlayerListElement::foreach(renderPlayer);
}

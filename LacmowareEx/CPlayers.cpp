#include "pch.h"
#include "CPlayers.h"

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
            ImGui::Text("[%d] %s", pPlayer->m_id, g_breachType[pPlayer->m_breachType]);

            if (!pPlayer->m_isDead)
            {
                //ImGui::SameLine();
                //ImGui::Text("%.f hp", pPlayer->m_health);

                /*
                if (pElement != SDK::pCOPlayerList) // != localplayer
                {
                    ImGui::SameLine(0.5);
                    if (ImGui::SmallButton("TP"))
                    {
                    }
                }
                */
            }
        }
    };

    CPlayerListElement::foreach(renderPlayer);
}

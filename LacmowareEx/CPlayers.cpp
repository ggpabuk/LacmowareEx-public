#include "pch.h"
#include "CPlayers.h"

CPlayers::CPlayers() :
    CFeature("Players", CHotkey(), Tab::Players)
{
}

void CPlayers::fnDraw(unsigned int &uElementId)
{
    bool hideDead;
    ImGui::Checkbox("Hide dead", &hideDead);

    if (!SDK::pCOPlayerList || !*SDK::pppCOServerInfo || !**SDK::pppCOServerInfo) return;

    CPlayerListElement *pElement = SDK::pCOPlayerList;
    CServerInfo *pServerInfo = **SDK::pppCOServerInfo;
    int online = pServerInfo->PlayersCount;

    for (UINT i = 0; i < online;)
    {
        if (!SDK::pCOPlayerList) break;

        if (pElement->fnIsPlayerValid())
        {
            ++i;

            CPlayer *pPlayer = *pElement->m_COplayer;

            if (!hideDead || !pPlayer->m_isDead)
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
        }

        pElement = pElement->fnGetNext();
    }
}

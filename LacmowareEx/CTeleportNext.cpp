#include "pch.h"
#include "CTeleportNext.h"

CTeleportNext::CTeleportNext(CHotkey COHotkey) :
    CFeature("Teleport Next Player", COHotkey, Tab::Movement)
{
    fnSelectFirstElement();
}

void CTeleportNext::fnSelectFirstElement()
{
    m_iCurrentPlayerNumber = 0;
    m_currentPlayerElement = SDK::g_pCOPlayerList;
}

bool CTeleportNext::fnTrySelectNext()
{
    do
    {
        if (!*SDK::g_pppCOServerInfo || !**SDK::g_pppCOServerInfo)
        {
            return false;
        }

        CServerInfo *pCOServerInfo = **SDK::g_pppCOServerInfo;
        if (++m_iCurrentPlayerNumber > pCOServerInfo->PlayersCount)
        {
            fnSelectFirstElement();
        }

        m_currentPlayerElement = m_currentPlayerElement->fnGetNext();
    }
    while (!m_currentPlayerElement || !m_currentPlayerElement->fnIsPlayerValid() ||
          (*m_currentPlayerElement->m_COplayer)->IsDead);

    return true;
}

void CTeleportNext::fnEnable()
{
    if (!*SDK::g_pppCOServerInfo || !**SDK::g_pppCOServerInfo ||
        !SDK::g_pCOPlayerList->fnIsPlayerValid())
    {
        return;
    }

    CServerInfo *pCOServerInfo = **SDK::g_pppCOServerInfo;
    CPlayer *pCOLocalPlayer = *SDK::g_pCOPlayerList->m_COplayer;
    if (pCOServerInfo->PlayersCount < 2 || pCOLocalPlayer->IsDead)
    {
        return;
    }

    if ((!m_currentPlayerElement || !m_currentPlayerElement->fnIsPlayerValid()) &&
        !fnTrySelectNext())
    {
        return;
    }

    CPlayer *pCOCurrentPlayer = *m_currentPlayerElement->m_COplayer;
    Vector3 *pCOLocalPosition = SDK::fnGetLocalPosition();

    bool bNoclipDisabled = !CNoclip::m_pCOInstance->m_bIsEnabled;
    if (bNoclipDisabled)
    {
        CNoclip::m_pCOInstance->fnEnable();
    }

    pCOLocalPosition->x = pCOCurrentPlayer->x;
    pCOLocalPosition->y = pCOCurrentPlayer->y;
    pCOLocalPosition->z = pCOCurrentPlayer->z;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (bNoclipDisabled)
    {
        CNoclip::m_pCOInstance->fnDisable();
    }

    fnTrySelectNext();
}

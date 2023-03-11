#include "pch.h"
#include "sdk.h"
#include "CPlayerListElement.h"

void CPlayerListElement::foreach(std::function<void(CPlayerListElement *)> callback)
{
    if (!SDK::pCOPlayerList || !*SDK::pppCOServerInfo || !**SDK::pppCOServerInfo) return;

    CPlayerListElement *pElement = SDK::pCOPlayerList;
    CServerInfo *pServerInfo = **SDK::pppCOServerInfo;
    int online = pServerInfo->PlayersCount;

    for (UINT i = 0; i < online;)
    {
        if (!SDK::pCOPlayerList || !*SDK::pppCOServerInfo || !**SDK::pppCOServerInfo) break;

        if (pElement->fnIsPlayerValid())
        {
            ++i;
            callback(pElement);
        }

        pElement = pElement->fnGetNext();
    }
}

bool CPlayerListElement::fnIsPlayerValid()
{
    return m_COplayer && *m_COplayer &&
        memory::fnIsMemoryReadable(*m_COplayer, 1);
}

CPlayerListElement *CPlayerListElement::fnGetNext()
{
    return reinterpret_cast<CPlayerListElement*>(*reinterpret_cast<DWORD*>(this) + 0x04);
}

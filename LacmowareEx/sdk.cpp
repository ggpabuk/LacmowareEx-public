#include "pch.h"
#include "sdk.h"

namespace SDK
{
    int *piWireframe;
    int *piCurrentGunId;
    int *piMaynardKeycode;
    CSettings *pCOSettings;
    CVisuals *pCOVisuals;
    CPlayerStats *pCOPlayerStats;
    CPlayerListElement *pCOPlayerList;
    CScpStats ***pppCOScpStats;
    CIntercom ***pppCOIntercom;
    CServerInfo ***pppCOServerInfo;
    CGunsContainer ***pppCOGunContainer;

    void fnInit()
    {
        auto gameModule = (DWORD)GetModuleHandle(NULL);
        DWORD base = memory::fnFindDMAAddy(gameModule + 0x000F5400, offsets::base);

        piWireframe       = reinterpret_cast<int *>(base + offsets::wireframe);
        piCurrentGunId    = reinterpret_cast<int *>(base + offsets::currentGunId);
        piMaynardKeycode  = reinterpret_cast<int *>(base + offsets::maynardKeycode);
        pCOSettings       = reinterpret_cast<CSettings *>(base + offsets::gammaUpdate);
        pCOVisuals        = reinterpret_cast<CVisuals *>(base + offsets::visuals);
        pCOPlayerStats    = reinterpret_cast<CPlayerStats *>(base + offsets::playerStats);
        pCOPlayerList     = reinterpret_cast<CPlayerListElement *>(base + offsets::playerList);
        pppCOScpStats     = reinterpret_cast<CScpStats ***>(base + offsets::scpStats);
        pppCOIntercom     = reinterpret_cast<CIntercom ***>(base + offsets::intercom);
        pppCOServerInfo   = reinterpret_cast<CServerInfo ***>(base + offsets::serverInfo);
        pppCOGunContainer = reinterpret_cast<CGunsContainer ***>(base + offsets::gunContainer);
    }

    CVector3 *getPositionWritable()
    {
        auto gameModule = (DWORD)GetModuleHandle(NULL);
        return reinterpret_cast<CVector3 *>(memory::fnFindDMAAddy(gameModule + 0x000F68FC, offsets::positionWritable));
    }
}

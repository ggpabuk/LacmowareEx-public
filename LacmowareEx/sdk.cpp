#include "pch.h"
#include "sdk.h"

namespace SDK
{
    int *g_piWireframe;
    int *g_piGammaUpdate;
    int *g_piCurrentGunId;
    int *g_piMaynardKeycode;
    CVisuals *g_pCOVisuals;
    CScpStats ***g_pppCOScpStats;
    CIntercom ***g_pppCOIntercom;
    CServerInfo ***g_pppCOServerInfo;
    CPlayerStats *g_pCOPlayerStats;
    CGunsContainer ***g_pppCOGunContainer;
    CPlayerListElement *g_pCOPlayerList;

    void fnInit()
    {
        auto gameModule = (DWORD)GetModuleHandle(NULL);
        DWORD base = memory::fnFindDMAAddy(gameModule + 0x000F5400, offsets::base);


        g_piWireframe       = reinterpret_cast<int *>(base + offsets::wireframe);
        g_piGammaUpdate     = reinterpret_cast<int *>(base + offsets::gammaUpdate);
        g_piCurrentGunId    = reinterpret_cast<int *>(base + offsets::currentGunId);
        g_piMaynardKeycode  = reinterpret_cast<int *>(base + offsets::maynardKeycode);
        g_pCOVisuals        = reinterpret_cast<CVisuals *>(base + offsets::visuals);
        g_pppCOScpStats     = reinterpret_cast<CScpStats ***>(base + offsets::scpStats);
        g_pppCOIntercom     = reinterpret_cast<CIntercom ***>(base + offsets::intercom);
        g_pppCOServerInfo   = reinterpret_cast<CServerInfo ***>(base + offsets::serverInfo);
        g_pCOPlayerStats    = reinterpret_cast<CPlayerStats *>(base + offsets::playerStats);
        g_pppCOGunContainer = reinterpret_cast<CGunsContainer ***>(base + offsets::gunContainer);
        g_pCOPlayerList     = reinterpret_cast<CPlayerListElement *>(base + offsets::playerList);
    }

    Vector3 *fnGetLocalPosition()
    {
        auto gameModule = (DWORD)GetModuleHandle(NULL);
        return reinterpret_cast<Vector3 *>(memory::fnFindDMAAddy(gameModule + 0x000F68DC, offsets::localPosition));
    }
}

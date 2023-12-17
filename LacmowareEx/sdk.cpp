#include "pch.h"
#include "sdk.h"
#include "CSendHook.h"
#include "CRecvHook.h"

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

    static void initHooks()
    {
        MH_STATUS status = MH_Initialize();
        if (status != MH_OK)
        {
            MessageBoxA(0, std::format("MH_Initialize failed with code {}", (int)status).c_str(), "", 0);
            exit(0);
        }

        CSendHook::enable();
        CRecvHook::enable();
    }

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

        initHooks();
    }

    CVector3 *getPositionWritable()
    {
        auto gameModule = (DWORD)GetModuleHandle(NULL);
        return reinterpret_cast<CVector3 *>(memory::fnFindDMAAddy(gameModule + 0x000F5400, offsets::positionWritable));
    }
}

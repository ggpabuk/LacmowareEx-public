#pragma once

#include "CIntercom.h"
#include "CPlayerStats.h"
#include "CGunsContainer.h"
#include "CVisuals.h"
#include "CScpStats.h"
#include "CServerInfo.h"
#include "CPlayerListElement.h"
#include "Vector3.h"
#include "memory.h"
#include "offsets.h"

namespace SDK
{
    extern int *g_piWireframe;
    extern int *g_piGammaUpdate;
    extern int *g_piCurrentGunId;
    extern int *g_piMaynardKeycode;
    extern CVisuals *g_pCOVisuals;
    extern CScpStats ***g_pppCOScpStats;
    extern CIntercom ***g_pppCOIntercom;
    extern CServerInfo ***g_pppCOServerInfo;
    extern CPlayerStats *g_pCOPlayerStats;
    extern CGunsContainer ***g_pppCOGunContainer;
    extern CPlayerListElement *g_pCOPlayerList;

    void fnInit();
}

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
#include "CSettings.h"

namespace SDK
{
    extern int *piWireframe;
    extern int *piCurrentGunId;
    extern int *piMaynardKeycode;
    extern CSettings *pCOSettings;
    extern CVisuals *pCOVisuals;
    extern CPlayerStats *pCOPlayerStats;
    extern CPlayerListElement *pCOPlayerList;
    extern CScpStats ***pppCOScpStats;
    extern CIntercom ***pppCOIntercom;
    extern CServerInfo ***pppCOServerInfo;
    extern CGunsContainer ***pppCOGunContainer;

    void fnInit();
}

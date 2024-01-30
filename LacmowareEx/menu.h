#pragma once

#include "Imgui/imgui.h"
#include "keyNames.h"
#include "Tab.h"
#include "CFeature.h"
#include "CNoclip.h"
#include "CNoBlink.h"
#include "CWallhack.h"
#include "CInfStamina.h"
#include "CNoFilters.h"
#include "CInfAmmo.h"
#include "CMaxShootSpeed.h"
#include "CNoRecoil.h"
#include "CForceVoice.h"
#include "CVomit.h"
#include "CWireframe.h"
#include "CSpeedhack.h"
#include "CBypassKeycodes.h"
#include "FiraCode.h"
#include "sdk.h"
#include "CFovChanger.h"
#include "CBypassPeanut.h"
#include "CPlayers.h"

#include <Windows.h>

namespace menu
{
    constexpr int iWidth = 600;
    constexpr int iHeight = 400;

    extern std::mutex hotkeysMutex;

    void fnInit();
    void fnSetTheme();
    void fnDrawMenu();
    void fnCatchHotkeys();
}

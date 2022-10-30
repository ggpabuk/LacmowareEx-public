#pragma once

#include "CFeature.h"
#include "CHotkey.h"
#include "CNoclip.h"
#include "CInfStamina.h"
#include "CWallhack.h"
#include "CNoBlink.h"
#include "CInfAmmo.h"
#include "CMaxShootSpeed.h"
#include "CNoRecoil.h"
#include "CBypassKeycodes.h"
#include "CVomit.h"
#include "CSpeedhack.h"
#include "CWireframe.h"
#include "CNoFilters.h"
#include "CForceVoice.h"
#include "freezeManager.h"
#include "sdk.h"
#include "menuRenderer.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

void fnInit();
void fnCreateConsole();

#pragma once

#include "CGunsContainer.h"
#include "weaponsFreezeState.h"
#include "sdk.h"

namespace freezeManager
{
    extern std::map<float *, float> g_floatFreezes;
    extern std::map<int *, int> g_intFreezes;
    extern BYTE g_fWeaponsFreezeState;
    extern std::mutex g_floatFreezesMutex;
    extern std::mutex g_intFreezesMutex;
    extern std::mutex g_weaponsFreezeMutex;

    void fnInit();
    void fnFreezeAll();
};

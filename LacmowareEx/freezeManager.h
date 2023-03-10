#pragma once

#include "CGunsContainer.h"
#include "weaponsFreezeState.h"
#include "sdk.h"

namespace freezeManager
{
    extern std::map<float *, float> floatFreezes;
    extern std::map<int *, int> intFreezes;
    extern BYTE fWeaponsFreezeState;
    extern bool peanutFreeze;
    extern std::mutex floatFreezesMutex;
    extern std::mutex intFreezesMutex;
    extern std::mutex weaponsFreezeMutex;
    extern std::mutex peanutFreezeMutex;

    void fnInit();
    void fnFreezeAll();
};

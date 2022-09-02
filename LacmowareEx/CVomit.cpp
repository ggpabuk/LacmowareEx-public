#include "pch.h"
#include "CVomit.h"

CVomit::CVomit(CHotkey COHotkey) :
    CFeature("Vomit", COHotkey, Tab::Fun)
{

}

void CVomit::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::g_pCOPlayerStats->VomitTimer, -15.0f));
}

void CVomit::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::g_floatFreezesMutex.lock();
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::g_pCOPlayerStats->VomitTimer));
    freezeManager::g_floatFreezesMutex.unlock();

    SDK::g_pCOPlayerStats->VomitTimer = 0;
    SDK::g_pCOPlayerStats->Vomit = 0;
}

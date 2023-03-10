#include "pch.h"
#include "CVomit.h"

CVomit::CVomit(CHotkey COHotkey) :
    CFeature("Vomit", COHotkey, Tab::Fun)
{

}

void CVomit::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOPlayerStats->VomitTimer, -15.0f));
}

void CVomit::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOPlayerStats->VomitTimer));
    freezeManager::floatFreezesMutex.unlock();

    SDK::pCOPlayerStats->VomitTimer = 0;
    SDK::pCOPlayerStats->Vomit = 0;
}

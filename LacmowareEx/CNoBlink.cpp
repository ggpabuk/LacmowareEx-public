#include "pch.h"
#include "CNoBlink.h"

CNoBlink::CNoBlink(CHotkey COHotkey) :
    CFeature("No Blink", COHotkey, Tab::Visuals)
{

}

void CNoBlink::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOPlayerStats->BlinkTimer, 569.0f));
}

void CNoBlink::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOPlayerStats->BlinkTimer));
    freezeManager::floatFreezesMutex.unlock();
}

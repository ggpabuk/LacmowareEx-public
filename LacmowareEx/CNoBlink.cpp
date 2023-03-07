#include "pch.h"
#include "CNoBlink.h"

CNoBlink::CNoBlink(CHotkey COHotkey) :
    CFeature("No Blink", COHotkey, Tab::Visuals)
{

}

void CNoBlink::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::pCOPlayerStats->BlinkTimer, 569.0f));
}

void CNoBlink::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::g_floatFreezesMutex.lock();
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::pCOPlayerStats->BlinkTimer));
    freezeManager::g_floatFreezesMutex.unlock();
}

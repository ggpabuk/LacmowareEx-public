#include "pch.h"
#include "CBypassPeanut.h"

CBypassPeanut::CBypassPeanut(CHotkey COHotkey) :
    CFeature("Bypass Peanut", COHotkey, Tab::Movement)
{
}

void CBypassPeanut::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::peanutFreeze = true;
}

void CBypassPeanut::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::peanutFreezeMutex.lock();
    freezeManager::peanutFreeze = false;
    freezeManager::peanutFreezeMutex.unlock();
}

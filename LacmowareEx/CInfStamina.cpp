#include "pch.h"
#include "CInfStamina.h"

CInfStamina::CInfStamina(CHotkey COHotkey) :
    CFeature("Infinite Stamina", COHotkey, Tab::Movement)
{

}

void CInfStamina::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOPlayerStats->Stamina, 99.0f));
}

void CInfStamina::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOPlayerStats->Stamina));
    freezeManager::floatFreezesMutex.unlock();
}

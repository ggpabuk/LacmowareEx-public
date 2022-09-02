#include "pch.h"
#include "CInfStamina.h"

CInfStamina::CInfStamina(CHotkey COHotkey) :
    CFeature("Infinite Stamina", COHotkey, Tab::Movement)
{

}

void CInfStamina::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::g_pCOPlayerStats->Stamina, 99.0f));
}

void CInfStamina::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::g_floatFreezesMutex.lock();
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::g_pCOPlayerStats->Stamina));
    freezeManager::g_floatFreezesMutex.unlock();
}

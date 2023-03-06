#include "pch.h"
#include "CNoFilters.h"

CNoFilters::CNoFilters(CHotkey COHotkey) :
    CFeature("No Filters", COHotkey, Tab::Visuals)
{

}

void CNoFilters::fnEnable()
{
    CFeature::fnEnable();

    freezeManager::g_floatFreezes.insert(std::pair(&SDK::g_pCOVisuals->BlurVolume, 0));
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::g_pCOVisuals->CameraShake, 0));

    m_oldCameraFogNear = SDK::g_pCOVisuals->CameraFogNear;
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::g_pCOVisuals->CameraFogNear, FLT_MAX));

    m_oldCameraFogFar = SDK::g_pCOVisuals->CameraFogFar;
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::g_pCOVisuals->CameraFogFar, 1000));
}

void CNoFilters::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::g_floatFreezesMutex.lock();
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::g_pCOVisuals->BlurVolume));
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::g_pCOVisuals->CameraShake));
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::g_pCOVisuals->CameraFogNear));
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::g_pCOVisuals->CameraFogFar));
    freezeManager::g_floatFreezesMutex.unlock();

    SDK::g_pCOVisuals->CameraFogNear = m_oldCameraFogNear;
    SDK::g_pCOVisuals->CameraFogFar = m_oldCameraFogFar;
}

#include "pch.h"
#include "CNoFilters.h"

CNoFilters::CNoFilters(CHotkey COHotkey) :
    CFeature("No Filters", COHotkey, Tab::Visuals)
{

}

void CNoFilters::fnEnable()
{
    CFeature::fnEnable();

    freezeManager::g_floatFreezes.insert(std::pair(&SDK::pCOVisuals->BlurVolume, 0));
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::pCOVisuals->CameraShake, 0));

    m_oldCameraFogNear = SDK::pCOVisuals->CameraFogNear;
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::pCOVisuals->CameraFogNear, FLT_MAX));

    m_oldCameraFogFar = SDK::pCOVisuals->CameraFogFar;
    freezeManager::g_floatFreezes.insert(std::pair(&SDK::pCOVisuals->CameraFogFar, FLT_MAX));
}

void CNoFilters::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::g_floatFreezesMutex.lock();
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::pCOVisuals->BlurVolume));
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::pCOVisuals->CameraShake));
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::pCOVisuals->CameraFogNear));
    freezeManager::g_floatFreezes.erase(freezeManager::g_floatFreezes.find(&SDK::pCOVisuals->CameraFogFar));
    freezeManager::g_floatFreezesMutex.unlock();

    SDK::pCOVisuals->CameraFogNear = m_oldCameraFogNear;
    SDK::pCOVisuals->CameraFogFar = m_oldCameraFogFar;
}

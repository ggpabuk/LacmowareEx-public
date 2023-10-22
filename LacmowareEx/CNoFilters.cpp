#include "pch.h"
#include "CNoFilters.h"

CNoFilters::CNoFilters(CHotkey COHotkey) :
    CFeature("No Filters", COHotkey, Tab::Visuals)
{

}

void CNoFilters::fnEnable()
{
    CFeature::fnEnable();

    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOVisuals->BlurVolume, 0));
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOVisuals->CameraShake, 0));

    m_oldCameraFogNear = SDK::pCOVisuals->CameraFogNear;
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOVisuals->CameraFogNear, FLT_MAX));

    m_oldCameraFogFar = SDK::pCOVisuals->CameraFogFar;
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOVisuals->CameraFogFar, FLT_MAX));
}

void CNoFilters::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOVisuals->BlurVolume));
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOVisuals->CameraShake));
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOVisuals->CameraFogNear));
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOVisuals->CameraFogFar));
    freezeManager::floatFreezesMutex.unlock();

    SDK::pCOVisuals->CameraFogNear = m_oldCameraFogNear;
    SDK::pCOVisuals->CameraFogFar = m_oldCameraFogFar;
}

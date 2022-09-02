#include "pch.h"
#include "CMaxShootSpeed.h"

CMaxShootSpeed::CMaxShootSpeed(CHotkey COHotkey) :
    CFeature("Max Shoot Speed", COHotkey, Tab::Combat)
{
    ZeroMemory(m_aOldShootSpeed, LENGTH(m_aOldShootSpeed));
}

void CMaxShootSpeed::fnEnable()
{
    if (!*SDK::g_pppCOGunContainer || !**SDK::g_pppCOGunContainer)
    {
        return;
    }

    CFeature::fnEnable();

    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::g_pppCOGunContainer)->Guns[i];
        m_aOldShootSpeed[i] = gun.ShootSpeed;
    }

    freezeManager::g_fWeaponsFreezeState |= ShootSpeed;
}

void CMaxShootSpeed::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::g_fWeaponsFreezeState &= ~ShootSpeed;

    if (!*SDK::g_pppCOGunContainer || !**SDK::g_pppCOGunContainer)
    {
        return;
    }

    freezeManager::g_weaponsFreezeMutex.lock();
    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::g_pppCOGunContainer)->Guns[i];
        gun.ShootSpeed = m_aOldShootSpeed[i];
    }
    freezeManager::g_weaponsFreezeMutex.unlock();
}

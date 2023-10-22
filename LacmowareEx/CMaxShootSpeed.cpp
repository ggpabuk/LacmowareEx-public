#include "pch.h"
#include "CMaxShootSpeed.h"

CMaxShootSpeed::CMaxShootSpeed(CHotkey COHotkey) :
    CFeature("Max Shoot Speed", COHotkey, Tab::Combat)
{
    ZeroMemory(m_aOldShootSpeed, LENGTH(m_aOldShootSpeed));
}

void CMaxShootSpeed::fnEnable()
{
    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    CFeature::fnEnable();

    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::pppCOGunContainer)->Guns[i];
        m_aOldShootSpeed[i] = gun.ShootSpeed;
    }

    freezeManager::fWeaponsFreezeState |= ShootSpeed;
}

void CMaxShootSpeed::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::fWeaponsFreezeState &= ~ShootSpeed;

    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    freezeManager::weaponsFreezeMutex.lock();
    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::pppCOGunContainer)->Guns[i];
        gun.ShootSpeed = m_aOldShootSpeed[i];
    }
    freezeManager::weaponsFreezeMutex.unlock();
}

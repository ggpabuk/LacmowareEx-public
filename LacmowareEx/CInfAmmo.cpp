#include "pch.h"
#include "CInfAmmo.h"

CInfAmmo::CInfAmmo(CHotkey COHotkey) :
    CFeature("Infinite Ammo", COHotkey, Tab::Combat)
{

}

void CInfAmmo::fnEnable()
{
    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    CFeature::fnEnable();
    freezeManager::fWeaponsFreezeState |= Ammo;
}

void CInfAmmo::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::fWeaponsFreezeState &= ~Ammo;

    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    freezeManager::weaponsFreezeMutex.lock();
    for (auto &gun : (**SDK::pppCOGunContainer)->Guns)
    {
        gun.CurrentAmmo = gun.MaxAmmo;
    }
    freezeManager::weaponsFreezeMutex.unlock();
}

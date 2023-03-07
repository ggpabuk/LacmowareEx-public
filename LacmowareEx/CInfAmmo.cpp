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
    freezeManager::g_fWeaponsFreezeState |= Ammo;
}

void CInfAmmo::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::g_fWeaponsFreezeState &= ~Ammo;

    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    freezeManager::g_weaponsFreezeMutex.lock();
    for (auto &gun : (**SDK::pppCOGunContainer)->Guns)
    {
        gun.CurrentAmmo = gun.MaxAmmo;
    }
    freezeManager::g_weaponsFreezeMutex.unlock();
}

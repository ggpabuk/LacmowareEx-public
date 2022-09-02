#include "pch.h"
#include "CInfAmmo.h"

CInfAmmo::CInfAmmo(CHotkey COHotkey) :
    CFeature("Infinite Ammo", COHotkey, Tab::Combat)
{

}

void CInfAmmo::fnEnable()
{
    if (!*SDK::g_pppCOGunContainer || !**SDK::g_pppCOGunContainer)
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

    if (!*SDK::g_pppCOGunContainer || !**SDK::g_pppCOGunContainer)
    {
        return;
    }

    freezeManager::g_weaponsFreezeMutex.lock();
    for (auto &gun : (**SDK::g_pppCOGunContainer)->Guns)
    {
        gun.CurrentAmmo = gun.MaxAmmo;
    }
    freezeManager::g_weaponsFreezeMutex.unlock();
}

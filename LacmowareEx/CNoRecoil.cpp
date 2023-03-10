#include "pch.h"
#include "CNoRecoil.h"

CNoRecoil::CNoRecoil(CHotkey COHotkey) :
    CFeature("No Recoil", COHotkey, Tab::Combat)
{
    ZeroMemory(m_aOldRecoil, LENGTH(m_aOldRecoil));
}

void CNoRecoil::fnEnable()
{
    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    CFeature::fnEnable();

    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::pppCOGunContainer)->Guns[i];
        m_aOldRecoil[i] = gun.RecoilForce;
    }

    freezeManager::fWeaponsFreezeState |= Recoil;
}

void CNoRecoil::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::fWeaponsFreezeState &= ~Recoil;

    if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer)
    {
        return;
    }

    freezeManager::weaponsFreezeMutex.lock();
    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::pppCOGunContainer)->Guns[i];
        gun.RecoilForce = m_aOldRecoil[i];
    }
    freezeManager::weaponsFreezeMutex.unlock();
}

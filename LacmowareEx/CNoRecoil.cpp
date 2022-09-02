#include "pch.h"
#include "CNoRecoil.h"

CNoRecoil::CNoRecoil(CHotkey COHotkey) :
    CFeature("No Recoil", COHotkey, Tab::Combat)
{
    ZeroMemory(m_aOldRecoil, LENGTH(m_aOldRecoil));
}

void CNoRecoil::fnEnable()
{
    if (!*SDK::g_pppCOGunContainer || !**SDK::g_pppCOGunContainer)
    {
        return;
    }

    CFeature::fnEnable();

    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::g_pppCOGunContainer)->Guns[i];
        m_aOldRecoil[i] = gun.RecoilForce;
    }

    freezeManager::g_fWeaponsFreezeState |= Recoil;
}

void CNoRecoil::fnDisable()
{
    CFeature::fnDisable();
    freezeManager::g_fWeaponsFreezeState &= ~Recoil;

    if (!*SDK::g_pppCOGunContainer || !**SDK::g_pppCOGunContainer)
    {
        return;
    }

    freezeManager::g_weaponsFreezeMutex.lock();
    for (unsigned int i = 0; i < gunsCount; ++i)
    {
        CGun &gun = (**SDK::g_pppCOGunContainer)->Guns[i];
        gun.RecoilForce = m_aOldRecoil[i];
    }
    freezeManager::g_weaponsFreezeMutex.unlock();
}

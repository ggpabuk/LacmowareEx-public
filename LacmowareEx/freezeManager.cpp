#include "pch.h"
#include "freezeManager.h"

namespace freezeManager
{
    std::map<int *, int> g_intFreezes;
    std::map<float *, float> g_floatFreezes;
    BYTE g_fWeaponsFreezeState;
    std::mutex g_intFreezesMutex;
    std::mutex g_floatFreezesMutex;
    std::mutex g_weaponsFreezeMutex{};

    void fnInit()
    {
        g_intFreezes = std::map<int *, int>();
        g_floatFreezes = std::map<float *, float>();
        g_fWeaponsFreezeState = 0;

        std::thread(fnFreezeAll).detach();
    }

    void fnFreezeAll()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if (g_intFreezesMutex.try_lock())
            {
                for (const auto &[ptr, value] : g_intFreezes)
                {
                    if (!ptr) continue;
                    *ptr = value;
                }

                g_intFreezesMutex.unlock();
            }


            if (g_floatFreezesMutex.try_lock())
            {
                for (const auto &[ptr, value] : g_floatFreezes)
                {
                    if (!ptr) continue;
                    *ptr = value;
                }

                g_floatFreezesMutex.unlock();
            }
          
            if (!*SDK::pppCOGunContainer || !**SDK::pppCOGunContainer) continue;

            g_weaponsFreezeMutex.lock();
            for (auto &gun : (**SDK::pppCOGunContainer)->Guns)
            {
                if (g_fWeaponsFreezeState & Ammo)
                {
                    gun.CurrentAmmo = INT_MAX;
                }

                if (g_fWeaponsFreezeState & ShootSpeed)
                {
                    gun.ShootSpeed = FLT_MIN;
                }

                if (g_fWeaponsFreezeState & Recoil)
                {
                    gun.RecoilForce = 0;
                }
            }
            g_weaponsFreezeMutex.unlock();
        }
    }
}

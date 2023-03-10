#include "pch.h"
#include "freezeManager.h"

namespace freezeManager
{
#if FREEZE_DELTA
    static std::chrono::system_clock::time_point last;

#endif

    std::map<int *, int> intFreezes;
    std::map<float *, float> floatFreezes;
    BYTE fWeaponsFreezeState;
    bool peanutFreeze;
    std::mutex intFreezesMutex;
    std::mutex floatFreezesMutex;
    std::mutex weaponsFreezeMutex;
    std::mutex peanutFreezeMutex;

    void fnInit()
    {
        intFreezes = std::map<int *, int>();
        floatFreezes = std::map<float *, float>();
        fWeaponsFreezeState = 0;
        peanutFreeze = false;

        std::thread(fnFreezeAll).detach();
    }

    void fnFreezeAll()
    {
#if FREEZE_DELTA
        std::chrono::system_clock::time_point now;
        std::chrono::duration<double> deltatime;
#endif

        while (true)
        {
#if FREEZE_DELTA
            now = std::chrono::system_clock::now();
            deltatime = now - last;
            last = now;
            
            printf("Freeze manager delta time: %.3f\n", deltatime);
#endif

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if (intFreezesMutex.try_lock())
            {
                for (const auto &[ptr, value] : intFreezes)
                {
                    if (!ptr) continue;
                    *ptr = value;
                }

                intFreezesMutex.unlock();
            }

            if (floatFreezesMutex.try_lock())
            {
                for (const auto &[ptr, value] : floatFreezes)
                {
                    if (!ptr) continue;
                    *ptr = value;
                }

                floatFreezesMutex.unlock();
            }

            if (peanutFreeze && SDK::pCOPlayerList && peanutFreezeMutex.try_lock())
            {
                CPlayerListElement *element = SDK::pCOPlayerList;
                while (element->fnIsPlayerValid())
                {
                    CPlayer *player = *element->m_COplayer;
                    player->m_blinkTimer = -11;
                    element = element->fnGetNext();
                }

                peanutFreezeMutex.unlock();
            }
          
            if (*SDK::pppCOGunContainer && **SDK::pppCOGunContainer)
            {
                weaponsFreezeMutex.lock();
                for (auto &gun : (**SDK::pppCOGunContainer)->Guns)
                {
                    if (fWeaponsFreezeState & Ammo)
                    {
                        gun.CurrentAmmo = INT_MAX;
                    }

                    if (fWeaponsFreezeState & ShootSpeed)
                    {
                        gun.ShootSpeed = FLT_MIN;
                    }

                    if (fWeaponsFreezeState & Recoil)
                    {
                        gun.RecoilForce = 0;
                    }
                }
                weaponsFreezeMutex.unlock();
            }
        }
    }
}

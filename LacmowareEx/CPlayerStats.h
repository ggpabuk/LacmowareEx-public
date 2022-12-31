#pragma once

#include "CIntercom.h"
#include <Windows.h>

class CPlayerStats
{
public:
    float KillTimer;
    int   KillAnim;
    float FallTimer;
    float DeathTimer;
    float Sanity;
    float ForceMove;
    float ForceAngle;
    int   RestoreSanity;
    int   Playable;
    float BlinkFreq;
    float BlinkTimer;
    float EyeIrritation;
    float EyeStuck;
    float BlinkEffect;
    float BlinkEffectTimer;
    float Stamina;
    float StaminaEffect;
    float StaminaEffectTimer;
    BYTE  pad0001[0x10];
    float CameraShakeTimer;
    int   Vomit;
    float VomitTimer;
    int   Regurgitate;
    BYTE  pad0002[0xE];
    float HeartBeatRate;
    float HeartBeatTimer;
    float HeartBeatVolume;
    int   WearingGasMask;
    int   WearingHazmat;
    int   WearingVest;
    int   Wearing714;
    int   WearingNightVision;
    float NVTimer;
    int   SuperMan;
    float SuperManTimer;
    float Injuries;
    float Bloodloss;
    float Infect;
    float HealTimer;
    int   RefinedItems;
    BYTE  pad0003[0x1D4];
    int   GodMode;
    int   Noclip;
    float NoclipSpeed;
    BYTE  pad0004[0x008];
    float CurrentSpeed;
    BYTE  pad0005[0x00C];
    int   Crouch;
};

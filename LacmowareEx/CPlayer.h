#pragma once

#include <Windows.h>

class CPlayer
{
public:
	UINT  Id;
	float x;
	float y;
	float z;
	float Yaw;
	float BonePitch;
	float PrevX;
	float PrevY;
	float PrevZ;
	float PrevYaw;
	float PrevPitch;
	char  pad0000[0x44];
	float BlinkTimer;
	int   IsAfk;
	int   IsDead;
	char  Ready[0x8];
	float CrouchState;
	float PlayerSoundVolume;
	UINT  UsedWeapon;
	float PlayerSoundVolumeFactor;
	UINT  WearingGasMask;
	UINT  WearingNightVision;
	UINT  WearingHazmat;
	UINT  WearingVest;
	char  pad0001[0x20];
	UINT  BreachType;
	char  pad0002[0x50];
	float Health;
};

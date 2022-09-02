#pragma once

#include <Windows.h>

class CVisuals
{
public:
	int   DebugHud;
	float BlurVolume;
	float BlurTimer;
	int   BumpEnabled;
	int   HudEnabled;
	int   Camera;
	float CameraShake;
	BYTE  pad0000[0x74];
	float CurrentCameraZoom;
	int   Brightness;
	float CameraFogNear;
	float CameraFogFar;
	float StoredCameraFogFar;
	float MouseSensitivity;
	int   EnableVRam;
};

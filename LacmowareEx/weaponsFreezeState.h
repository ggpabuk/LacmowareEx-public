#pragma once

enum WeaponsFreezeState : BYTE
{
	Ammo       = 1 << 0,
	ShootSpeed = 1 << 1,
	Recoil     = 1 << 2,
};

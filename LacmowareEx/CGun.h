#pragma once

class CGun
{
public:
    int   Id;
    int   CurrentAmmo;
    int   MaxAmmo;
    float ShootState;
    float ShootSpeed;
    BYTE  pad0000[0x18];
    float RecoilForce;
    BYTE  pad0001[0x1C];
    int   Magazines;
    BYTE  pad0002[0x38];
    int   MaxMagazines;
    BYTE  pad0003[0x18];
};

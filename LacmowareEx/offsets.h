#pragma once

#include <Windows.h>
#include <vector>

typedef int offset_t;

namespace offsets
{
    const std::vector<offset_t> base = { 0x11C, 0x00 };

    const offset_t gunContainer   = -0x1E8; // fixed
    const offset_t visuals        = 0xE14; // fixed
    const offset_t playerStats    = 0xB14; // fixed
    const offset_t maynardKeycode = 0xAEC; // fixed
    const offset_t wireframe      = 0x5B8; // fixed
    const offset_t playerList     = -0x890;
    const offset_t currentGunId   = -0x824;
    const offset_t serverInfo     = -0x44; // fixed
    const offset_t intercom       = -0x5D0;
    const offset_t scpStats       = -0x5CC;
    const offset_t gammaUpdate    = 0x4E0; // fixed
}

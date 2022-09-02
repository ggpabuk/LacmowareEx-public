#pragma once

#include <Windows.h>
#include <vector>

typedef int offset_t;

namespace offsets
{
    const std::vector<offset_t> base          = { 0x1EC, 0x00 };
    const std::vector<offset_t> localPosition = { 0x04, 0x00, 0x40 };

    const offset_t gunContainer   = 0x1ED4; // fixed
    const offset_t visuals        = 0xA70; // fixed
    const offset_t playerStats    = 0x770; // fixed
    const offset_t maynardKeycode = 0x748; // fixed
    const offset_t wireframe      = 0x270; // fixed
    const offset_t playerList     = -0x890;
    const offset_t currentGunId   = -0x824;
    const offset_t serverInfo     = -0x29C; // fixed
    const offset_t intercom       = -0x5D0;
    const offset_t scpStats       = -0x5CC;
    const offset_t gammaUpdate    = 0x198; // fixed
}

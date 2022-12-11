#pragma once

#define OUTDATED 0

#include <Windows.h>
#include <vector>

typedef int offset_t;

namespace offsets
{
    const std::vector<offset_t> base = { 0x11C, 0x00 };

    const offset_t gunContainer   = 0x2464;
    const offset_t visuals        = 0xE50;
    const offset_t playerStats    = 0xB4C;
    const offset_t maynardKeycode = 0xB24;
    const offset_t wireframe      = 0x5E8;
    const offset_t playerList     = OUTDATED;
    const offset_t currentGunId   = OUTDATED;
    const offset_t serverInfo     = 0x44;
    const offset_t intercom       = OUTDATED;
    const offset_t scpStats       = OUTDATED;
    const offset_t gammaUpdate    = 0x510;
}

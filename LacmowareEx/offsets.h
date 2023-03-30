#pragma once

#define OUTDATED 0

#include <Windows.h>
#include <vector>

typedef int offset_t;

namespace offsets
{
    const std::vector<offset_t> base = { 0x11C, 0x00 };
    const std::vector<offset_t> positionWritable = { 0xB8, 0x08, 0x48, 0x40 };

    const offset_t gunContainer   = 0x24C0;
    const offset_t visuals        = 0xE80;
    const offset_t playerStats    = 0xB7C;
    const offset_t maynardKeycode = 0xB54;
    const offset_t wireframe      = 0x61C;
    const offset_t playerList     = -0x284;
    const offset_t currentGunId   = OUTDATED;
    const offset_t serverInfo     = 0x44;
    const offset_t intercom       = OUTDATED;
    const offset_t scpStats       = OUTDATED;
    const offset_t gammaUpdate    = 0x518;
}

#pragma once

#define OUTDATED 0

#include <Windows.h>
#include <vector>

typedef int offset_t;

namespace offsets
{
    const std::vector<offset_t> base = { 0x11C, 0x00 };

    const offset_t gunContainer   = -0xF8; // fixed
    const offset_t visuals        = 0xF24; // fixed
    const offset_t playerStats    = 0xC24; // fixed
    const offset_t maynardKeycode = 0xBFC; // fixed
    const offset_t wireframe      = 0x6C8; // fixed
    const offset_t playerList     = OUTDATED;
    const offset_t currentGunId   = OUTDATED;
    const offset_t serverInfo     = 0x138; // fixed
    const offset_t intercom       = OUTDATED;
    const offset_t scpStats       = OUTDATED;
    const offset_t gammaUpdate    = 0x5F0; // fixed
}

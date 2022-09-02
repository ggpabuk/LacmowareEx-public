#pragma once

#include "CGun.h"

constexpr unsigned int gunsCount = 15;

class CGunsContainer {
public:
    CGun Guns[gunsCount];
};

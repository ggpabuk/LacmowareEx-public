#pragma once

#include "CFeature.h"
#include "offsets.h"
#include "memory.h"
#include "patterns.h"
#include "sdk.h"

class CBypassKeycodes :
    public CFeature
{
public:
    CBypassKeycodes();

    void fnDraw(unsigned int &uElementId) override;
};

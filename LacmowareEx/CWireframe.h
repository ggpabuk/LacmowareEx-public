#pragma once

#include "CFeature.h"
#include "CHotkey.h"
#include "sdk.h"

class CWireframe :
    public CFeature
{
public:
    CWireframe(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};

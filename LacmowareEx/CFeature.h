#pragma once

#include "CHotkey.h"
#include "memory.h"
#include "keyNames.h"
#include "Tab.h"
#include "Imgui/imgui.h"

class CFeature
{
public:
    const char *m_szName;
    bool m_bIsEnabled;
    Tab m_tab;
    CHotkey m_COHotkey;

    CFeature(
        const char *szName,
        CHotkey COHotkey,
        Tab tab,
        bool bDefaultEnabled = false
    );
    virtual ~CFeature();
    
    virtual void fnEnable();
    virtual void fnDisable();
    virtual void fnToggle();
    virtual void fnReload();
    virtual void fnDraw(unsigned int &uElementId);
};

#pragma once

class CHotkey
{
public:
    CHotkey();
    CHotkey(int vKey, bool holdToUse);

    int m_iVKey;
    bool m_bHoldToUse;
};

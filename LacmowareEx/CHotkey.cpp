#include "pch.h"
#include "CHotkey.h"

CHotkey::CHotkey()
{
    m_iVKey = 0;
    m_bHoldToUse = false;
}

CHotkey::CHotkey(int vKey, bool holdToUse)
{
    m_iVKey = vKey;
    m_bHoldToUse = holdToUse;
}

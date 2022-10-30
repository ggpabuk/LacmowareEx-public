#include "pch.h"
#include "CWallhack.h"

CWallhack::CWallhack(CHotkey COHotkey) :
    CFeature("Wallhack", COHotkey, Tab::Visuals)
{
    m_dwAddress = memory::fnFindPatternIDA(0x00000000, 0x10000000, patterns::wallhack096.c_str());
}

void CWallhack::fnEnable()
{
    CFeature::fnEnable();
    memory::fnReplaceWithNop(reinterpret_cast<DWORD *>(m_dwAddress + 0x4C), m_aBuffer1, 6);
    memory::fnReplaceWithNop(reinterpret_cast<DWORD *>(m_dwAddress + 0xC1), m_aBuffer2, 6);
}

void CWallhack::fnDisable()
{
    CFeature::fnDisable();
    memcpy(reinterpret_cast<DWORD *>(m_dwAddress + 0x4C), m_aBuffer1, 6);
    memcpy(reinterpret_cast<DWORD *>(m_dwAddress + 0xC1), m_aBuffer2, 6);
}

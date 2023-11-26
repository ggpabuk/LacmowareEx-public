#include "pch.h"
#include "CFakeMove.h"
#include "patterns.h"
#include "MoveType.h"

CFakeMove::CFakeMove()
	: CFeature("Fake move", CHotkey(), Tab::Fun)
{
	m_pTarget = reinterpret_cast<DWORD *>(memory::fnFindPatternIDA(0x00000000, 0x10000000, patterns::movetypeUpdate.c_str()) + 0x2B + 0x02);
	m_original = *m_pTarget;
	m_moveType = (int)MOVETYPE_FIRST;
}

void CFakeMove::fnDraw(unsigned int &uElementId)
{
	CFeature::fnDraw(uElementId);

	ImGui::SliderInt(std::format("Move type##{}", uElementId++).c_str(),
		&m_moveType, (int)MOVETYPE_FIRST, (int)MOVETYPE_LAST);
}

void CFakeMove::fnEnable()
{
	CFeature::fnEnable();
	*m_pTarget = reinterpret_cast<DWORD>(&m_moveType);
}

void CFakeMove::fnDisable()
{
	CFeature::fnDisable();
	*m_pTarget = m_original;
}

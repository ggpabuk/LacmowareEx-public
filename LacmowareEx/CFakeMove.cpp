#include "pch.h"
#include "CFakeMove.h"
#include "patterns.h"
#include "MoveType.h"
#include "CSendHook.h"

CFakeMove::CFakeMove()
	: CFeature("Fake move", CHotkey(), Tab::Fun)
{
	m_pTarget = reinterpret_cast<DWORD *>(memory::fnFindPatternIDA(0x00000000, 0x10000000, patterns::movetypeUpdate.c_str()) + 0x2B + 0x02);
	m_original = *m_pTarget;
	m_moveType = 0;
	m_jitterEnabled = false;

	CSendHook::addPacketModifier(PacketId::M_UPDATE, 
		[this](char **data, int *len)
		{
			if (!this->m_bIsEnabled || !this->m_jitterEnabled) return;

			static std::random_device s_rd;
			static std::mt19937 s_rng(s_rd());

			std::uniform_int_distribution<unsigned int> dist(0, UINT_MAX);
			*(unsigned int *)(*data + 3) = dist(s_rng);
		});
}

void CFakeMove::fnDraw(unsigned int &uElementId)
{
	CFeature::fnDraw(uElementId);

	ImGui::SliderInt(std::format("Move type##{}", uElementId++).c_str(),
		&m_moveType, 0, 22);

	ImGui::Checkbox(std::format("Jitter##{}", uElementId++).c_str(),
		&m_jitterEnabled);
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

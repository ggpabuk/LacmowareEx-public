#pragma once

#include "CPlayer.h"
#include "memory.h"
#include <Windows.h>

class CPlayerListElement
{
public:
	
	CPlayer* *m_COplayer;

	bool fnIsPlayerValid();
	CPlayerListElement *fnGetNext();
};

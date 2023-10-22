#pragma once

#include "CPlayer.h"
#include "memory.h"
#include <functional>

class CPlayerListElement
{
public:
	CPlayer **m_COplayer;

    static void foreach(std::function<void(CPlayerListElement *)> callback);

	bool fnIsPlayerValid();
	CPlayerListElement *fnGetNext();
};

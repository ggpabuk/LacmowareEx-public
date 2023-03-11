#include "pch.h"
#include "CPlayer.h"

breachTeam CPlayer::getTeam()
{
    switch (m_breachType)
    {
        case 1:
        case 2:
        case 4:
        case 8:
        case 9:
        case 17:
        {
            return breachTeam::Mtf;
        }

        case 3:
        case 7:
        {
            return breachTeam::Chaos;
        }

        case 5:
        case 6:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        {
            return breachTeam::Scp;
        }

        default:
        {
            return breachTeam::None;
        }
    }
}

ImU32 CPlayer::getRoleColor()
{
    switch (getTeam())
    {
        case breachTeam::Scp:
        {
            return IM_COL32(200, 0, 0, 255);
        }
        case breachTeam::Chaos: 
        {
            return IM_COL32(0, 150, 0, 255);
        }
        case breachTeam::Mtf:
        {
            return IM_COL32(0, 100, 200, 255);
        }
        case None:
        {
            return IM_COL32(100, 100, 100, 255);
        }
    }
}

#pragma once

class CPlayer
{
public:
	unsigned int m_id;         // 0x00
	float m_x;                 // 0x04
	float m_y;                 // 0x08
	float m_z;                 // 0x0C
	float m_yaw;               // 0x10
	float m_bonePitch;         // 0x14
    char pad_0001[0x64];
	float m_blinkTimer;        // 0x7C
    char pad_0002[0x04];
    int m_isDead;              // 0x84
    char pad_0003[0x44];
    unsigned int m_breachType; // 0xCC
    char pad_0004[0x0C];
    int m_forceMove;           // 0xDC
    char pad_0005[0x38];
    float m_health;            // 0x118
};

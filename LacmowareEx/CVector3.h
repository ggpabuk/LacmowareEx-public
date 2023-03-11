#pragma once

class CVector3 final
{
public:
    static float distance(CVector3 *vec1, CVector3 *pos2);
    float distance(CVector3 *destination);

	float m_x;
	float m_y;
	float m_z;
};

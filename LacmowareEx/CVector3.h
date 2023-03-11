#pragma once

class CVector3 final
{
public:
    CVector3();
    CVector3(float x, float y, float z);

    float distance(CVector3 *destination);
    static float distance(CVector3 *vec1, CVector3 *pos2);

	float m_x;
	float m_y;
	float m_z;
};

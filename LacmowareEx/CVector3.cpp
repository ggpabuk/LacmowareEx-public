#include "pch.h"
#include "CVector3.h"
#include <cmath>

CVector3::CVector3()
{
}

CVector3::CVector3(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

float CVector3::distance(CVector3 *vec1, CVector3 *pos2)
{
    return std::sqrt(
        std::pow((pos2->m_x - vec1->m_x), 2) +
        std::pow((pos2->m_y - vec1->m_y), 2) +
        std::pow((pos2->m_z - vec1->m_z), 2)
    );
}

float CVector3::distance(CVector3 *destination)
{
    return distance(this, destination);
}

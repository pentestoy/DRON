/**
 *  Utility/DXutil.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include "DXUtil.hpp"

/*
float DistanceXY(D3DXVECTOR2 v1, D3DXVECTOR2 v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrt(dx * dx + dy * dy);
}

float DistanceXY(D3DXVECTOR2 v1, D3DXVECTOR3 v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrt(dx * dx + dy * dy);
}

float DistanceXY(D3DXVECTOR3 v1, D3DXVECTOR2 v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrt(dx * dx + dy * dy);
}

/**
 *  For two vectors V1 and V2:
 *  V1 dot V2 = length(V1)*length(V2)*cos(angle)
 *  We can use this to determine parallelity. cos(angle) should be 1 for true
 *  parallelity. We return true if it's > 0.9998 to account for floating point
 *  errors.
 * /
bool AreParallel( const D3DXVECTOR3& v1, const D3DXVECTOR3& v2 )
{
    if( ( D3DXVec3Dot(&v1, &v2) /
        ( D3DXVec3Length(&v1) * D3DXVec3Length(&v2) ) )
        > 0.998 )
        return true;

    return false;
}
*/
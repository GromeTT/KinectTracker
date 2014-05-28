#include "../Inc/Intersection.h"

bool pointInCube( const float x,
                  const float y,
                  const float z,
                  const float cubeX,
                  const float cubeY,
                  const float cubeZ,
                  const float width,
                  const float height,
                  const float depth )
{
    float d = width / 2;
    float minW = cubeX - d;
    float maxW = cubeX + d;
    if ( x < minW || x > maxW )
    {
        return false;
    }
    d = height / 2;
    float minH = cubeY - d;
    float maxH = cubeY + d;
    if ( y < minH || y > maxH )
    {
        return false;
    }
    d = depth / 2;
    float minD = cubeZ - d;
    float maxD = cubeZ + d;
    if ( z < minD || z > maxD )
    {
        return false;
    }

    return true;
}

#include "../inc/AMath.h"

float AMath::radToDegF(const float rad)
{
    return rad*factorRadianToDegree;
}

double AMath::radToDegD(const double rad)
{
    return rad*factorRadianToDegree;
}

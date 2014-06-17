#ifndef DEFINES_H
#define DEFINES_H

#include <QObject>

const float PI = 3.14159265359f;
const float factorRadianToDegree = 180/PI;

struct FixedPropertyVector
{
    unsigned int channelCount;
    std::vector<float> vec;
};

Q_DECLARE_METATYPE( FixedPropertyVector )


#endif // DEFINES_H

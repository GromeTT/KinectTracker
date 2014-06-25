#ifndef DEFINES_H
#define DEFINES_H

#include <QObject>

struct FixedPropertyVector
{
    unsigned int channelCount;
    std::vector<float> vec;
};

Q_DECLARE_METATYPE( FixedPropertyVector )


#endif // DEFINES_H

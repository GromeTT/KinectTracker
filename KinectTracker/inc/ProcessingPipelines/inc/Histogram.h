#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "ProcessingComponent.h"
#include <opencv2/opencv.hpp>

class Histogram : public ProcessingComponent
{
    Q_OBJECT

public:
    Histogram();
    virtual ~Histogram();

private:
    int     m_numberOfBins;
};

#endif // HISTOGRAM_H

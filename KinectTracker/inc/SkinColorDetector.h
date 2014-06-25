#ifndef SKINDETECTOR_H
#define SKINDETECTOR_H

#include <QSharedPointer>
#include "opencv2/opencv.hpp"
#include "ProcessingComponent.h"
#include "InRange.h"

class SkinColorDetector : public ProcessingComponent
{
    Q_OBJECT

public:
    SkinColorDetector();
    ~SkinColorDetector();

    void detect( cv::Mat& img );
    void setBins( const int bins );

    int bins() const;

private:
    int        m_bins;
    cv::Mat    m_hue;
    InRangePtr mp_inRange;

signals:
    void binsChanged();

private:
    Q_PROPERTY( int bins MEMBER m_bins
                READ bins
                WRITE setBins
                NOTIFY binsChanged )
};

typedef QSharedPointer<SkinColorDetector> SkinColorDetectorPtr;

#endif // SKINDETECTOR_H

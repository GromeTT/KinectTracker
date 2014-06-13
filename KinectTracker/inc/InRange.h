#ifndef INRANGE_H
#define INRANGE_H

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include "ProcessingComponent.h"

class InRange : public ProcessingComponent
{
    Q_OBJECT

public:
    InRange();
    ~InRange();

//    void inRange( cv::InputArray& src,
//                  cv::OutputArray& dst,
//                  const int channels );

};

typedef QSharedPointer<InRange> InRangePtr;

#endif // INRANGE_H

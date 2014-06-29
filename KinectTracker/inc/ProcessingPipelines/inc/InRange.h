#ifndef INRANGE_H
#define INRANGE_H

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include "ProcessingComponent.h"
#include "../../PropertyBrowser/inc/FixedPropertyVector.h"

class InRange : public ProcessingComponent
{
    Q_OBJECT

public:
    InRange( const int channelCount,
             QObject* parent = nullptr );
    ~InRange();

    void process( cv::InputArray& input,
                  cv::OutputArray& output );
    void setLowerBounds( const FixedPropertyVector& lowerBounds );
    void setUpperBounds( const FixedPropertyVector& upperBounds );

    const FixedPropertyVector& lowerBounds() const;
    const FixedPropertyVector& upperBounds() const;

private:
    FixedPropertyVector     m_lowerBounds;
    FixedPropertyVector     m_upperBounds;

signals:
    void lowerBoundsChanged();
    void upperBoundsChanged();

private:
    Q_PROPERTY( FixedPropertyVector lowerBounds MEMBER m_lowerBounds
                READ lowerBounds
                WRITE setLowerBounds
                NOTIFY lowerBoundsChanged )

    Q_PROPERTY( FixedPropertyVector upperBounds MEMBER m_upperBounds
                READ upperBounds
                WRITE setUpperBounds
                NOTIFY upperBoundsChanged )
};

typedef QSharedPointer<InRange> InRangePtr;

#endif // INRANGE_H

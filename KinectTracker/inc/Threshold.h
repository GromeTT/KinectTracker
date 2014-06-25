#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include "ProcessingComponent.h"

class Threshold : public ProcessingComponent
{
    Q_OBJECT

public:
    enum ThresholdType
    {
        Thresh_Binary = cv::THRESH_BINARY,
        Thresh_Binary_Inv = cv::THRESH_BINARY_INV,
        Thresh_Trunc = cv::THRESH_TRUNC,
        Thresh_ToZero = cv::THRESH_TOZERO,
        Thresh_ToZero_Inv = cv::THRESH_TOZERO_INV
    };

    Q_ENUMS( ThresholdType )

public:
    Threshold( QObject* parent = nullptr );
    virtual ~Threshold();

    void threshold( cv::Mat& input );
    void threshold( cv::Mat& input, cv::Mat& output );

    void setMaxValue( const float maxValue );
    void setThreshold( const float threshold );
    void setThresholdType( const ThresholdType thresholdType );

    float         maxValue() const;
    float         threshold() const;
    ThresholdType thresholdType() const;

signals:
    void maxValueChanged();
    void thresholdChanged();
    void thresholdTypeChanged();

private:
    double          m_maxValue;
    double          m_threshold;
    ThresholdType   m_thresholdType;

    Q_PROPERTY( double maxValue MEMBER m_maxValue
                READ maxValue
                WRITE setMaxValue
                NOTIFY maxValueChanged )

    Q_PROPERTY( double threshold MEMBER m_threshold
                READ threshold
                WRITE setThreshold
                NOTIFY thresholdChanged )

    Q_PROPERTY( ThresholdType thresholdType MEMBER m_thresholdType
                READ thresholdType
                WRITE setThresholdType
                NOTIFY thresholdTypeChanged )

};

typedef QSharedPointer<Threshold> ThresholdPtr;

#endif // THRESHOLD_H

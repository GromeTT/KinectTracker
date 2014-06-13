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
//    enum
//    {
//        Adaptive_Thresh_Mean = cv::ADAPTIVE_THRESH_MEAN_C,
//        Adaptive_Thresh_Gaussian_C = cv::ADAPTIVE_THRESH_GAUSSIAN_C
//    }AdaptiveMode;

    enum ThresholdType
    {
        // http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html?highlight=threshold#double%20threshold%28InputArray%20src,%20OutputArray%20dst,%20double%20thresh,%20double%20maxval,%20int%20type%29
        Thresh_Binary = cv::THRESH_BINARY,
        Thresh_Binary_Inv = cv::THRESH_BINARY_INV,
        Thresh_Trunc = cv::THRESH_TRUNC,
        Thresh_ToZero = cv::THRESH_TOZERO,
        Thresh_ToZero_Inv = cv::THRESH_TOZERO_INV
    };

//    Q_ENUMS( AdaptiveMode )
    Q_ENUMS( ThresholdType )

public:
    Threshold( QObject* parent = nullptr );
    virtual ~Threshold();

    void threshold( cv::Mat& input );
    void threshold( cv::Mat& input, cv::Mat& output );

    void setMaxValue( const float maxValue );
//    void setAdaptiveMode( const AdaptiveMode adaptiveMode );
    void setThreshold( const float threshold );
    void setThresholdType( const ThresholdType thresholdType );
//    void setBlockSize( const int blockSize );

    float         maxValue() const;
    float         threshold() const;
//    AdaptiveMode  adaptiveMode() const;
    ThresholdType thresholdType() const;
//    int           blockSize() const;

signals:
    void maxValueChanged();
    void thresholdChanged();
//    void adaptiveModeChanged();
    void thresholdTypeChanged();
//    void blockSizeChanged();

private:
    float           m_maxValue;
    float           m_threshold;
//    AdaptiveMode    m_adaptiveMode;
    ThresholdType   m_thresholdType;
//    int             m_blockSize;

    Q_PROPERTY( float maxValue MEMBER m_maxValue
                READ maxValue
                WRITE setMaxValue
                NOTIFY maxValueChanged )
//    Q_PROPERTY( AdaptiveMode adaptiveMode MEMBER m_adaptiveMode
//                READ adaptiveMode
//                WRITE setAdaptiveMode
//                NOTIFY adaptiveModeChanged )
    Q_PROPERTY( float threshold MEMBER m_threshold
                READ threshold
                WRITE setThreshold
                NOTIFY thresholdChanged )
    Q_PROPERTY( ThresholdType thresholdType MEMBER m_thresholdType
                READ thresholdType
                WRITE setThresholdType
                NOTIFY thresholdTypeChanged )
//    Q_PROPERTY( int blockSize MEMBER m_blockSize
//                READ blockSize
//                WRITE setBlockSize
//                NOTIFY blockSizeChanged )
};

typedef QSharedPointer<Threshold> ThresholdPtr;

#endif // THRESHOLD_H

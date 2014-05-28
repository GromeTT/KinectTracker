#include "../inc/Threshold.h"


Threshold::Threshold()
    : m_maxValue( 1 )
    , m_threshold( 0.5 )
    , m_thresholdType( Thresh_ToZero )
{
    setObjectName( "Threshold" );
}

Threshold::~Threshold()
{

}

void Threshold::threshold(cv::Mat& input)
{
    cv::threshold( input, input, m_threshold, m_maxValue, m_thresholdType );
}

void Threshold::threshold(cv::Mat& input, cv::Mat& output)
{
    cv::threshold( input, output, m_threshold, m_maxValue, m_thresholdType );
}

void Threshold::setMaxValue(const float maxValue)
{
    if ( m_maxValue != maxValue )
    {
        m_maxValue = maxValue;
        emit maxValueChanged();
    }
}

void Threshold::setThreshold ( const float threshold )
{
    if( m_threshold != threshold )
    {
        m_threshold = threshold;
        emit thresholdChanged();
    }
}

//void Threshold::setAdaptiveMode(const Threshold::AdaptiveMode adaptiveMode)
//{
//    if ( m_adaptiveMode != adaptiveMode )
//    {
//        m_adaptiveMode = adaptiveMode;
//        emit adaptiveModeChanged();
//    }
//}

void Threshold::setThresholdType(const Threshold::ThresholdType thresholdType)
{
    if ( m_thresholdType != thresholdType )
    {
        m_thresholdType = thresholdType;
        emit thresholdTypeChanged();
    }
}

//void Threshold::setBlockSize(const int blockSize)
//{
//    if ( m_blockSize != blockSize )
//    {
//        m_blockSize = blockSize;
//        emit blockSizeChanged();
//    }
//}

float Threshold::maxValue() const
{
    return m_maxValue;
}

float Threshold::threshold() const
{
    return m_threshold;
}

//Threshold::AdaptiveMode Threshold::adaptiveMode() const
//{
//    return m_adaptiveMode;
//}

Threshold::ThresholdType Threshold::thresholdType() const
{
    return m_thresholdType;
}

//int Threshold::blockSize() const
//{
//    return m_blockSize;
//}

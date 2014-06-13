#include "../Inc/Dilate.h"
#include <opencv2/opencv.hpp>

Dilate::Dilate( QObject* parent )
    : ProcessingComponent( parent )
    , m_anchorPointX( 1 )
    , m_anchorPointY( 1 )
    , m_iterations( 1 )
{
    setObjectName( "Dilate" );
}

Dilate::~Dilate()
{
}

void Dilate::dilate( cv::Mat& input )
{
    cv::dilate( input,
                input,
                cv::Mat(),
                cv::Point( m_anchorPointX, m_anchorPointY ),
                m_iterations );
}

void Dilate::dilate( cv::Mat& input, cv::Mat& output )
{
    cv::dilate( input,
                output,
                cv::Mat(),
                cv::Point( m_anchorPointX, m_anchorPointY ),
                m_iterations );
}

float Dilate::anchorPointX() const
{
    return m_anchorPointX;
}

float Dilate::anchorPointY() const
{
    return m_anchorPointY;
}

int Dilate::iterations() const
{
    return m_iterations;
}

int Dilate::kernelRowCount() const
{
    return m_kernelRowCount;
}

int Dilate::kernelColumnCount() const
{
    return m_kernelColumnCount;
}

void Dilate::setAnchorPointX( const float x )
{
    if ( m_anchorPointX != x )
    {
        m_anchorPointX = x;
        emit anchorPointXChanged();
    }
}

void Dilate::setAnchorPointY( const float y )
{
    if ( m_anchorPointY != y )
    {
        m_anchorPointY = y;
        emit anchorPointYChanged();
    }
}

void Dilate::setIterations( const float iterations )
{
    if ( m_iterations != iterations )
    {
        m_iterations = iterations;
        emit iterationsChanged();
    }
}

void Dilate::setKernelRowCount(const int rowCount)
{
    if ( m_kernelRowCount != rowCount )
    {
        m_kernelRowCount = rowCount;
        emit kernelRowCountChanged();
    }
}

void Dilate::setKernelColumnCount(const int columnCount)
{
    if ( m_kernelColumnCount != columnCount )
    {
        m_kernelColumnCount = columnCount;
        emit kernelColumnCountChanged();
    }
}

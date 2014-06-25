#include "../inc/Erode.h"


Erode::Erode( QObject* parent )
    : ProcessingComponent( parent )
    , m_anchorPointX( 1 )
    , m_anchorPointY( 1 )
    , m_iterations( 1 )
    , m_kernelRowCount( 0 )
    , m_kernelColumnCount( 0 )
{
    setObjectName( "Erode" );
}

Erode::~Erode()
{
}

void Erode::erode( cv::Mat& input )
{
    cv::Mat element = cv::getStructuringElement( cv::MORPH_ELLIPSE,
                                                 cv::Size( 2*m_kernelRowCount + 1, 2*m_kernelRowCount+1 ),
                                                 cv::Point( m_kernelRowCount, m_kernelRowCount ) );

    cv::erode( input,
               input,
               element );
}

void Erode::erode(cv::Mat& input, cv::Mat& output)
{
    cv::Mat element = cv::getStructuringElement( cv::MORPH_CLOSE,
                                                 cv::Size( 2*m_kernelRowCount + 1, 2*m_kernelRowCount+1 ),
                                                 cv::Point( m_kernelRowCount, m_kernelRowCount ) );
    cv::erode( input,
               output,
               element );
}

float Erode::anchorPointX() const
{
    return m_anchorPointX;
}

float Erode::anchorPointY() const
{
    return m_anchorPointY;
}

int Erode::iterations() const
{
    return m_iterations;
}

int Erode::kernelRowCount() const
{
    return m_kernelRowCount;
}

int Erode::kernelColumnCount() const
{
    return m_kernelColumnCount;
}

void Erode::setAnchorPointX( const float x )
{
    if ( m_anchorPointX != x )
    {
        m_anchorPointX = x;
        emit anchorPointXChanged();
    }
}

void Erode::setAnchorPointY( const float y )
{
    if ( m_anchorPointY != y )
    {
        m_anchorPointY = y;
        emit anchorPointYChanged();
    }
}

void Erode::setIterations( const float iterations )
{
    if ( m_iterations != iterations )
    {
        m_iterations = iterations;
        emit iterationsChanged();
    }
}

void Erode::setKernelRowCount(const int rowCount)
{
    if ( m_kernelRowCount != rowCount )
    {
        m_kernelRowCount = rowCount;
        emit kernelRowCountChanged();
    }
}

void Erode::setKernelColumnCount(const int columnCount)
{
    if ( m_kernelColumnCount != columnCount )
    {
        m_kernelColumnCount = columnCount;
        emit kernelColumnCountChanged();
    }
}

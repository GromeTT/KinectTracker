#include "../inc/DepthProcessingPipeline.h"
#include <QDebug>
#include <QSize>


DepthProcessingPipeline::DepthProcessingPipeline( QObject* parent )
    : QObject( parent )
    , m_threshold( 2000 )
    , m_minContourSize( 1000 )
{
    setObjectName( "DepthProcessingPipeline" );
//    cv::SimpleBlobDetector::Params params;
//    params.filterByArea = true;
//    params.minArea = 5;
//    params.maxArea = 3200;
//    params.filterByColor = false;
//    params.blobColor = 255;

//    m_blobDetector = new cv::SimpleBlobDetector( params );
//    m_blobDetector->create( "SimpleBlob" );
//    Q_ASSERT( !m_blobDetector.empty() );
}

DepthProcessingPipeline::~DepthProcessingPipeline()
{

}

void DepthProcessingPipeline::process( ushort* depthImage,
                                       ushort* screenshot,
                                       const float size )
{
    // Calculate the absolute difference between currentImage and
    // screenshot.
    std::vector<uchar> dif ( size );
    for ( int i = 0; i < size; ++i )
    {
        int d = depthImage[i] - screenshot[i];
        d = abs( d );
        if ( d > m_threshold )
        {
            dif[i] = 255;
        }
        else
        {
            dif[i] = 0;
        }
    }
    cv::Mat difImage( 480, 640, CV_8UC1, dif.data() );
//    cv::fastNlMeansDenoisingMulti( difImage, difImage, 0 );
    cv::Mat colorImg;
    cv::cvtColor( difImage, colorImg, CV_GRAY2RGB );
    cv::imshow( "Color", colorImg  );
    cv::findContours( difImage, contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point( 0, 0 ) );
    int indexLargestContour = 0;
    double largestArea = 0;
    for ( int i = 0; i < contours.size(); ++ i )
    {
        double area = cv::contourArea( contours[i], false );
        if ( area > largestArea )
        {
            largestArea = area;
            indexLargestContour = i;
        }
    }
    cv::Scalar color = cv::Scalar( 255, 0, 0 );
    drawContours( colorImg, contours, indexLargestContour, color, 2, 8, hierarchy, 0, cv::Point() );
    cv::rectangle( colorImg, cv::boundingRect( contours[indexLargestContour]), cv::Scalar( 0, 0, 255 ) );
    cv::imshow( "Thresholded difference", colorImg  );
}

void DepthProcessingPipeline::setThreshold( const int threshold )
{
    m_threshold = threshold;
}

void DepthProcessingPipeline::setMinContourSize( const int size )
{
    m_minContourSize = size;
    emit minContourSizeChanged();
}

QVector<ProcessingComponent*>& DepthProcessingPipeline::getComponents()
{
    return m_processingComponents;
}

int DepthProcessingPipeline::threshold() const
{
    return m_threshold;
}

int DepthProcessingPipeline::minContourSize() const
{
    return m_minContourSize;
}

#include "../inc/HighLevelProcessingPipeline.h"
#include "../inc/BBMovementAnalyzer.h"
#include "../inc/UpperBodySizeAnalyzer.h"
#include "../inc/BBSizeAnalyzer.h"
#include <QVector2D>
#include <opencv2/opencv.hpp>

HighLevelProcessingPipeline::HighLevelProcessingPipeline( KinectPtr& kinect,
                                                          LowLevelProcessingPipeline* rbgProcessingPipeline,
                                                          DepthProcessingPipeline* depthProcessingPipeline,
                                                          QObject* parent )
    : QObject( parent )
    , m_kinect( kinect )
    , m_rgbProcessingPipeline( rbgProcessingPipeline )
    , m_depthProcessingPipeline( depthProcessingPipeline )
    , m_movementAnalyzer( new BBMovementAnalyzer )
    , m_sizeAnalyzer( new BBSizeAnalyzer )
    , m_skeletonAnalyzer( new SkeletonAnalyzer )
{
    setObjectName( "MovementAnalyzer" );
    // Initialize depth  arrays.
    m_depthSize = kinect->depthStreamResolution().width() * kinect->depthStreamResolution().height();
    mp_depthData = new ushort[m_depthSize];
    mp_depthScrennshot = new ushort[m_depthSize];
    // Initialize rgb arrays.
    m_rgbSize = kinect->rgbStreamResolution().width() * kinect->rgbStreamResolution().height() * 3;
    mp_rgbData = new uchar [m_rgbSize];
    mp_rgbScreenshot = new uchar [m_rgbSize];
}

HighLevelProcessingPipeline::~HighLevelProcessingPipeline()
{

}

/*!
   \brief HighLevelProcessingPipeline::process
   Process the RGB, depth and skeleton data.
 */
void HighLevelProcessingPipeline::process( const unsigned int timestamp )
{
    m_skeletons.clear();

    // Get data from the kinect sensor.
    HRESULT res;
    res = m_kinect->getDepthImage( mp_depthData );
    if ( res != S_OK )
    {
        return;
    }
    res = m_kinect->getRGBImage( mp_rgbData );
    if ( res != S_OK )
    {
        return;
    }
    res = m_kinect->getSkeleton( m_skeletons );
    if ( res != S_OK )
    {
        return;
    }
    // Process the data.
    processV( timestamp );
}

/*!
   \brief HighLevelProcessingPipeline::rgbImage
   Returns the rgb image.
 */
uchar* HighLevelProcessingPipeline::rgbImage() const
{
    return mp_rgbData;
}

/*!
   \brief HighLevelProcessingPipeline::depthImage
   Returns the depth image.
 */
ushort*HighLevelProcessingPipeline::depthImage() const
{
    return mp_depthData;
}

/*!
   \brief HighLevelProcessingPipeline::skeletonData
   Returns the skeleton data.
 */
SkeletonDataPtr HighLevelProcessingPipeline::skeletonData() const
{
    if ( m_skeletons.size() > 0 )
    {
        return m_skeletons.at( 0 );
    }
    return SkeletonDataPtr( nullptr );
}

/*!
   \brief HighLevelProcessingPipeline::rgbProcessingPipeline
   Returns the RGBProcessingPipeline.
 */
LowLevelProcessingPipelinePtr HighLevelProcessingPipeline::rgbProcessingPipeline() const
{
    return m_rgbProcessingPipeline;
}

/*!
   \brief HighLevelProcessingPipeline::depthProcessingPipeline
   Returns the DepthProcessingPipeline.
 */
DepthProcessingPipelinePtr HighLevelProcessingPipeline::depthProcessingPipeline() const
{
    return m_depthProcessingPipeline;
}

/*!
   \brief HighLevelProcessingPipeline::movementAnalyzer
   Returns the MovementAnalyzer.
 */
MovementAnalyzerPtr HighLevelProcessingPipeline::movementAnalyzer() const
{
    return m_movementAnalyzer;
}

/*!
   \brief HighLevelProcessingPipeline::sizeAnalyzer
   Returns the SizeAnalyzer.
 */
SizeAnalyzerPtr HighLevelProcessingPipeline::sizeAnalyzer() const
{
    return m_sizeAnalyzer;
}

/*!
   \brief HighLevelProcessingPipeline::takeScreenShot
   Makes a copy of the current depth and rgb Data.
 */
void HighLevelProcessingPipeline::takeScreenShot()
{
    std::memcpy( mp_depthScrennshot, mp_depthData, m_depthSize * sizeof( ushort ) );
    std::memcpy( mp_rgbScreenshot, mp_rgbData, m_rgbSize * sizeof( uchar ) );
}

/*!
   \brief HighLevelProcessingPipeline::drawRegionOfInterest
 */
void HighLevelProcessingPipeline::drawRegionOfInterest()
{
    const QVector<QVector3D> regionOfInterest = m_skeletonAnalyzer->regionOfInterest();
    QVector2D p1 = transformFromSkeltonToRGB( regionOfInterest.at( 0 ) ); // Top right
    QVector2D p2 = transformFromSkeltonToRGB( regionOfInterest.at( 2 ) ); // Bottom left
    cv::Scalar color ( 0, 255, 255 );
    cv::Mat curr ( m_kinect->rgbStreamResolution().height(),
                   m_kinect->rgbStreamResolution().width(),
                   CV_8UC3,
                   mp_rgbData );
    rectangle( curr, cv::Point( p1.x(), p1.y() ), cv::Point( p2.x(), p2.y() ), color, 5 );
}

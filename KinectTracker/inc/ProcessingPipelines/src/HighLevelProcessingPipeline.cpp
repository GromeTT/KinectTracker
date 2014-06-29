#include "../inc/HighLevelProcessingPipeline.h"
#include "../../Analyzer/inc/BBMovementAnalyzer.h"
#include "../../Analyzer/inc/UpperBodySizeAnalyzer.h"
#include "../../Analyzer/inc/BBSizeAnalyzer.h"
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
   \brief HighLevelProcessingPipeline::saveHeadHistograms
   Saves the current histograms for comparison.
 */
void HighLevelProcessingPipeline::saveHeadHistograms()
{

}



/*!
   \brief HighLevelProcessingPipeline::drawRegionOfInterest
   Translates the region defined by \a rect from the 3D space to the rgb space
   and draws it.
 */
void HighLevelProcessingPipeline::drawRegionOfInterest( const AMath::Rectangle3D& rect,
                                                        cv::Mat& image,
                                                        const cv::Scalar& color )
{
    QVector2D p1 = transformFromSkeltonToRGB( rect.topLeftCorner() );
    QVector2D p2 = transformFromSkeltonToRGB( rect.bottomRightCorner() );
    rectangle( image,
               cv::Point( p1.x(), p1.y() ), cv::Point( p2.x(), p2.y() ),
               color,
               5 );
}

/*!
   \brief HighLevelProcessingPipeline::drawRegionOfInterest
   Draws a rectangle around \a center defined by \a width and \a height in \a image.
   Note that \a center has to be in rgb space.
 */
void HighLevelProcessingPipeline::drawRegionOfInterestWithAndHeightAsPixels( const QVector3D& center,
                                                                             const float width,
                                                                             const float height,
                                                                             cv::Mat& image,
                                                                             const cv::Scalar& color )
{
    rectangle( image,
               cv::Point( center.x() + width, center.y() + height ), cv::Point( center.x() - width, center.y() - height),
               color,
               5 );
}

/*!
   \brief HighLevelProcessingPipeline::drawRegionOfInterestWithAndHeightAsPixels
   Transforms the center point of \a rect into color space and passes it to
   HighLevelProcessingPipeline::drawRegionOfInterestWithAndHeightAsPixels

 */
void HighLevelProcessingPipeline::drawRegionOfInterestWithAndHeightAsPixels( const AMath::Rectangle3D& rect,
                                                                             cv:: Mat image,
                                                                             const cv::Scalar& color )
{
    drawRegionOfInterestWithAndHeightAsPixels( transformFromSkeltonToRGB( rect.center() ),
                                               rect.width(),
                                               rect.height(),
                                               image,
                                               color );
}

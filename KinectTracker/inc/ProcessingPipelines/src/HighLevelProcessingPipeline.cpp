#include "../inc/HighLevelProcessingPipeline.h"
#include "../../Analyzer/inc/BBMovementAnalyzer.h"
#include "../../Analyzer/inc/UpperBodySizeAnalyzer.h"
#include "../../Analyzer/inc/BBSizeAnalyzer.h"
#include <QVector2D>
#include <QColor>
#include <QDebug>
#include <opencv2/opencv.hpp>

HighLevelProcessingPipeline::HighLevelProcessingPipeline( KinectPtr& kinect,
                                                          LowLevelProcessingPipeline* rbgProcessingPipeline,
                                                          DepthProcessingPipeline* depthProcessingPipeline,
                                                          QObject* parent )
    : QObject( parent )
    , m_kinect( kinect )
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

    m_rgbProcessingPipelines.append( LowLevelProcessingPipelinePtr( rbgProcessingPipeline ) );
}

HighLevelProcessingPipeline::~HighLevelProcessingPipeline()
{

}

/*!
   \brief HighLevelProcessingPipeline::process
   Process the RGB, depth and skeleton data.
 */
bool HighLevelProcessingPipeline::process( const unsigned int timestamp )
{
    m_skeletons.clear();

    // Get data from the kinect sensor.
    HRESULT res;
    res = m_kinect->getDepthImage( mp_depthData );
    if ( res != S_OK )
    {
        return false;
    }
    res = m_kinect->getRGBImage( mp_rgbData );
    if ( res != S_OK )
    {
        return false;
    }
    res = m_kinect->getSkeleton( m_skeletons );
    if ( res != S_OK )
    {
        return false;
    }
    // Process the data.
    processV( timestamp );
    return true;
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
   \brief HighLevelProcessingPipeline::processingPipelines
   Returns a list of all RGBPipelines registered.
 */
QList<LowLevelProcessingPipelinePtr>& HighLevelProcessingPipeline::rgbProcessingPipelines()
{
    return m_rgbProcessingPipelines;
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
   \brief HighLevelProcessingPipeline::skeletonAnalyzer
   Returns the skeletonanlyzer.
 */
SkeletonAnalyzerPtr HighLevelProcessingPipeline::skeletonAnalyzer() const
{
    return m_skeletonAnalyzer;
}

/*!
   \brief HighLevelProcessingPipeline::skeletonDataAvailable
 */
bool HighLevelProcessingPipeline::skeletonDataAvailable() const
{
    return m_skeletonDataAvailable;
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
   Draws \a rect into \a image with \a color.
   Note that the region has to be croped.
 */
void HighLevelProcessingPipeline::drawRegionOfInterest( const QRect& rect,
                                                        cv::Mat image,
                                                        const QColor& color )
{
    // Draw the reactangle only if the it's width and height
    // is greater then 0.
    if ( rect.width() > 0 && rect.height() > 0 )
    {
        rectangle( image,
                   cv::Point( rect.bottomRight().x(), rect.bottomRight().y() ),
                   cv::Point( rect.topLeft().x(), rect.topLeft().y() ),
                   cv::Scalar( color.blue(), color.green(), color.red() ),
                   1 );
    }
}

/*!
   \brief HighLevelProcessingPipeline::reset
 */
void HighLevelProcessingPipeline::reset()
{
    m_sizeAnalyzer->reset();
    m_movementAnalyzer->reset();
    resetV();
}

/*!
   \brief HighLevelProcessingPipeline::crop
   Corps \a rect, so that it fits into \a image.
 */
QRect HighLevelProcessingPipeline::crop( const AMath::Rectangle3D& rect,
                                         cv::Mat& image )
{
    QPoint topLeft = transformFromSkeltonToRGB( rect.topLeftCorner() );
    if ( topLeft.x() < 0 )
    {
        topLeft.setX( 0 );
    }
    if ( topLeft.y() < 0 )
    {
        topLeft.setY( 0 );
    }
    QPoint bottomRight = transformFromSkeltonToRGB( rect.bottomRightCorner() );
    if ( bottomRight.x() >= image.cols )
    {
        bottomRight.setX( image.cols - 1 );
    }
    if ( bottomRight.y() >= image.rows )
    {
        bottomRight.setY( image.rows - 1 );
    }
    return QRect( topLeft, bottomRight );
}

/*!
   \brief HighLevelProcessingPipeline::cropRegionWithWidthAndHeightAsPixels
   \overload HighLevelProcessingPipeline::cropRegionWithWidthAndHeightAsPixels(QPoint &center, const float width, const float height, cv::Mat &image)
 */
QRect HighLevelProcessingPipeline::cropRegionWithWidthAndHeightAsPixels( const QRect& rect,
                                                                         const cv::Mat& image)
{
    return cropRegionWithWidthAndHeightAsPixels( rect.center(),
                                                 rect.width(),
                                                 rect.height(),
                                                 image );
}

/*!
   \brief HighLevelProcessingPipeline::cropRegionWithWidthAndHeightAsPixels
   Crops the rectangle descibed by \a center, \a width and \a height so that it
   fits into \a image.
 */
QRect HighLevelProcessingPipeline::cropRegionWithWidthAndHeightAsPixels( const QPoint& center,
                                                                         const float width,
                                                                         const float height,
                                                                         const cv::Mat& image )
{
    // Compute top left point.
    QPoint topLeft ( center.x() - width + 1 ,
                     center.y() - height + 1 );
    if ( topLeft.x() < 0  )
    {
        topLeft.setX( 0 );
    }
    if ( topLeft.x() > image.cols )
    {
        topLeft.setX( image.cols -1 );
    }
    if ( topLeft.y() < 0 )
    {
        topLeft.setY( 0 );
    }
    if ( topLeft.y() > image.rows )
    {
        topLeft.setY( image.rows-1 );
    }

    // Compute bottom right point.
    QPoint bottomRight ( center.x() + width,
                         center.y() + height );

    if ( bottomRight.x() > image.cols )
    {
        bottomRight.setX( image.cols - 1 );
        if ( bottomRight.x() < topLeft.x() )
        {
            bottomRight.setX( topLeft.x() );
        }
    }
    if ( bottomRight.x() < 0 )
    {
        bottomRight.setX( 0 );
    }

    if ( bottomRight.y() > image.rows )
    {
        bottomRight.setY( image.rows - 1 );
        if ( bottomRight.y() < topLeft.y() )
        {
            bottomRight.setY( topLeft.y() );
        }
    }
    if ( bottomRight.y() < 0 )
    {
        bottomRight.setY( 0 );
    }

    // Return rect.
    return QRect( topLeft, bottomRight );
}

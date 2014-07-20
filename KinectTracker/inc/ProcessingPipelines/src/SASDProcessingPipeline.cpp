#include "../inc/SASDProcessingPipeline.h"
#include "../../Analyzer/inc/SkeletonAnalyzer.h"
#include <QVector2D>
#include <QDebug>

using namespace std;
using namespace cv;

/*!
  \class
  This pipeline performs an analysis based on the skeleton data
  and it uses skin detection to extract informations if the skeleton
  data is broken or the quality insufficient.
*/

/*!
   \brief SASDProcessingPipeline::SASDProcessingPipeline
   Constructs a SASDProcessingPipeline.
 */
SASDProcessingPipeline::SASDProcessingPipeline( KinectPtr& kinect,
                                                QObject* parent )
    : HighLevelProcessingPipeline( kinect,
                                   new SkinColorExplicitDefinedSkinRegionDetectionPipeline,
                                   new DepthProcessingPipeline,
                                   parent )
    , m_skinPipeline( new SkinColorExplicitDefinedSkinRegionDetectionPipeline )
    , m_skinColorHistogramDetectionPipeline( new SkinColorHistogramDetectionPipeline )
    , mp_deriveViewingDirectionFunc( &SASDProcessingPipeline::deriveViewingDirectionBySkinColor )
{
    setObjectName( "SASDProcessingPipeline" );
    m_rgbProcessingPipelines.append( m_skinColorHistogramDetectionPipeline );
}

/*!
   \brief SASDProcessingPipeline::~SASDProcessingPipeline
   Destroyes the object.
 */
SASDProcessingPipeline::~SASDProcessingPipeline()
{
}

/*!
   \brief SASDProcessingPipeline::processV
   \see HighLevelProcessingPipeline::process()
 */
void SASDProcessingPipeline::processV( const unsigned int timestamp )
{
    if ( !processSkeletonData( timestamp ) )
    {
        // case: Analysis of the skeleton data failed.
        //       Make use of the rgb data for the analysis.

        // Not necessary yet.
//        processRGBData();
    }
}

void SASDProcessingPipeline::resetV()
{
    m_skinColorHistogramDetectionPipeline->reset();
}

/*!
   \brief SASDProcessingPipeline::processSkeletonData
   Process the skeleton data and store the results into \a results.
 */
bool SASDProcessingPipeline::processSkeletonData( const unsigned int timestamp )
{
    cv::Mat currentImage ( m_kinect->rgbStreamResolution().height(),
                           m_kinect->rgbStreamResolution().width(),
                           CV_8UC3,
                           mp_rgbData );
    m_regions.clear();
    if ( m_skeletons.count() <= 0 ||
         !m_skeletonAnalyzer->update( m_skeletons.at( 0 ), timestamp ) )
    {
        // case: Insufficient data for further analysis.
        //       Pass this information to the movementAnalyzer,
        //       so that the visualizer knows that it doesn't
        //       have to paint.
        m_movementAnalyzer->setDataAvailable( false );
        m_sizeAnalyzer->reset();
        m_sizeAnalyzer->setWorkerStatus( tr( "Nothing detected.") );
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              Qt::red );
        return false;
    }
    else
    {
        // case: The data provided by the skeleton are of good quality.
        //       Perform the further analysis on the skeleton data.
        m_movementAnalyzer->analyze( m_skeletons.at( 0 ), timestamp );
        m_sizeAnalyzer->analyze( m_kinect,  m_skeletons.at( 0 ) );

        m_lastRegion = crop( m_skeletonAnalyzer->regionOfInterest(), currentImage );
        extractAllRegions( currentImage );
        cv::Mat headRegion = m_regions.at( static_cast<int>( SkeletonData::Joints::Head ) ).m_subMatrix;
        // Derive the viewing direction.
        deriveViewingDirectionBySkinColor( headRegion );
        // Draw the regions of interest.
        drawRegionsOfInterest( currentImage );
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              Qt::red );
        return true;
    }
}

void SASDProcessingPipeline::extractAllRegions( Mat& image )
{
    extractRegion( image, SkeletonData::Joints::Hip );
    extractRegion( image, SkeletonData::Joints::Spine );
    extractRegion( image, SkeletonData::Joints::ShoulderCenter );
    extractRegion( image, SkeletonData::Joints::Head );
    extractRegion( image, SkeletonData::Joints::ShoulderLeft );
    extractRegion( image, SkeletonData::Joints::ElbowLeft );
    extractRegion( image, SkeletonData::Joints::WristLeft );
    extractRegion( image, SkeletonData::Joints::HandLeft );
    extractRegion( image, SkeletonData::Joints::ShoulderRight );
    extractRegion( image, SkeletonData::Joints::ElbowRight );
    extractRegion( image, SkeletonData::Joints::WristRight );
    extractRegion( image, SkeletonData::Joints::HandRight );
    extractRegion( image, SkeletonData::Joints::HipLeft );
    extractRegion( image, SkeletonData::Joints::KneeLeft );
    extractRegion( image, SkeletonData::Joints::AnkleLeft );
    extractRegion( image, SkeletonData::Joints::FootLeft );
    extractRegion( image, SkeletonData::Joints::HipRight );
    extractRegion( image, SkeletonData::Joints::KneeRight );
    extractRegion( image, SkeletonData::Joints::AnkleRight );
    extractRegion( image, SkeletonData::Joints::FootRight );
}

void SASDProcessingPipeline::extractRegion( Mat& image, SkeletonData::Joints joint )
{
    QVector3D centerSkeletonSpace = m_skeletons.at( 0 )->getJoint( joint );
    QPoint centerRGBSpace = transformFromSkeltonToRGB( centerSkeletonSpace ) ;
    QRect cropedRegion = cropRegionWithWidthAndHeightAsPixels( centerRGBSpace,
                                                               25,
                                                               25,
                                                               image );
    QColor color;
    if ( skeletonData()->jointTrackState( joint ) == SkeletonData::TrackState::Tracked )
    {
        color = Qt::green;
    }
    else
    {
        color = Qt::red;
    }
    qDebug() << "Image height " << image.rows;
    qDebug() << "Image width " << image.cols;
    qDebug() << "Joint "  << static_cast<int>( joint );
    qDebug() << "Top left x " << cropedRegion.topLeft().x();
    qDebug() << "Top left y " << cropedRegion.topLeft().y();
    qDebug() << "Bottom right x " << cropedRegion.bottomRight().x();
    qDebug() << "Bottom right y " << cropedRegion.bottomRight().y();
    qDebug() << "Width " << cropedRegion.width();
    qDebug() << "Height " << cropedRegion.height();
    Q_ASSERT( cropedRegion.x() >= 0 );
    Q_ASSERT( cropedRegion.y() >= 0 );
    Q_ASSERT( cropedRegion.width() >= 0 );
    Q_ASSERT( cropedRegion.height() >= 0 );
//    Q_ASSERT( cropedRegion.x() + cropedRegion.width() <= image.cols );
    qDebug() << "Bottom Right y " << cropedRegion.y() + cropedRegion.height();
//    Q_ASSERT( cropedRegion.y() + cropedRegion.height() <=  image.rows );

    m_regions.append( JointSummary( image( cv::Rect( cv::Point( cropedRegion.topLeft().x(),
                                                                cropedRegion.topLeft().y() ),
                                                     cv::Point( cropedRegion.bottomRight().x(),
                                                                cropedRegion.bottomRight().y() ) ) ),
                                    cropedRegion,
                                    joint,
                                    color ) );
}
/*!
   \brief SASDProcessingPipeline::processRGBData
   Processes the rgb data.
 */
void SASDProcessingPipeline::processRGBData()
{
    cv::Mat rgb ( m_kinect->rgbStreamResolution().height(),
                  m_kinect->rgbStreamResolution().width(),
                  CV_8UC3,
                  mp_rgbData );
    //    m_rgbProcessingPipeline->process( rgb );
}

void SASDProcessingPipeline::deriveViewingDirection( cv::Mat& image )
{
    // case: Not enough non zero pixels.

    // Iterate over the other joints to check if there is a region which contains
    // enough non zero pixels and can potentially the head.
    if ( (this->*mp_deriveViewingDirectionFunc)( image ) )
    {
        m_skeletonAnalyzer->setUserLooksTowardsCamera( true );
    }
    else
    {
        // case: No region contains enough non zero pixels to run count as
        //       front face.
        m_skeletonAnalyzer->setUserLooksTowardsCamera( false );
    }
}

/*!
   \brief SASDProcessingPipeline::analyzeViewingDirectionBySkinColor
   Uses the SkinColorExplicitDefinedSkinRegionDetectionPipeline to determine if the tracked person
   is lookin torwards the camera.
 */
bool SASDProcessingPipeline::deriveViewingDirectionBySkinColor( cv::Mat& head )
{
    m_skinPipeline->process( head );
    if ( m_skinPipeline->absoluteFrequency() >= 20 )
    {
        // case: Enoguh pixels with skincolor, the person is looking
        //       towards the camera.
        return true;
    }
    else
    {
        // case: Person is not looking towards the camera.
        return false;
    }
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirectionByHistogram
   Uses backprojection to determine whether the person is looking towards the camera or not.
   For informations see:
   http://docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
 */
bool SASDProcessingPipeline::deriveViewingDirectionByHistogram( cv::Mat& headRegion )
{
    if ( !m_skinColorHistogramDetectionPipeline->initialized() )
    {
        if ( skeletonData()->allPointsTracked() )
        {
            // case: All joints are tracked and the processing pipeline is not initialized.

            //  Intialize the processing pipeline.
            m_skinColorHistogramDetectionPipeline->computeAndSaveROIHistogram( headRegion );
            return false;
        }
    }
    else
    {
        // case: The processing pipeline is initialized.

        // Use backprojection to determine, if the person is looking towards the camera.
        m_skinColorHistogramDetectionPipeline->process( headRegion );
        if ( m_skinColorHistogramDetectionPipeline->nonZeroRelativeFrequency() > 8.0f )
        {
            return true;
        }
    }
    return false;
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirectionByHistogramHSV
    Calculates the backprojection in the HSV-color space.
 */
bool SASDProcessingPipeline::deriveViewingDirectionByHistogramHSV( cv::Mat& headRegion )
{
    cv::Mat headRegionHSV;
    headRegion.copyTo( headRegionHSV );
    cv::cvtColor( headRegionHSV, headRegionHSV, CV_BGR2HSV );
    return deriveViewingDirectionByHistogram( headRegionHSV ); // call existing algorithm
}

/*!
   \brief SASDProcessingPipeline::drawRegionsOfInteres
 */
void SASDProcessingPipeline::drawRegionsOfInterest( cv::Mat& image )
{
    for ( int i = 0; i < m_regions.count(); ++i )
    {
        drawRegionOfInterest( m_regions.at( i ).m_cropedRegion, image, m_regions.at( i ).m_color );
    }
}

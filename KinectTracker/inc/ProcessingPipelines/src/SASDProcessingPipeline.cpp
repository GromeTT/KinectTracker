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
    if ( m_skeletons.count() <= 0 ||
         !m_skeletonAnalyzer->update( m_skeletons.at( 0 ), timestamp ) )
    {
        // case: Insufficient data for further analysis.
        //       Pass this information to the movementAnalyzer,
        //       so that the visualizer knows that it doesn't
        //       have to paint.
        m_movementAnalyzer->setDataAvailable( false );
        m_sizeAnalyzer->setWorkerStatus( tr( "Nothing detected.") );
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              cv::Scalar( 0, 255, 0 ) );
        return false;
    }
    else
    {
        // case: The data provided by the skeleton are of good quality.
        //       Perform the further analysis on the skeleton data.
        m_movementAnalyzer->analyze( m_skeletons.at( 0 ), timestamp );
        m_sizeAnalyzer->analyze( m_kinect,  m_skeletons.at( 0 ) );

        m_lastRegion = crop( m_skeletonAnalyzer->regionOfInterest(), currentImage );

        QVector3D tmpHeadCenter = m_skeletons.at( 0 )->getJoint( SkeletonData::Joints::Head );
        QPoint headCenter = transformFromSkeltonToRGB( tmpHeadCenter ) ;
        QRect cropedHead = cropRegionWithWidthAndHeightAsPixels( headCenter,
                                                                 25,
                                                                 25,
                                                                 currentImage );

        cv::Mat headRegion = currentImage( cv::Rect( cropedHead.topLeft().x(),
                                                     cropedHead.topLeft().y(),
                                                     cropedHead.width(),
                                                     cropedHead.height() ) );
        deriveViewingDirectionBySkinColor( headRegion );
        // Draw the regions of interest.
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              cv::Scalar( 0, 255, 0 ) );
        if ( m_skeletons.at( 0 )->jointTrackState( SkeletonData::Joints::Head ) == SkeletonData::TrackState::Tracked )
        {
            drawRegionOfInterest( cropedHead,
                                  currentImage,
                                  cv::Scalar( 255, 0, 0 ) );
        }
        else
        {
            drawRegionOfInterest( cropedHead,
                                  currentImage,
                                  cv::Scalar( 0, 0, 255 ) );
        }
        trackJoints( m_skeletons.at( 0 ), currentImage );
        return true;
    }
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

/*!
   \brief SASDProcessingPipeline::analyzeViewingDirectionBySkinColor
   Uses the SkinColorExplicitDefinedSkinRegionDetectionPipeline to determine if the tracked person
   is lookin torwards the camera.
 */
void SASDProcessingPipeline::deriveViewingDirectionBySkinColor( cv::Mat& head )
{
    m_skinPipeline->process( head );
    if ( m_skinPipeline->absoluteFrequency() >= 20 )
    {
        // case: Enoguh pixels with skincolr, the person is looking
        //       towards the camera.
        m_movementAnalyzer->setViewingDirection( "To the camera" );
    }
    else
    {
        // case: Person is not looking towards the camera.
        m_movementAnalyzer->setViewingDirection( "Away from the camera" );
    }
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirectionByHistogram
   Uses backprojection to determine whether the person is looking towards the camera or not.
   For informations see:
   http://docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
 */
void SASDProcessingPipeline::deriveViewingDirectionByHistogram( cv::Mat& headRegion )
{
    if ( !m_skinColorHistogramDetectionPipeline->initialized() )
    {
        if ( skeletonData()->allPointsTracked() )
        {
            // case: All joints are tracked and the processing pipeline is not initialized.

            //  Intialize the processing pipeline.
            m_skinColorHistogramDetectionPipeline->computeAndSaveROIHistogram( headRegion );
            m_skeletonAnalyzer->setUserLooksTowardsCamera( false );
        }
    }
    else
    {
        // case: The processing pipeline is initialized.

        // Use backprojection to determine, if the person is looking towards the camera.
        m_skinColorHistogramDetectionPipeline->process( headRegion );
        if ( m_skinColorHistogramDetectionPipeline->nonZeroRelativeFrequency() > 8.0f )
        {
            m_skeletonAnalyzer->setUserLooksTowardsCamera( true );
        }
        else
        {
            m_skeletonAnalyzer->setUserLooksTowardsCamera( false );
        }
    }
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirectionByHistogramHSV
    Calculates the backprojection in the HSV-color space.
 */
void SASDProcessingPipeline::deriveViewingDirectionByHistogramHSV( cv::Mat& headRegion )
{
    cv::Mat headRegionHSV;
    headRegion.copyTo( headRegionHSV );
    cv::cvtColor( headRegionHSV, headRegionHSV, CV_BGR2HSV );
    deriveViewingDirectionByHistogram( headRegionHSV );
}

#include "../inc/SASDProcessingPipeline.h"
#include "../../Analyzer/inc/SkeletonAnalyzer.h"
#include <QVector2D>

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
{
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
        processRGBData();
    }
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
        m_sizeAnalyzer->setWorkerStatus( tr( "Nothing detected") );
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
        m_sizeAnalyzer->analyze( m_skeletons.at( 0 ) );

        m_lastRegion = m_skeletonAnalyzer->regionOfInterest();
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              cv::Scalar( 0, 255, 0 ) );
        // Draw the regions of interest.
        QVector3D headCenter = m_skeletons.at( 0 )->getJoint( SkeletonData::Joints::Head );
        QVector2D center = transformFromSkeltonToRGB( headCenter ) ;
        drawRegionOfInterestWithAndHeightAsPixels( center,
                                                   25,
                                                   25,
                                                   currentImage,
                                                   cv::Scalar( 255, 0, 0 ) );
        deriveViewingDirectionBySkinColor( currentImage,
                                           center );

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
    m_rgbProcessingPipeline->process( rgb );
}

/*!
   \brief SASDProcessingPipeline::analyzeViewingDirectionBySkinColor
   Uses the SkinColorExplicitDefinedSkinRegionDetectionPipeline to determine if the tracked person
   is lookin torwards the camera.
 */
void SASDProcessingPipeline::deriveViewingDirectionBySkinColor( cv::Mat& currentImage ,
                                                                const QVector2D& center )
{
    // Extract the region of the head.
    cv::Mat head = currentImage( cv::Rect( center.x() - 25,
                                           center.y() - 25,
                                           50,
                                           50 ) );

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
   For informations see:
   http://docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
 */
void SASDProcessingPipeline::deriveViewingDirectionByHistogram( cv::Mat& currentImage,
                                                                const QVector2D& center )
{


}



#include "../inc/SASDProcessingPipeline.h"
#include "../inc/SkeletonAnalyzer.h"
#include <QVector2D>

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
        return false;
    }
    else
    {
        // case: The data provided by the skeleton are of good quality.
        //       Perform the further analysis on the skeleton data.
        m_movementAnalyzer->analyze( m_skeletons.at( 0 ), timestamp );
        m_sizeAnalyzer->analyze( m_skeletons.at( 0 ) );
        drawRegionOfInterestWithAndHeightAsPixels( m_skeletonAnalyzer->headRegion(), cv::Scalar( 255, 0, 0 ) );
//        drawRegionOfInterest( m_skeletonAnalyzer->regionOfInterest(), cv::Scalar( 0, 0, 255 ) );
        QVector2D center = transformFromSkeltonToRGB( m_skeletonAnalyzer->headRegion().center() ) ;

//        cv::Mat head = currentImage( cv::Rect( topLeftCorner.x(),
//                                               topLeftCorner.y(),
//                                               m_skeletonAnalyzer->headRegion().width(),
//                                               m_skeletonAnalyzer->headRegion().height() ) );
        cv::Mat head = currentImage( cv::Rect( center.x() - m_skeletonAnalyzer->headRegion().width() / 2,
                                               center.y() - m_skeletonAnalyzer->headRegion().height() / 2,
                                               m_skeletonAnalyzer->headRegion().width(),
                                               m_skeletonAnalyzer->headRegion().height() ) );
        m_skinPipeline->process( head );
        if ( m_skinPipeline->absoluteFrequency() >= 20 )
        {
            m_movementAnalyzer->setViewingDirection( "To the camera" );
        }
        else
        {
            m_movementAnalyzer->setViewingDirection( "Away from the camera" );
        }

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



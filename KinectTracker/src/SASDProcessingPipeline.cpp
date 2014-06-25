#include "../inc/SASDProcessingPipeline.h"
#include "../inc/SkeletonAnalyzer.h"

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
        drawRegionOfInterest();
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



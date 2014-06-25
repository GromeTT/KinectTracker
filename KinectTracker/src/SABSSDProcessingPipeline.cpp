#include "../inc/SABSSDProcessingPipeline.h"


SABSSDProcessingPipeline::SABSSDProcessingPipeline( KinectPtr& kinect,
                                                    QObject* parent )
    : HighLevelProcessingPipeline( kinect,
                                   new SkinColorExplicitDefinedSkinRegionDetectionPipeline,
                                   new DepthProcessingPipeline,
                                   parent )
{

}

/*!
   \brief SABSSDProcessingPipeline::~SABSSDProcessingPipeline
   Destroyes the object.
 */
SABSSDProcessingPipeline::~SABSSDProcessingPipeline()
{

}

/*!
   \brief SABSSDProcessingPipeline::procesV
 */
void SABSSDProcessingPipeline::processV( const unsigned int timestamp )
{
    if ( !processSkeletonData( timestamp ) )
    {
        // case: Analysis of the skeleton data failed.
        //       Make use of the depth data for the analysis.
        processDepthData();
    }
}

bool SABSSDProcessingPipeline::processSkeletonData(const unsigned int timestamp)
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

void SABSSDProcessingPipeline::processDepthData()
{
    m_depthProcessingPipeline->process( mp_depthData,
                                        mp_depthScrennshot,
                                        m_depthSize );
}

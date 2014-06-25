#include "../inc/RGBAnalyzer.h"
#include <QSize>
#include <opencv2/opencv.hpp>

/*!
   \brief RGBAnalyzer::RGBAnalyzer
   \param parent
 */
RGBAnalyzer::RGBAnalyzer( QObject* parent )
    : ImageAnalyzer( nullptr, parent )
{
}

/*!
   \brief RGBAnalyzer::~RGBAnalyzer
   Destoryes the object.
   \see ImageAnalyzer::~ImageAnalyzer()
 */
RGBAnalyzer::~RGBAnalyzer()
{
}

/*!
   \brief RGBAnalyzer::analyze

 */
void RGBAnalyzer::analyze( cv::Mat& input )
{
    if ( !mp_processingPipeline.isNull() )
    {
        mp_processingPipeline->process( input );
    }
}



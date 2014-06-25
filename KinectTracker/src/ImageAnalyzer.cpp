#include "../Inc/ImageAnalyzer.h"

ImageAnalyzer::ImageAnalyzer( LowLevelProcessingPipeline* pipeline,
                              QObject* parent )
    : QObject( parent )
    , mp_processingPipeline( pipeline )
{
}

/*!
   \brief ImageAnalyzer::~ImageAnalyzer
 */
ImageAnalyzer::~ImageAnalyzer()
{
}

QObject* ImageAnalyzer::getObjectByName( const QString& name )
{
    if ( mp_processingPipeline.isNull() )
    {
        return nullptr;
    }
    return mp_processingPipeline->getObjectByName( name );
}

LowLevelProcessingPipeline* ImageAnalyzer::getProcessingPipeline() const
{
    return mp_processingPipeline.data();
}

void ImageAnalyzer::setProcessingPipeline( LowLevelProcessingPipelinePtr& pipeline )
{
    mp_processingPipeline.reset( pipeline.data() );
}


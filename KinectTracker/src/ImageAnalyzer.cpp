#include "../Inc/ImageAnalyzer.h"

ImageAnalyzer::ImageAnalyzer()
    : mp_processingPipeline( new SkinColorExplicitDefinedSkinRegionDetectionPipeline( this ) )
    , m_snapshot()
{
}

ImageAnalyzer::~ImageAnalyzer()
{
}

void ImageAnalyzer::analyze( cv::Mat& input )
{
    mp_processingPipeline->process( input );
}

void ImageAnalyzer::setSnapshot( cv::Mat& snapshot )
{
    m_snapshot = snapshot;
    if ( mp_processingPipeline.data() )
    {
        mp_processingPipeline->setSnapshot( &m_snapshot );
    }
}

const QVector<ProcessingComponent*>& ImageAnalyzer::getPiplineComponents() const
{

    return mp_processingPipeline->getComponents();
}

QObject* ImageAnalyzer::getObjectByName( const QString& name )
{
    return mp_processingPipeline->getObjectByName( name );
}

ProcessingPipeline*ImageAnalyzer::getProcessingPipeline() const
{
    return mp_processingPipeline.data();
}


#include "../Inc/ProcessingPipeline.h"
#include "../inc/ImageAnalyzer.h"
#include <QDebug>

ProcessingPipeline::ProcessingPipeline( ImageAnalyzer* parent )
    : m_parent( parent )
    , mp_snapshot( nullptr )
{

}

ProcessingPipeline::~ProcessingPipeline()
{
}

void ProcessingPipeline::setSnapshot( cv::Mat* snapshot )
{
    mp_snapshot = snapshot;
}

const QVector<QObject*>& ProcessingPipeline::getComponents() const
{
    return m_processingComponents;
}

QObject* ProcessingPipeline::getObjectByName( const QString& name )
{
    for ( int i = 0; i < m_processingComponents.count(); ++i )
    {
        if ( m_processingComponents.at( i )->objectName() == name )
        {
            return m_processingComponents.at( i );
        }
    }
    return nullptr;
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


BackgroudSubtractionPipeline::BackgroudSubtractionPipeline( ImageAnalyzer* parent )
    : ProcessingPipeline( parent )
    , mp_erode( new Erode() )
{
    m_processingComponents.append( mp_erode.data() );
}

BackgroudSubtractionPipeline::~BackgroudSubtractionPipeline()
{

}

void BackgroudSubtractionPipeline::process(cv::Mat& input)
{
    m_backgroundSubtractor.operator ()( input, input );
    mp_erode->erode( input );
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


BSPipeline::BSPipeline( ImageAnalyzer* parent )
    : ProcessingPipeline( parent )
    , mp_erode( new Erode() )
    , mp_dilate( new Dilate() )
    , mp_threshold( new Threshold() )
{
    m_processingComponents.append( mp_erode.data() );
    m_processingComponents.append( mp_dilate.data() );
    m_processingComponents.append( mp_threshold.data() );
}

BSPipeline::~BSPipeline()
{

}

void BSPipeline::process( cv::Mat& input )
{
    cv::Mat diff;
    cvtColor( input, input, CV_BGR2GRAY );
    cv::equalizeHist( diff, diff );
    if ( mp_snapshot )
    {
        cv::absdiff( input, *mp_snapshot, input );
    }
    else
    {
        qWarning() << QObject::tr( "No screenshot available." );
    }

    mp_threshold->threshold( input );
    mp_erode->erode( input );
    mp_dilate->dilate( input );
//    diff.copyTo( input );
}

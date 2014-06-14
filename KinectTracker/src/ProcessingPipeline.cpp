#include "../Inc/ProcessingPipeline.h"
#include "../inc/ImageAnalyzer.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDebug>

ProcessingPipeline::ProcessingPipeline( ImageAnalyzer* parent )
    : m_parent( parent )
    , mp_snapshot( nullptr )
    , m_instanceCounter( 0 )
{

}

ProcessingPipeline::~ProcessingPipeline()
{
}

void ProcessingPipeline::setSnapshot( cv::Mat* snapshot )
{
    mp_snapshot = snapshot;
}

const QVector<ProcessingComponent*>& ProcessingPipeline::getComponents() const
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

void ProcessingPipeline::registerComponent( ProcessingComponent* component,
                                            const bool recursive )
{
    m_allComponents.insert( m_instanceCounter++, component );
    if ( recursive )
    {
        for ( int i = 0; i < component->getComponents().count(); ++i )
        {
            registerComponent( component->getProcessingComponent( i ), true );
        }
    }
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


/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

HOGDetectionPipeline::HOGDetectionPipeline( ImageAnalyzer* parent )
    : ProcessingPipeline( parent )
    , mp_HOGFeatureDetector( new HOGFeatureDetector() )
{
    mp_HOGFeatureDetector->useDefaultPeopleDetector();
    m_processingComponents.append( mp_HOGFeatureDetector.data() );
}

HOGDetectionPipeline::~HOGDetectionPipeline()
{

}

void HOGDetectionPipeline::process( cv::Mat& input )
{
    cv::Mat greyImg;
    cv::cvtColor( input, greyImg, CV_BGR2GRAY );
    mp_HOGFeatureDetector->detectMultiScale( greyImg,
                                             m_rectangles );

    for ( int i = 0; i < m_rectangles.size(); ++i )
    {

        cv::rectangle( input, m_rectangles.at( i ), cv::Scalar( 255, 0, 0 ), 5 );
    }
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

SkinColorDetectionPipeline::SkinColorDetectionPipeline( ImageAnalyzer* parent )
    : ProcessingPipeline( parent )
    , mp_skinColorDetector( new SkinColorDetector() )
{
    m_processingComponents.append( mp_skinColorDetector.data() );
}

SkinColorDetectionPipeline::~SkinColorDetectionPipeline()
{

}

void SkinColorDetectionPipeline::process( cv::Mat& input )
{
    mp_skinColorDetector->detect( input );
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

SkinColorExplicitDefinedSkinRegionDetectionPipeline::SkinColorExplicitDefinedSkinRegionDetectionPipeline( ImageAnalyzer* parent )
    : ProcessingPipeline( parent )
    , mp_dilate( new Dilate() )
    , mp_erode( new Erode() )
{
    m_processingComponents.append( mp_dilate.data() );
    m_processingComponents.append( mp_erode.data() );

}


SkinColorExplicitDefinedSkinRegionDetectionPipeline::~SkinColorExplicitDefinedSkinRegionDetectionPipeline()
{

}

/*!
   \brief SkinColorExplicitDefinedSkinRegionDetectionPipeline::process

 */
void SkinColorExplicitDefinedSkinRegionDetectionPipeline::process( cv::Mat& input )
{
    // MatTypes: http://ninghang.blogspot.de/2012/11/list-of-mat-type-in-opencv.html
    if ( input.type() != CV_8UC3 )
    {
        qWarning() << QStringLiteral("SkinColorExplicitDefinedSkinRegionDetctionPipeline only supports CV_8UC3 as cv:: Mat type.");
    }
    cv::Mat mask( input.rows, input.cols, input.type() );
    int count = 3*input.rows*input.cols;
    int i = 0;
    while ( i < count )
    {
        uchar b = input.data[i];
        uchar g = input.data[i+1];
        uchar r = input.data[i+2];
        int diff = MAX( MAX( r, g ), b ) - MIN( MIN( r, g ), b );
        if ( r > 95 &&
             g > 40 &&
             b > 20 &&
             diff > 15 &&
             abs( r-g ) > 15 &&
             r > g &&
             g > b )
        {
            mask.data[i]   = 255;
            mask.data[i+1] = 255;
            mask.data[i+2] = 255;
        }
        else
        {
            mask.data[i]   = 0;
            mask.data[i+1] = 0;
            mask.data[i+2] = 0;
        }
        i+=3;
    }
    cv::imshow( "Mask", mask );
//    cv::cvtColor( mask, mask, cv::COLOR_BGR2HSV );
    mp_erode->erode( mask );
    mp_dilate->dilate( mask );
}

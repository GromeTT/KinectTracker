#include "../inc/LowLevelProcessingPipeline.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDebug>

LowLevelProcessingPipeline::LowLevelProcessingPipeline( QObject* parent )
    : QObject( parent )
    , m_instanceCounter( 0 )
    , mp_screenshot( nullptr )
{
    setObjectName( "ProcessingPipeline" );
}

LowLevelProcessingPipeline::~LowLevelProcessingPipeline()
{
}

/*!
   \brief LowLevelProcessingPipeline::setScreenshot
   Stores a pointer to \a screenshot but does not take controll
   over it.
 */
void LowLevelProcessingPipeline::setScreenshot( cv::Mat* screenshot )
{
    mp_screenshot = screenshot;
}

const QVector<ProcessingComponent*>& LowLevelProcessingPipeline::getComponents() const
{
    return m_processingComponents;
}

QObject* LowLevelProcessingPipeline::getObjectByName( const QString& name )
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

cv::Mat* LowLevelProcessingPipeline::getProcessedImage()
{
    return nullptr;
}

void LowLevelProcessingPipeline::registerComponent( ProcessingComponent* component,
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


BackgroudSubtractionPipeline::BackgroudSubtractionPipeline( QObject* parent )
    : LowLevelProcessingPipeline( parent )
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


BSPipeline::BSPipeline( QObject* parent )
    : LowLevelProcessingPipeline( parent )
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
//    if ( mp_snapshot )
//    {
//        cv::absdiff( input, *mp_snapshot, input );
//    }
//    else
//    {
//        qWarning() << QObject::tr( "No screenshot available." );
//    }

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

HOGDetectionPipeline::HOGDetectionPipeline( QObject* parent )
    : LowLevelProcessingPipeline( parent )
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

SkinColorDetectionPipeline::SkinColorDetectionPipeline( QObject* parent )
    : LowLevelProcessingPipeline( parent )
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

SkinColorExplicitDefinedSkinRegionDetectionPipeline::SkinColorExplicitDefinedSkinRegionDetectionPipeline( QObject* parent )
    : LowLevelProcessingPipeline( parent )
    , m_absoluteFrequency( 0 )
{
    setObjectName( "SkinColorExplicitDefinedSkinRegionDetectionPipeline" );
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
        qWarning() << QStringLiteral( "SkinColorExplicitDefinedSkinRegionDetctionPipeline only supports CV_8UC3 as cv:: Mat type." );
        return;
    }
    m_processedImage = cv::Mat( input.rows, input.cols, CV_8UC1 );
    // Reset counters
    m_absoluteFrequency = 0;
    for ( int i = 0; i < input.rows; ++i )
    {
        int k = 0;
        for ( int j = 0; j < input.cols * input.channels(); j += 3 )
        {
            uchar b = input.at<uchar>( i, j );   // blue channel of the pixel
            uchar g = input.at<uchar>( i, j+1 ); // green channel of the pixel
            uchar r = input.at<uchar>( i, j+2 ); // red channel of the pixel
            int diff = MAX( MAX( r, g ), b ) - MIN( MIN( r, g ), b );
            if ( r <= 95 ||
                 g <= 40 ||
                 b <= 20 ||
                 diff <= 15 ||
                 abs( r-g ) <= 15 ||
                 r <= g ||
                 g < b )
            {
                m_processedImage.at<uchar>( i, k ) = 0;
            }
            else
            {
                m_processedImage.at<uchar>( i, k ) = 255;
                ++m_absoluteFrequency;
            }
            ++k;
        }
    }
    if ( m_processedImage.rows > 0 && m_processedImage.cols > 0 )
    {
        cv::imshow("FixedRegoin Processed", m_processedImage );
    }
}

/*!
   \brief SkinColorExplicitDefinedSkinRegionDetectionPipeline::absoluteFrequency
   Returns the absolute frequency of the appearance of skin color.
 */
int SkinColorExplicitDefinedSkinRegionDetectionPipeline::absoluteFrequency()
{
    return m_absoluteFrequency;
}

/*!
   \brief SkinColorExplicitDefinedSkinRegionDetectionPipeline::getProcessedImage
   Returns the filtered image.
 */
cv::Mat* SkinColorExplicitDefinedSkinRegionDetectionPipeline::getProcessedImage()
{
    return& m_processedImage;
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


/*!
   \brief SkinColorHistogramDetectionPipeline::SkinColorHistogramDetectionPipeline
   Standardconstructor.
 */
SkinColorHistogramDetectionPipeline::SkinColorHistogramDetectionPipeline( QObject* parent )
    : LowLevelProcessingPipeline( parent )
    , m_initialized( false )
    , m_threshold( 20 )
    , m_nonZeroPixels( 0 )
    , m_nonZeroRelativeFrequency( 0 )
{
    setObjectName( "SkinColorHistogramDetectionPipeline" );
    m_channels[0] = 0;
    m_channels[0] = 1;
    m_channels[0] = 2;

    m_bins[0] = 256;
    m_bins[1] = 256;
    m_bins[2] = 256;

    m_ranges[0] = 0;
    m_ranges[1] = 255;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::~SkinColorHistogramDetectionPipeline
   Destroyes the object.
 */
SkinColorHistogramDetectionPipeline::~SkinColorHistogramDetectionPipeline()
{
}

/*!
   \brief SkinColorHistogramDetectionPipeline::process
   Computes the backprojection of \a input and the histogram which will be
   computed by calling SkinColorHistogramDetectionPipeline::computeAndSaveROIHistogram.
 */
void SkinColorHistogramDetectionPipeline::process( cv::Mat& input )
{
    const float* range = { m_ranges };
    cv::calcBackProject( &input, 1, &m_channels[0], m_histogram, m_backprojection, &range, 1, true );
//    cv::imshow( "Backprojection", m_backprojection );
    cv::threshold( m_backprojection, m_backprojection, m_threshold, 255, cv::THRESH_BINARY );
//    cv::imshow( "Threshold", backprojection );
    m_nonZeroPixels = cv::countNonZero( m_backprojection );

    if ( m_backprojection.rows == 49 && m_backprojection.cols == 49 )
    {
//        qDebug() << "rows: " << m_backprojection.rows;
//        qDebug() << "cols: " << m_backprojection.cols;
        input.at<uchar>( 10, 10 );
    }
    qDebug() << QString( "Non zero %1" ).arg( m_nonZeroPixels );
    if ( input.rows > 0 && input.cols > 0 )
    {
        cv::imshow( "input", input );
    }
    if ( m_backprojection.rows > 0 && m_backprojection.cols > 0 )
    {
        cv::imshow( "Backprojection", m_backprojection );
    }

    emit nonZeroPixelsChanged();
    m_nonZeroRelativeFrequency = (float) ( m_nonZeroPixels ) / (float)( input.rows + input.cols );
    emit nonZeroRelativeFrequencyChanged();
}

/*!
   \brief SkinColorHistogramDetectionPipeline::setThreshold
   Sets the threshold to \a threshold.
 */
void SkinColorHistogramDetectionPipeline::setThreshold( const float threshold )
{
    m_threshold = threshold;
    emit thresholdChanged();
}

/*!
   \brief SkinColorHistogramDetectionPipeline::computeAndSaveROIHistogram
   If \a rio is a valid cv::Mat, a histogram will be computed and stored in addtion to
   a copy of \a roi. If this function succeeds the SkinColorHistogramDetectionPipeline
   is \a initialized.
 */
bool SkinColorHistogramDetectionPipeline::computeAndSaveROIHistogram( const cv::Mat& roi )
{
    if ( roi.rows == 0 || roi.cols == 0 )
    {
        return false;
    }
    else
    {
        qDebug() << "roi initilaized.";
        roi.copyTo( m_roi );
        const float* range = { m_ranges };
        cv::calcHist( &m_roi, 1, &m_channels[0], cv::Mat(), m_histogram, 1, &m_bins[0], &range, true, false );
        m_initialized = true;
        cv::imshow( "Roi" , m_roi );
        return true;
    }
}

/*!
   \brief SkinColorHistogramDetectionPipeline::channels
   Returns a pointer to the first element of the channels array.
 */
int* SkinColorHistogramDetectionPipeline::channels() const
{
    return &m_channels[0];
}

/*!
   \brief SkinColorHistogramDetectionPipeline::bins
   Returns a pointer to the first element of the bins array.
 */
int*SkinColorHistogramDetectionPipeline::bins() const
{
    return &m_bins[0];
}

/*!
   \brief SkinColorHistogramDetectionPipeline::ranges
   Returns a pointer to the first element of the ranges array.
 */
float* SkinColorHistogramDetectionPipeline::ranges() const
{
    return m_ranges;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::roi
   Returns a cv::Mat with the region of interest.
 */
cv::Mat& SkinColorHistogramDetectionPipeline::roi() const
{
    return m_roi;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::histogram
    Returns the histogram of roi.
 */
cv::MatND&SkinColorHistogramDetectionPipeline::histogram() const
{
    return m_histogram;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::initialized
   Returns true, if the roi has been set.
   Otherwise false.
 */
bool SkinColorHistogramDetectionPipeline::initialized() const
{
    return m_initialized;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::threshold
   Returns the threshold.
 */
double SkinColorHistogramDetectionPipeline::threshold() const
{
    return m_threshold;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::nonZeroPixels
   Returns the number of pixels which are not zero in the backprojection.
 */
int SkinColorHistogramDetectionPipeline::nonZeroPixels() const
{
    return m_nonZeroPixels;
}

/*!
   \brief SkinColorHistogramDetectionPipeline::nonZeroRelativeFrequency
   Returns the relative freuqency of non zero pixels in the backprojection.
 */
float SkinColorHistogramDetectionPipeline::nonZeroRelativeFrequency() const
{
    return m_nonZeroRelativeFrequency;
}

void SkinColorHistogramDetectionPipeline::reset()
{
    m_initialized = false;
}

cv::Mat*SkinColorHistogramDetectionPipeline::getProcessedImage()
{
    return &m_backprojection;
}



#include "../inc/SASDProcessingPipeline.h"
#include "../../Analyzer/inc/SkeletonAnalyzer.h"
#include <QVector2D>
#include <QDebug>
#include <vector>

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
    , m_skinColorHistogramDetectionPipeline( new SkinColorHistogramDetectionPipeline )
    , mp_deriveViewingDirectionFunc( &SASDProcessingPipeline::deriveViewingDirectionBySkinColorFixedRegion )
    , m_useHaarClassifier( false )
    , m_currentThreshold ( 200 )
    , m_skinColorFixedRegionThreshold( 200 )
    , m_histogramThreshold ( 8 )
    , m_histogramHSVThreshold ( 8 )
{
    setObjectName( "SASDProcessingPipeline" );
    m_rgbProcessingPipelines.append( m_skinColorHistogramDetectionPipeline );
    if ( !m_hairFaceClassifier.load( "../KinectTracker/res/haarcascade_frontalface_alt.xml" ) )
    {
        qDebug() << "Error loading hair classifier file.";
    }
    else
    {
        qDebug() << "Loading haarcascade_frontalface_alt.xml was succeful";
    }
}

/*!
   \brief SASDProcessingPipeline::~SASDProcessingPipeline
   Destroyes the object.
 */
SASDProcessingPipeline::~SASDProcessingPipeline()
{
}

/*!
   \brief SASDProcessingPipeline::setUseHaarClassifier
   Activates or deactivates the usage of the haarclassifier.
 */
void SASDProcessingPipeline::setUseHaarClassifier( const bool arg )
{
    m_useHaarClassifier = arg;
    emit useHaarClassifierChanged();
}

/*!
   \brief SASDProcessingPipeline::setSkinColorFixedRegionThreshold
   Sets the threshold for the SkinColorFixedRegion-method.
 */
void SASDProcessingPipeline::setSkinColorFixedRegionThreshold( const int threshold )
{
    m_skinColorFixedRegionThreshold = threshold;
    emit skinColorFixedRegionThresholdChanged();
}

/*!
   \brief SASDProcessingPipeline::setHistogramThreshold
   Sets the threshold for the SkinColorHistogram-method.
 */
void SASDProcessingPipeline::setHistogramThreshold( const int threshold )
{
    m_histogramThreshold = threshold;
    emit histogramHSVThresholdChanged();
}

/*!
   \brief SASDProcessingPipeline::setHistogramHSVThreshold
    Sets the threshold for the SkinColorHistogramHSV-method.
 */
void SASDProcessingPipeline::setHistogramHSVThreshold(const int threshold)
{
    m_histogramHSVThreshold = threshold;
    emit histogramHSVThresholdChanged();
}

/*!
   \brief SASDProcessingPipeline::useHaarClassifier
   Returns true, if the haarClassifier is used while prrocessing.
 */
bool SASDProcessingPipeline::useHaarClassifier() const
{
    return m_useHaarClassifier;
}

/*!
   \brief SASDProcessingPipeline::skinColorFixedRegionThreshold
   Returns the threshold used by the SkinColorFixedRegion-method.
 */
int SASDProcessingPipeline::skinColorFixedRegionThreshold() const
{
    return m_skinColorFixedRegionThreshold;
}

/*!
   \brief SASDProcessingPipeline::histogramThreshold
   Returns the threshold used by the SkinColorHistogram-method.
 */
int SASDProcessingPipeline::histogramThreshold() const
{
    return m_histogramThreshold;
}

/*!
   \brief SASDProcessingPipeline::histogramHSVThreshold
   Returns the threshold used by the SkinColorHistogram-method.
 */
int SASDProcessingPipeline::histogramHSVThreshold() const
{
    return m_histogramHSVThreshold;
}

/*!
   \brief SASDProcessingPipeline::processV
   \see HighLevelProcessingPipeline::process()
 */
void SASDProcessingPipeline::processV( const unsigned int timestamp )
{
    processSkeletonData( timestamp );
}

void SASDProcessingPipeline::resetV()
{
    m_skinColorHistogramDetectionPipeline->reset();
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
        m_sizeAnalyzer->analyze( m_kinect, SkeletonDataPtr( nullptr ) );
        // Explore the last skeleton.
        if ( m_lastRegion.width() > 0 &&
             m_lastRegion.height() > 0 )
        {
            if ( !deriveViewingDirection() )
            {
                QVector3D headPosition;
                // Explore the last region.
                if( !analyseLastRegion( currentImage, headPosition ) )
                {
                    // Use cascade haar classifier as last possibility
                    // if enabled.
                    if ( m_useHaarClassifier )
                    {
                         qDebug() << "Using hair classifier.";
                         useHaarClassifier( currentImage );
                    }
                }
            }
        }
        // Draw the region where the person has been found
        // the at last.
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              Qt::red );
        return false;
    }
    else
    {
        m_regions.clear();
        // case: The data provided by the skeleton are of good quality.
        //       Perform the further analysis on the skeleton data.
        m_unableToTrackInARowCount = 0;
        m_movementAnalyzer->analyze( m_skeletons.at( 0 ), timestamp );
        m_sizeAnalyzer->analyze( m_kinect,  m_skeletons.at( 0 ) );

        m_lastRegion = crop( m_skeletonAnalyzer->regionOfInterest(), currentImage );
        extractAllRegions( currentImage );
        // Derive the viewing direction.
        deriveViewingDirection();
        // Draw the regions of interest.
        drawRegionsOfInterest( currentImage );
        drawRegionOfInterest( m_lastRegion,
                              currentImage,
                              Qt::red );
        m_lastSkeleton = SkeletonDataPtr( m_skeletons.at( 0 ) );
        return true;
    }
}

/*!
   \brief SASDProcessingPipeline::extractAllRegions
   Executes extract region on all joints of the skeleton.
 */
void SASDProcessingPipeline::extractAllRegions( Mat& image )
{
    extractRegion( image, SkeletonData::Joints::Hip );
    extractRegion( image, SkeletonData::Joints::Spine );
    extractRegion( image, SkeletonData::Joints::ShoulderCenter );
    extractRegion( image, SkeletonData::Joints::Head );
    extractRegion( image, SkeletonData::Joints::ShoulderLeft );
    extractRegion( image, SkeletonData::Joints::ElbowLeft );
    extractRegion( image, SkeletonData::Joints::WristLeft );
    extractRegion( image, SkeletonData::Joints::HandLeft );
    extractRegion( image, SkeletonData::Joints::ShoulderRight );
    extractRegion( image, SkeletonData::Joints::ElbowRight );
    extractRegion( image, SkeletonData::Joints::WristRight );
    extractRegion( image, SkeletonData::Joints::HandRight );
    extractRegion( image, SkeletonData::Joints::HipLeft );
    extractRegion( image, SkeletonData::Joints::KneeLeft );
    extractRegion( image, SkeletonData::Joints::AnkleLeft );
    extractRegion( image, SkeletonData::Joints::FootLeft );
    extractRegion( image, SkeletonData::Joints::HipRight );
    extractRegion( image, SkeletonData::Joints::KneeRight );
    extractRegion( image, SkeletonData::Joints::AnkleRight );
    extractRegion( image, SkeletonData::Joints::FootRight );
}

/*!
   \brief SASDProcessingPipeline::extractRegion
   Extracts a pre-defined region around \a joint from \a image and stores the data into \a m_regions.
*/
void SASDProcessingPipeline::extractRegion( Mat& image, SkeletonData::Joints joint )
{
    QVector3D centerSkeletonSpace = m_skeletons.at( 0 )->getJoint( joint );
    QPoint centerRGBSpace = transformFromSkeltonToRGB( centerSkeletonSpace ) ;
    QRect cropedRegion = cropRegionWithWidthAndHeightAsPixels( centerRGBSpace,
                                                               25,
                                                               25,
                                                               image );
    QColor color;
    if ( skeletonData()->jointTrackState( joint ) == SkeletonData::TrackState::Tracked )
    {
        color = Qt::green;
    }
    else
    {
        color = Qt::red;
    }
    m_regions.append( JointSummary( image( cv::Rect( cv::Point( cropedRegion.topLeft().x(),
                                                                cropedRegion.topLeft().y() ),
                                                     cv::Point( cropedRegion.bottomRight().x(),
                                                                cropedRegion.bottomRight().y() ) ) ),
                                    cropedRegion,
                                    joint,
                                    color ) );
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
    //    m_rgbProcessingPipeline->process( rgb );
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirection
   Derives the viewing direcion of the user.
 */
bool SASDProcessingPipeline::deriveViewingDirection()
{
    if ( m_regions.count() != 20 )
    {
        return false;
    }
    cv::Mat head = m_regions.at( static_cast<int>(SkeletonData::Joints::Head) ).m_subMatrix;
    if ( (this->*mp_deriveViewingDirectionFunc)( head ) )
    {
        // case: From the analysis of the head region it follows
        //       that the user is looking towards the camera.
        m_skeletonAnalyzer->setUserLooksTowardsCamera( true );
        return true;
    }
    else
    {
        // case: From the analysis of the head region it doesn't
        //       follow, that the user is looking towards the camera.

        // Check the remaining regions.
        int index = -1;
        int count = 0;
        bool found = false;
        for ( int i = 0; i < m_regions.count(); ++i )
        {
            cv::Mat region = m_regions.at( i ).m_subMatrix;
            int c = 0;
            if ( (this->*mp_deriveViewingDirectionFunc)( region ) &&
                 c > count )
            {
                found = true;
                index = i;
                count = c;
            }
        }
        if ( !found )
        {
            // case: No region contains enough non zero pixels, it follows that the
            //       user isn't looking towards the camera.
            m_skeletonAnalyzer->setUserLooksTowardsCamera( false );
            return false;
        }
        else
        {
            qDebug() << QString( "Found at joint: %1" ).arg( jointToString( static_cast<SkeletonData::Joints>( index ) ) );
            // Get xyz - coordinates of the found head and pass them to the size analyzer.
            QVector3D headPos = skeletonData()->getJoint( static_cast<SkeletonData::Joints>( index ) );
            return true;
        }
    }
}

/*!
   \brief SASDProcessingPipeline::analyzeViewingDirectionBySkinColorFixedRegion
   Uses the SkinColorExplicitDefinedSkinRegionDetectionPipeline to determine if the tracked person
   is lookin torwards the camera.
 */
bool SASDProcessingPipeline::deriveViewingDirectionBySkinColorFixedRegion( cv::Mat& region )
{
    m_skinPipeline->process( region );
    int absoluteCount = m_skinPipeline->absoluteFrequency();
    if ( absoluteCount >= 200 )
    {
        // case: Enough pixels with skincolor, the person is looking
        //       towards the camera.
        return true;
    }
    else
    {
        // case: Person is not looking towards the camera.
        return false;
    }
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirectionByHistogram
   Uses backprojection to determine whether the person is looking towards the camera or not.
   For informations see:
   http://docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
 */
bool SASDProcessingPipeline::deriveViewingDirectionByHistogram( cv::Mat& region )
{
    if ( !m_skinColorHistogramDetectionPipeline->initialized() )
    {
        // case: ProcessingPipeline is not initialized yet.
        if ( skeletonData()->allPointsTracked() )
        {
            // case: All joints are tracked and the processing pipeline is not initialized.

            //  Intialize the processing pipeline.
            m_skinColorHistogramDetectionPipeline->computeAndSaveROIHistogram( region );
            return false;
        }
    }
    else
    {
        // case: ProcessingPipeline is already initialized.
        // Use backprojection to determine, if the person is looking towards the camera.
        m_skinColorHistogramDetectionPipeline->process( region );
        if ( m_skinColorHistogramDetectionPipeline->nonZeroRelativeFrequency() > m_histogramThreshold )
        {
            return true;
        }
    }
    return false;
}

/*!
   \brief SASDProcessingPipeline::deriveViewingDirectionByHistogramHSV
    Calculates the backprojection in the HSV-color space.
 */
bool SASDProcessingPipeline::deriveViewingDirectionByHistogramHSV( cv::Mat& region )
{
    cv::Mat regionHSV;
    region.copyTo( regionHSV );
    cv::cvtColor( regionHSV, regionHSV, CV_BGR2HSV );
    return deriveViewingDirectionByHistogram( regionHSV ); // call existing algorithm.
}

/*!
   \brief SASDProcessingPipeline::drawRegionsOfInteres
   Draws all regions in \a m_regions.
 */
void SASDProcessingPipeline::drawRegionsOfInterest( cv::Mat& image )
{
    for ( int i = 0; i < m_regions.count(); ++i )
    {
        drawRegionOfInterest( m_regions.at( i ).m_cropedRegion, image, m_regions.at( i ).m_color );
    }
}

/*!
   \brief SASDProcessingPipeline::useHaarClassifier
   http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
   http://docs.opencv.org/modules/objdetect/doc/cascade_classification.html?highlight=detectmultiscale#cascadeclassifier-detectmultiscale

 */
void SASDProcessingPipeline::useHaarClassifier( cv::Mat& currentImage )
{
    faces.clear();
    cv::Mat lastRegion = currentImage( cv::Rect( cv::Point( m_lastRegion.topLeft().x(),
                                                            m_lastRegion.topLeft().y() ),
                                                 cv::Point( m_lastRegion.bottomRight().x(),
                                                            m_lastRegion.bottomRight().y() )) );
    if ( lastRegion.rows < 0 || lastRegion.cols < 0 )
    {
        return;
    }
    cv::Mat greyRegion;
    lastRegion.copyTo( greyRegion );
    currentImage.copyTo( greyRegion );
    cv::cvtColor( greyRegion, greyRegion, CV_BGR2GRAY );
    m_hairFaceClassifier.detectMultiScale( greyRegion, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
    {
        rectangle( currentImage, faces.at( i ), Scalar( 0, 0, 255 ), 5 );
        cv::imshow(  "Face", currentImage );
    }
}

/*!
   \brief SASDProcessingPipeline::analyseLastRegion
   Analysis the last region and checks if there is a 50x50 region
   which could be potentially the face.
 */
bool SASDProcessingPipeline::analyseLastRegion(cv::Mat& image , QVector3D& head )
{
    qDebug() << "Analysing last region";
    QSize patchSize ( 50, 50 );
    cv::Mat lastRegion = image( cv::Rect( cv::Point( m_lastRegion.topLeft().x(),
                                                     m_lastRegion.topLeft().y() ),
                                          cv::Point( m_lastRegion.bottomRight().x(),
                                                     m_lastRegion.bottomRight().y() ) ) );
    m_skinPipeline->process( lastRegion );
    cv::Mat* filteredCopy = m_skinPipeline->getProcessedImage();
    if ( filteredCopy->channels() != 1 )
    {
        qWarning() << "Image has more or less the one channel.";
        return false;
    }
    cv::imshow( "Filtered copy", *filteredCopy );
    int absoluteCount = 0;
    int i_x = -1;
    int i_y = -1;
    for ( int i = 0; i < lastRegion.cols - patchSize.width(); ++i )
    {
        for ( int j = 0; j < lastRegion.rows - patchSize.height(); ++j )
        {
            cv::Mat tmp = (*filteredCopy)( cv::Rect( cv::Point( i, j ),
                                                     cv::Point( i + patchSize.width(), j+patchSize.height() ) ) );
            int tmpCount = cv::countNonZero( tmp );
            if ( tmpCount > absoluteCount )
            {
                absoluteCount = tmpCount;
                i_x = i;
                i_y = j;
            }
        }
    }
    if ( absoluteCount > m_currentThreshold )
    {
        cv::Mat res = (*filteredCopy)( cv::Rect( cv::Point( i_x, i_y ),
                                                 cv::Point( i_x + patchSize.width(),  i_y + patchSize.height() ) ) );
        if (  m_kinect->transformFromRGBToSkeleton( QPoint( i_x + res.cols/2,
                                                            i_y + res.rows/2 ),
                                                    head ) )
        {
            cv::imshow( "Result", res );
            return true;
        }
        return true;
    }
    return false;
}

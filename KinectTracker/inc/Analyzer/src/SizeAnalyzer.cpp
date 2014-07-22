#include "../inc/SizeAnalyzer.h"
#include <QDebug>

/*!
   \brief SizeAnalyzer::SizeAnalyzer
   Standardconstructor.
 */
SizeAnalyzer::SizeAnalyzer( QObject* parent )
    : QObject( parent )
    , m_kneelingThreshold( 0.55f )
    , m_lyingThreshold( 0.4f )
    , m_estimatedBodySize( 0.0f )
    , m_currentBodySize( 0.0f )
    , m_workerStatus( WorkerStatus::NotPossible )
    , m_distanceHeadRightFood( 0.0f )
    , m_distanceHeadLeftFood( 0.0f )
    , m_distanceFloorHead( 0.0f )
    , m_floorInitialized( false )
{
}

/*!
   \brief SizeAnalyzer::~SizeAnalyzer
   Destroyes the object.
 */
SizeAnalyzer::~SizeAnalyzer()
{
}


/*!
   \brief SizeAnalyzer::analyze
   Perform analysis on \a skeletonData.
 */
void SizeAnalyzer::analyze( const KinectPtr kinect,
                            const SkeletonDataPtr& skeletonData )
{
    // Estimate the body height of the user and update the current body height.
    analyzeV( skeletonData );

    if ( skeletonData.isNull() )
    {
        if ( m_workerStatus != WorkerStatus::Lying )
        {
            // The worker was not lying in the last frame, assume, that he left
            // the ara or hidden.
            setWorkerStatus( WorkerStatus::NotPossible );
        }
        return;
    }

    // Compute the distance between the head and the feets.
    // It's going to be used to determine, if the person is lying.
    m_distanceHeadLeftFood = ( skeletonData->getJoint( SkeletonData::Joints::Head ) - skeletonData->getJoint( SkeletonData::Joints::FootLeft ) ).length();
    emit distanceHeadLeftFoodChanged();
    m_distanceHeadRightFood = ( skeletonData->getJoint( SkeletonData::Joints::Head ) - skeletonData->getJoint( SkeletonData::Joints::FootRight) ).length();
    emit distanceHeadRightFoodChanged();

    // Compare the current body height with the estiamed body height
    // and classify the pose.
    if ( m_currentBodySize >= m_kneelingThreshold * m_estimatedBodySize )
    {
        setWorkerStatus( WorkerStatus::Standing );
    }
    else
    {
        if ( m_currentBodySize < m_lyingThreshold * m_estimatedBodySize )
        {
            setWorkerStatus( WorkerStatus::Lying );
        }
        else
        {
            setWorkerStatus( WorkerStatus::Kneeling );
        }
    }

    // Compute the distance from the head to the floor.
    if ( skeletonData->majorPointsTracked() && !floorInitialized() )
    {
        // All joints are tracked and the floor coefficients haven't
        // been stored yet.
        // Do it now.
        if ( kinect->planeCoefficients() != QVector4D( 0, 0, 0, 0 ) )
        {
            m_planeCoefficients = kinect->planeCoefficients();
            m_floorInitialized = true;
            qDebug() << "Floor initialized";
        }
    }
    if ( skeletonData->jointTrackState( SkeletonData::Joints::Head ) == SkeletonData::TrackState::Tracked &&
         m_floorInitialized )
    {
        // The head is tracked and the plane coefficients have been stored.
        // Now compute the distance between the head and the floor by formula:
        // http://www.frustfrei-lernen.de/mathematik/abstand-punkt-zu-ebene.html
        QVector3D normalVector ( m_planeCoefficients.x(),
                                 m_planeCoefficients.y(),
                                 m_planeCoefficients.z() );
        QVector3D pointInPlane( 0,
                                -m_planeCoefficients.w() / m_planeCoefficients.y() ,
                                0 );
        normalVector.normalize();
        QVector3D head = skeletonData->getJoint( SkeletonData::Joints::Head );
        m_distanceFloorHead = head.distanceToPlane( pointInPlane, normalVector );
        emit distanceFloorHeadChanged();
    }
    emit workerStatusChanged();
}

/*!
   \brief SizeAnalyzer::setKneelingThreshold
   Sets the kneelingThreshold.
 */
void SizeAnalyzer::setKneelingThreshold( const float threshold )
{
    m_kneelingThreshold = threshold;
    emit kneelingThresholdChanged();
}

/*!
   \brief SizeAnalyzer::setLyingThreshold
   Sets the lyingThreshold.
 */
void SizeAnalyzer::setLyingThreshold( const float threshold )
{
    m_lyingThreshold = threshold;
    emit lyingThresholdChanged();
}

void SizeAnalyzer::setWorkerStatus( const WorkerStatus status )
{
    m_workerStatus = status;
    emit workerStatusChanged();
}

/*!
   \brief SizeAnalyzer::estimatedBodySize
   Returns the estimated body size.
 */
float SizeAnalyzer::estimatedBodySize() const
{
    return m_estimatedBodySize;
}

/*!
   \brief SizeAnalyzer::currentBodySize
   Returns the current body size.
 */
float SizeAnalyzer::currentBodySize() const
{
    return m_currentBodySize;
}

/*!
   \brief SizeAnalyzer::kneelingThreshold
   Returns the threshold used to determine if the worker
   is kneeling.
 */
float SizeAnalyzer::kneelingThreshold() const
{
    return m_kneelingThreshold;
}

/*!
   \brief SizeAnalyzer::lyingThreshold
   Returns the threshold used to determine if the worker
   is lying.
 */
float SizeAnalyzer::lyingThreshold() const
{
    return m_lyingThreshold;
}

/*!
   \brief SizeAnalyzer::distanceHeadRightFood
   Returns the distance between the head and the right food.
 */
float SizeAnalyzer::distanceHeadRightFood() const
{
    return m_distanceHeadRightFood;
}

/*!
   \brief SizeAnalyzer::distanceHeadLeftFood
   Returns the distance between the head and the left food.
 */
float SizeAnalyzer::distanceHeadLeftFood() const
{
    return m_distanceHeadLeftFood;
}

/*!
   \brief SizeAnalyzer::distanceFloorHead
   Returns the distance between the floor and the head.
 */
float SizeAnalyzer::distanceFloorHead() const
{
    return m_distanceFloorHead;
}

/*!
   \brief SizeAnalyzer::workerStatus
   Returns the status of the worker.
 */
QString SizeAnalyzer::workerStatusToString() const
{
    switch ( m_workerStatus )
    {
        case WorkerStatus::Standing:
            return "Standing";
        case WorkerStatus::Kneeling:
            return "Kneeling";
        case WorkerStatus::Lying:
            return "Lying";
        default:
            return "No prediction possible";
    }
}

SizeAnalyzer::WorkerStatus SizeAnalyzer::workerStatus() const
{
    return m_workerStatus;
}

/*!
   \brief SizeAnalyzer::floorInitialized
   Returns if the coefficients has been adopted.
 */
bool SizeAnalyzer::floorInitialized() const
{
    return m_floorInitialized;}

/*!
   \brief SizeAnalyzer::planeCoefficients
   Returns the plane coefficients.
 */
QVector4D SizeAnalyzer::planeCoefficients() const
{
    return m_planeCoefficients;
}

/*!
   \brief SizeAnalyzer::reset
 */
void SizeAnalyzer::reset()
{
    m_floorInitialized = false;
    m_estimatedBodySize = 0;
    estimatedBodySizeChanged();
    resetV();
}

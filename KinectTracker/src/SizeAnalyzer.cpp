#include "../inc/SizeAnalyzer.h"

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
    , m_workerStatus( "Not tracked" )
    , m_distanceHeadRightFood( 0 )
    , m_distanceHeadLeftFood( 0 )
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
void SizeAnalyzer::analyze( const SkeletonDataPtr& skeletonData )
{
    // Compute the distance between the head and the feets.
    // It's going to be used to determine, if the person is lying.
    m_distanceHeadLeftFood = ( skeletonData->getJoint( SkeletonData::Joints::Head ) - skeletonData->getJoint( SkeletonData::Joints::FootLeft ) ).length();
    emit distanceHeadLeftFoodChanged();
    m_distanceHeadRightFood = ( skeletonData->getJoint( SkeletonData::Joints::Head ) - skeletonData->getJoint( SkeletonData::Joints::FootRight) ).length();
    emit distanceHeadRightFoodChanged();


    analyzeV( skeletonData );
    if ( m_currentBodySize >= m_kneelingThreshold * m_estimatedBodySize )
    {
        m_workerStatus = tr( "Staying" );
    }
    else
    {
        if ( m_currentBodySize < m_lyingThreshold * m_estimatedBodySize )
        {
            m_workerStatus = tr( "Lying" );
        }
        else
        {
            m_workerStatus = tr( "Kneeling" );
        }
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

void SizeAnalyzer::setWorkerStatus( const QString& status )
{
    m_workerStatus = status;
    emit workerStatusChanged();
}

/*!
   \brief SizeAnalyzer::estimatedBodySize
   Returns the estimated body size.
 */
float SizeAnalyzer::estimatedBodySize()
{
    return m_estimatedBodySize;
}

/*!
   \brief SizeAnalyzer::currentBodySize
   Returns the current body size.
 */
float SizeAnalyzer::currentBodySize()
{
    return m_currentBodySize;
}

/*!
   \brief SizeAnalyzer::kneelingThreshold
   Returns the threshold used to determine if the worker
   is kneeling.
 */
float SizeAnalyzer::kneelingThreshold()
{
    return m_kneelingThreshold;
}

/*!
   \brief SizeAnalyzer::lyingThreshold
   Returns the threshold used to determine if the worker
   is lying.
 */
float SizeAnalyzer::lyingThreshold()
{
    return m_lyingThreshold;
}

/*!
   \brief SizeAnalyzer::distanceHeadRightFood
   Returns the distance between the head and the right food.
 */
float SizeAnalyzer::distanceHeadRightFood()
{
    return m_distanceHeadRightFood;
}

/*!
   \brief SizeAnalyzer::distanceHeadLeftFood
   Returns the distance between the head and the left food.
 */
float SizeAnalyzer::distanceHeadLeftFood()
{
    return m_distanceHeadLeftFood;
}

/*!
   \brief SizeAnalyzer::workerStatus
   Returns the status of the worker.
 */
QString SizeAnalyzer::workerStatus()
{
    return m_workerStatus;
}

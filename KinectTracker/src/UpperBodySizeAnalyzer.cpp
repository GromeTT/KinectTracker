#include "../inc/UpperBodySizeAnalyzer.h"
#include <QDebug>

/*!
   \brief UpperBodySizeAnalyzer::UpperBodySizeAnalyzer
   Standardconstructor.
 */
UpperBodySizeAnalyzer::UpperBodySizeAnalyzer()
    : m_bodyPropotionFactor( 8/3 )
{

}

/*!
   \brief UpperBodySizeAnalyzer::~UpperBodySizeAnalyzer
   Destoryes the object.
 */
UpperBodySizeAnalyzer::~UpperBodySizeAnalyzer()
{

}

/*!
   \brief UpperBodySizeAnalyzer::setBodyPropotionFactor
   Sets the bodyPropotionFactor to \a factor.
 */
void UpperBodySizeAnalyzer::setBodyPropotionFactor( const float factor )
{
    m_bodyPropotionFactor = factor;
}

/*!
   \brief UpperBodySizeAnalyzer::bodyPropotionFactor
   Returns the bodyPropotionFactor.
   This factor is used to conclude the size of the body by only
   knowing the size of the upper part of the body.
   Normaly the size of the upper body should be
   3/8 of the total size.
 */
float UpperBodySizeAnalyzer::bodyPropotionFactor() const
{
    return m_bodyPropotionFactor;
}

/*!
   \brief UpperBodySizeAnalyzer::analyzeV

 */
void UpperBodySizeAnalyzer::analyzeV( const SkeletonDataPtr& skeletonData )
{
    if ( m_estimatedBodySize == 0)
    {
        // case: The body size of the worker hasn't been estimated yet.
        estimateBodySize( skeletonData );
    }
    else
    {
        // case: Classify worker pose.

        // TODO: Implement
    }
}

/*!
   \brief UpperBodySizeAnalyzer::estimateBodySize
   Estimates the size of the detected person.
   For this purpose the status for the joints head, spine, and shouldercenter have to be tracked.
 */
void UpperBodySizeAnalyzer::estimateBodySize( const SkeletonDataPtr& skeletonData )
{
    if ( skeletonData->jointTrackState( SkeletonData::Joints::ShoulderCenter) == SkeletonData::TrackState::Tracked &&
         skeletonData->jointTrackState( SkeletonData::Joints::Hip) == SkeletonData::TrackState::Tracked &&
         skeletonData->jointTrackState( SkeletonData::Joints::Spine) == SkeletonData::TrackState::Tracked )
    {
        // case: The skeleton data is of good quality. Accumalte the length of the two vectors connecting:
        //          1. Hip and Spine
        //          2. Spine and ShoulderCenter
        //       After http://malen-malerei.de/proportionsregel-menschen-zeichnen the size of the upperbody
        //       should be 3/8 of the total size.
        //       Unfortunately this factor won't hold here.

        m_estimatedBodySize = 0;
        m_estimatedBodySize += ( skeletonData->getJoint( SkeletonData::Joints::Hip) - skeletonData->getJoint( SkeletonData::Joints::Spine) ).length();
        qDebug() <<  m_estimatedBodySize;
        m_estimatedBodySize += ( skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter) - skeletonData->getJoint( SkeletonData::Joints::Spine) ).length();
        qDebug() <<  m_estimatedBodySize;
        m_estimatedBodySize = m_bodyPropotionFactor * m_estimatedBodySize;
        m_workerStatus = "Standing";
        emit workerStatusChanged();
        emit estimatedBodySizeChanged();
    }
}

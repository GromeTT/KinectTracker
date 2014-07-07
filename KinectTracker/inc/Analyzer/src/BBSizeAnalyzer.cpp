#include "../inc/BBSizeAnalyzer.h"

/*!
   \brief BBSizeAnalyzer::BBSizeAnalyzer
   Standardconstructor.
 */
BBSizeAnalyzer::BBSizeAnalyzer( QObject* parent )
    : SizeAnalyzer( parent )
    , m_boundingBox( new BoundingBox )
{
    setObjectName( "BBSizeAnalyzer" );
}

/*!
   \brief BBSizeAnalyzer::~BBSizeAnalyzer
   Destroyes the object.
 */
BBSizeAnalyzer::~BBSizeAnalyzer()
{
}

/*!
   \brief BBSizeAnalyzer::boundigBox
   Returns the BoundingBox which contains the following joints:
   - Head
   - ShoulderCenter
   - ShoulderLeft
   - ShoulderRight
   - Hip
   - HipLeft
   - HipRight
   - KneeLeft
   - KneeRight
   - AnkleLeft
   - AnkleRight
   - FootLeft
   - FootRight
 */
BoundingBoxPtr BBSizeAnalyzer::boundigBox() const
{
    return m_boundingBox;
}

/*!
   \brief BBSizeAnalyzer::analyzeV
    This method will calculate a BoundingBox around the
    - Head
    - ShoulderCenter
    - ShoulderLeft
    - ShoulderRight
    - Hip
    - HipLeft
    - HipRight
    - KneeLeft
    - KneeRight
    - AnkleLeft
    - AnkleRight
    - FootLeft
    - FootRight
    If the size of this BoundingBox is greater then the estimated height,
    this value will be updated.
    Generally the height of the box is handeld as the height of the
    detected person.
 */
void BBSizeAnalyzer::analyzeV( const SkeletonDataPtr& skeletonData )
{
    QVector<QVector3D> joints;
    joints.append( skeletonData->getJoint( SkeletonData::Joints::Head ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::ShoulderLeft) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::ShoulderRight) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::Hip ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::HipLeft ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::HipRight ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::KneeLeft ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::KneeRight ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::AnkleLeft ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::AnkleRight ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::FootLeft ) );
    joints.append( skeletonData->getJoint( SkeletonData::Joints::FootRight ) );

    // Calculate a bounding box around the joints.
    m_boundingBox->calculateBoundingBox( joints );

    if ( m_boundingBox->height() > m_estimatedBodySize &&
         m_boundingBox->height() < 2.30f )
    {
        // If the bounding box is greater then the estiamted body height
        // and lower the 2.3 meters, update the value of the estimated body
        // size.
        m_estimatedBodySize = m_boundingBox->height();
        emit estimatedBodySizeChanged();
    }

    m_currentBodySize = m_boundingBox->height();
    emit currentBodySizeChanged();

    // This crap is for another method.

//    if ( skeletonData->jointTrackState( SkeletonData::Joints::Head ) == SkeletonData::TrackState::Tracked &&
//         skeletonData->jointTrackState( SkeletonData::Joints::ShoulderCenter ) == SkeletonData::TrackState::Tracked  &&
//         skeletonData->jointTrackState( SkeletonData::Joints::Spine ) == SkeletonData::TrackState::Tracked  &&
//         skeletonData->jointTrackState( SkeletonData::Joints::Hip ) == SkeletonData::TrackState::Tracked )
//    {
//        if ( skeletonData->jointTrackState( SkeletonData::Joints::AnkleLeft) == SkeletonData::TrackState::Tracked &&
//             skeletonData->jointTrackState( SkeletonData::Joints::KneeLeft ) == SkeletonData::TrackState::Tracked )
//        {
//            height    = skeletonData->getJoint( SkeletonData::Joints::Head ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::Spine ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::Hip ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::AnkleLeft ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::KneeLeft ).length();
//            return true;
//        }
//        else if ( skeletonData->jointTrackState( SkeletonData::Joints::AnkleLeft) == SkeletonData::TrackState::Tracked &&
//                  skeletonData->jointTrackState( SkeletonData::Joints::KneeLeft ) == SkeletonData::TrackState::Tracked )
//        {
//            height    = skeletonData->getJoint( SkeletonData::Joints::Head ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::Spine ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::Hip ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::AnkleLeft ).length();
//            height   += skeletonData->getJoint( SkeletonData::Joints::KneeLeft ).length();
//            return true;
//        }
//    }
    //    return false;
}

void BBSizeAnalyzer::resetV()
{

}

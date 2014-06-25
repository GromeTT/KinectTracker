#include "../inc/SkeletonData.h"
#include <math.h>
#include <QDebug>


/*!
   \fn SkeletonData::SkeletonData
   Constructs a SkeletonData object with all joints set to (0, 0, 0).
 */
SkeletonData::SkeletonData()
{
    m_joints.resize( 20 );
    m_jointTrackState.resize( 20 );
}

/*!
   \fn SkeletonData::SkeletonData( const NUI_SKELETON_DATA& skeletonData )
   Constructs a new SkeletonData object from the data provided by \a skeletonData.
 */
SkeletonData::SkeletonData( const NUI_SKELETON_DATA& skeletonData )
{
    m_joints.resize( 20 );
    m_jointTrackState.resize( 20 );
    setSkeletonBySkeletonData( skeletonData );
}

/*!
   \brief SkeletonData::SkeletonData
   Copyconstrutor;
 */

SkeletonData::SkeletonData( const SkeletonData& other)
{
    m_joints                    = other.m_joints;
    m_jointTrackState           = other.m_jointTrackState;
    m_quality                   = other.m_quality;
    m_numberOfTrackedPoints     = other.m_numberOfTrackedPoints;
}

/*!
   \fn SkeletonData::~SkeletonData
   Destroyes this object.
 */
SkeletonData::~SkeletonData()
{
}

/*!
   \fn SkeletonData::setSkeletonBySkeletonData
   Stores the data provided by \a skeleton data in this object.
 */
void SkeletonData::setSkeletonBySkeletonData( const NUI_SKELETON_DATA& skeletonData )
{
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_HIP_CENTER], m_joints[static_cast<int>( Joints::Hip )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_SPINE], m_joints[static_cast<int>( Joints::Spine )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER], m_joints[static_cast<int>( Joints::ShoulderCenter)] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_HEAD], m_joints[static_cast<int>( Joints::Head )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT], m_joints[static_cast<int>( Joints::ShoulderLeft )]  );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT], m_joints[static_cast<int>( Joints::ElbowLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT], m_joints[static_cast<int>( Joints::WristLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT], m_joints[static_cast<int>( Joints::HandLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT], m_joints[static_cast<int>( Joints::ShoulderRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT], m_joints[static_cast<int>( Joints::ElbowRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT], m_joints[static_cast<int>( Joints::WristRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT], m_joints[static_cast<int>( Joints::HandRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_HIP_LEFT], m_joints[static_cast<int>( Joints::HipLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT], m_joints[static_cast<int>( Joints::KneeLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_LEFT], m_joints[static_cast<int>( Joints::AnkleLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT], m_joints[static_cast<int>( Joints::FootLeft )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_HIP_RIGHT], m_joints[static_cast<int>( Joints::HipRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT], m_joints[static_cast<int>( Joints::KneeRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_RIGHT], m_joints[static_cast<int>( Joints::AnkleRight )] );
    copy( skeletonData.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT], m_joints[static_cast<int>( Joints::FootRight )] );

    m_numberOfTrackedPoints = 0;

    m_jointTrackState[static_cast<int>( Joints::Hip )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HIP_CENTER] );
    m_jointTrackState[static_cast<int>( Joints::Spine )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SPINE] );
    m_jointTrackState[static_cast<int>( Joints::ShoulderCenter )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SHOULDER_CENTER] );
    m_jointTrackState[static_cast<int>( Joints::Head )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HEAD] );
    m_jointTrackState[static_cast<int>( Joints::ShoulderLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SHOULDER_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::ElbowLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_ELBOW_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::WristLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_WRIST_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::HandLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::ShoulderRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SHOULDER_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::ElbowRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_ELBOW_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::WristRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_WRIST_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::HandRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::HipLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HIP_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::KneeLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_KNEE_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::AnkleLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_ANKLE_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::FootLeft )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_FOOT_LEFT] );
    m_jointTrackState[static_cast<int>( Joints::HipRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HIP_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::KneeRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_KNEE_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::AnkleRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_ANKLE_RIGHT] );
    m_jointTrackState[static_cast<int>( Joints::FootRight )] = static_cast<TrackState>( skeletonData.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_FOOT_RIGHT] );
}

/*!
   \fn SkeletonData::getJoints
   Returns a vector with all joints.
 */
const QVector<QVector3D>& SkeletonData::getJoints() const
{
    return m_joints;
}

/*!
   \fn SkeletonData::getJoint
   Returns the joint specified by \a joint.
   \see Skeleton::Joints
 */
const QVector3D& SkeletonData::getJoint( const SkeletonData::Joints joint ) const
{
    return m_joints.at( static_cast<int>( joint ) );
}

/*!
   \brief SkeletonData::jointTrackState
   Returns the TrackState of \a joint.
 */
const SkeletonData::TrackState SkeletonData::jointTrackState( const SkeletonData::Joints joint ) const
{
    return m_jointTrackState.at( static_cast<int>( joint ) );
}

/*!
   \brief SkeletonData::quality
   Returns the quality of the skeleton data.
   \see http://msdn.microsoft.com/en-us/library/nuisensor.nui_skeleton_data.aspx
 */
const SkeletonData::Quality SkeletonData::quality() const
{
    return m_quality;
}

/*!
   \brief SkeletonData::numberOfTrackedPoints
   Returns the nuber of points which are tracked.
 */
int SkeletonData::numberOfTrackedPoints() const
{
    return m_numberOfTrackedPoints;
}

/*!
   \brief SkeletonData::areMajorPointsTracked
   Returns true, if the following Joints are tracked:
   1. Hip
   2. Spine
   3. ShoulderCenter
 */
bool SkeletonData::areMajorPointsTracked() const
{
    if ( m_jointTrackState.at( static_cast<int>( Joints::Hip ) ) == TrackState::Tracked &&
         m_jointTrackState.at( static_cast<int>( Joints::Spine ) ) == TrackState::Tracked &&
         m_jointTrackState.at( static_cast<int>( Joints::ShoulderCenter) ) == TrackState::Tracked )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SkeletonData::initialize()
{
    for ( int i = 0; i < 20; ++i )
    {
        m_jointTrackState[i] = TrackState::Not_Tracked;
    }
}

/*!
   \fn copy
   Copies the data from \a source to \a target.
 */
void copy( const Vector4& source, QVector3D& target )
{
    target.setX( source.x );
    target.setY( source.y );
    target.setZ( source.z );
}

#include "../inc/SkeletonData.h"
#include <math.h>


/*!
   \fn SkeletonData::SkeletonData
   Constructs a SkeletonData object with all joints set to (0, 0, 0).
 */
SkeletonData::SkeletonData()
{
    m_joints.resize( 20 );
}

/*!
   \fn SkeletonData::SkeletonData( const NUI_SKELETON_DATA& skeletonData )
   Constructs a new SkeletonData object from the data provided by \a skeletonData.
 */
SkeletonData::SkeletonData( const NUI_SKELETON_DATA& skeletonData )
{
    m_joints.resize( 20 );
    setSkeletonBySkeletonData( skeletonData );
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
   \fn copy
   Copies the data from \a source to \a target.
 */
void copy( const Vector4& source, QVector3D& target )
{
    target.setX( source.x );
    target.setY( source.y );
    target.setZ( source.z );
}

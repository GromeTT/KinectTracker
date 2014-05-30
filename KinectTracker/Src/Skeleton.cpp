#include "../Inc/Skeleton.h"
#include "../Inc/Vertex.h"

/**
 * @class
 * Skeleton encapsulates twenty characteristic points of the human body.
 * The positions of these points is extracted from the NUI_SKELETON_DATA structure and
 * is given in meters.
 */

/**
  * \enum
  * This enum defines the different joints of the skeleton.
  *
  * \value Hip
  * \value Spine
  * \value ShoulderCenter
  * \value Head
  * \value ShoulderLeft
  * \value ElbowLeft
  * \value WristLeft
  * \value HandLeft
  * \value ShoulderRight
  * \value ElbowRight
  * \value WristRight
  * \value HandRight
  * \value HipLeft
  * \value KneeLeft
  * \value AnkleLeft
  * \value FootLeft
  * \value HipRight
  * \value KneeRight
  * \value AnkleRight
  * \value FootRight
  *
  * /

/**
 * @brief Skeleton::Skeleton
 * Creates an skeleton with random coordinates.
 */
Skeleton::Skeleton()
    : m_vertices( 20 )
{
}

/**
 * @brief Skeleton::Skeleton
 * Extracts the skeleton infromations from \a skeletonData and stores them.
 */
Skeleton::Skeleton( const NUI_SKELETON_DATA& skeletonData )
    : m_vertices( 20 )
{
    setSkeletonBySkeletonData( skeletonData );
}

/**
 * @brief Skeleton::~Skeleton
 * Destructor
 */
Skeleton::~Skeleton()
{
}

/**
 * @brief Skeleton::setSkeletonBySkeletonData
 * Extracts the skeleton infromations from \a skeletonData and stores them.
 */
void Skeleton::setSkeletonBySkeletonData( const NUI_SKELETON_DATA& skeletonData )
{
    fillVertex( m_vertices[Joints::Hip], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_HIP_CENTER ] );
    fillVertex( m_vertices[Joints::Spine], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_SPINE ] );
    fillVertex( m_vertices[Joints::ShoulderCenter], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_SHOULDER_CENTER ] );
    fillVertex( m_vertices[Joints::Head], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_HEAD ] );
    fillVertex( m_vertices[Joints::ShoulderLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_SHOULDER_LEFT ] );
    fillVertex( m_vertices[Joints::ElbowLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_ELBOW_LEFT ] );
    fillVertex( m_vertices[Joints::WristLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_WRIST_LEFT ] );
    fillVertex( m_vertices[Joints::HandLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_HAND_LEFT ] );
    fillVertex( m_vertices[Joints::ShoulderRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_SHOULDER_RIGHT ] );
    fillVertex( m_vertices[Joints::ElbowRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_ELBOW_RIGHT ] );
    fillVertex( m_vertices[Joints::WristRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_WRIST_RIGHT ] );
    fillVertex( m_vertices[Joints::HandRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_HAND_RIGHT ] );
    fillVertex( m_vertices[Joints::HipLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_HIP_LEFT ] );
    fillVertex( m_vertices[Joints::KneeLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_KNEE_LEFT ] );
    fillVertex( m_vertices[Joints::AnkleLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_ANKLE_LEFT ] );
    fillVertex( m_vertices[Joints::FootLeft], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_FOOT_LEFT ] );
    fillVertex( m_vertices[Joints::HipRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_HIP_RIGHT ] );
    fillVertex( m_vertices[Joints::KneeRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_KNEE_RIGHT ] );
    fillVertex( m_vertices[Joints::AnkleRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_ANKLE_RIGHT ] );
    fillVertex( m_vertices[Joints::FootRight], skeletonData.SkeletonPositions[ NUI_SKELETON_POSITION_FOOT_RIGHT ] );
}

/**
 * @brief Skeleton::getJoint
 * Returns the Vertex specified by \a joint.
 */
const Vertex Skeleton::getJoint( const Skeleton::Joints joint ) const
{
    return m_vertices.at( joint );
}

/**
 * @brief Skeleton::getJoints
 * Returns a vector with the positions of the particual characteristic points.
 */
const Vertices& Skeleton::getJoints() const
{
    return m_vertices;
}


void fillVertex( Vertex& vec, const Vector4& other )
{
    vec.x = other.x;
    vec.y = other.y;
    vec.z = other.z;
    vec.r = 1.0f;
}

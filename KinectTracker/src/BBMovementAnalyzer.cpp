#include "../inc/BBMovementAnalyzer.h"


/*!
   \brief BBMovementAnalyzer::BBMovementAnalyzer
   Standardconstructor.
 */
BBMovementAnalyzer::BBMovementAnalyzer( QObject* parent )
    : MovementAnalyzer( parent )
    , m_deltaX( 0.1f )
    , m_deltaY( 0.1f )
    , m_deltaZ( 0.1f )
{
    setObjectName( "BoudingBoxMovementAnalyzer" );
}

/*!
   \brief BBMovementAnalyzer::~BBMovementAnalyzer
   Destroyes the object.
 */
BBMovementAnalyzer::~BBMovementAnalyzer()
{

}

void BBMovementAnalyzer::setDeltaX( const float deltaX )
{
    m_deltaX = deltaX;
}

void BBMovementAnalyzer::setDeltaY( const float deltaY )
{
    m_deltaY = deltaY;
}

void BBMovementAnalyzer::setDeltaZ( const float deltaZ )
{
    m_deltaZ = deltaZ;
}

float BBMovementAnalyzer::deltaX() const
{
    return m_deltaX;
}

float BBMovementAnalyzer::deltaY() const
{
    return m_deltaY;
}

float BBMovementAnalyzer::deltaZ() const
{
    return m_deltaZ;
}

/*!
   \brief BBMovementAnalyzer::anaylzeV
   \see MovementAnalyzer::analyze
 */
void BBMovementAnalyzer::anaylzeV( const SkeletonDataPtr skeleton ,
                                   const unsigned int timestamp )
{
    // Store the lower body parts into a vector.
    QVector<QVector3D> lowerBody;
    lowerBody << skeleton->getJoint( SkeletonData::Joints::FootLeft );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::AnkleLeft );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::KneeLeft );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::FootRight);
    lowerBody << skeleton->getJoint( SkeletonData::Joints::AnkleRight );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::KneeRight );

    // Update the bounding box for the lower body.
    if ( m_boudingGeometries.first().isNull() ||
         !m_boudingGeometries.first()->m_geometry->arePointsInsideGeometry( lowerBody ) )
    {
        // Compute the BoundingBox if the vector of BoundingBoxes is empty
        // or if the person has left the previous one.
        BoundingGeometryPtr bb ( new BoundingBox ( lowerBody,
                                                   m_deltaX,
                                                   m_deltaY,
                                                   m_deltaZ ) );
        addBoundingGeometry( bb, timestamp );
    }
    else
    {
        // The person stayed in the volume of the previous BoundingBox,
        // only the timestamp has to be updated.
        BoundingGeometryPtr bb ( m_boudingGeometries.first()->m_geometry );
        addBoundingGeometry( bb, timestamp );
    }
}

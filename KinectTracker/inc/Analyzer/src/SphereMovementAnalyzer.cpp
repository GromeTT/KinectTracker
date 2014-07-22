#include "../inc/SphereMovementAnalyzer.h"

SphereMovementAnalyzer::SphereMovementAnalyzer( QObject* parent )
    : MovementAnalyzer( parent )
    , m_radius( 0.3f )
{

}

SphereMovementAnalyzer::~SphereMovementAnalyzer()
{

}

void SphereMovementAnalyzer::setRadius( const float radius )
{
    m_radius = radius;
    emit radiusChanged();
}

float SphereMovementAnalyzer::radius() const
{
    return m_radius;
}

void SphereMovementAnalyzer::analyzerV( const SkeletonDataPtr skeleton,
                                        const unsigned int timestamp )
{
    QVector<QVector3D> vec;
    vec.append( skeleton->getJoint(SkeletonData::Joints::Hip ) );
    // Update the bounding box for the lower body.
    if ( m_boudingGeometries.first().isNull() ||
         !m_boudingGeometries.first()->m_geometry->arePointsInsideGeometry( vec ) )
    {
        // Compute the BoundingBox if the vector of BoundingBoxes is empty
        // or if the person has left the previous one.
        BoundingGeometryPtr bb ( new BoundingSphere ( vec, m_radius ) );
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

void SphereMovementAnalyzer::resetV()
{

}

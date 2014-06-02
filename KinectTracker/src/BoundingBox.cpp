#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include "../inc/BoundingBox.h"
#include "../inc/Vertex.h"
#include "../inc/Intersection.h"

BoundingBox::BoundingBox()
    : m_width ( 0.0f )
    , m_height ( 0.0f )
    , m_depth ( 0.0f )
    , m_x( 0.0f )
    , m_y( 0.0f )
    , m_z( 0.0f )
{
}

BoundingBox::BoundingBox( const QVector<QVector3D>& points,
                          const float deltaW,
                          const float deltaD,
                          const float deltaH )
{
    if ( points.count() == 0 )
    {
        m_x = 0;
        m_y = 0;
        m_z = 0;
        m_width = 0;
        m_height = 0;
        m_depth = 0;
    }

    float maxW, minW;
    float maxD, minD;
    float maxH, minH;

    // Initialize values with first point
    maxW = minW = points.at( 0 ).x();
    maxD = minD = points.at( 0 ).z();
    maxH = minH = points.at( 0 ).y();

    for ( int i = 1; i < points.count(); ++i )
    {
        const QVector3D* v = &points.at( i );
        // Update width
        if ( v->x() > maxW )
        {
            maxW = v->x();
        }
        else if ( v->x() < minW )
        {
            minW = v->x();
        }

        // Update depth
        if ( v->z() > maxD )
        {
            maxD = v->z();
        }
        else if ( v->z() < minD )
        {
            minD = v->z();
        }

        // Update height
        if ( v->y() > maxH )
        {
            maxH = v->y();
        }
        else if ( v->y() < minH )
        {
            minH = v->y();
        }
    }
    maxW += deltaW;
    minW -= deltaW;
    maxH += deltaH;
    minH -= deltaH;
    maxD += deltaD;
    minD -= deltaD;

    // Calculate dimensions
    m_width =  maxW - minW;
    m_depth = maxD - minD;
    m_height = maxH - minH;

    // Calculate position
    m_x =  maxW - ( 0.5f * m_width );
    m_y =  maxH - ( 0.5f * m_height );
    m_z =  maxD - ( 0.5f * m_depth );
}

BoundingBox::BoundingBox( const BoundingBox& other )
    : m_width ( other.m_width )
    , m_height( other.m_height )
    , m_depth( other.m_depth )
    , m_x( other.m_x )
    , m_y( other.m_y )
    , m_z( other.m_z )
{

}

BoundingBox::~BoundingBox()
{
}

float BoundingBox::getDepth() const
{
    return m_depth;
}

float BoundingBox::getWidth() const
{
    return m_width;
}

float BoundingBox::getHeight() const
{
    return m_height;
}

float BoundingBox::getX() const
{
    return m_x;
}

float BoundingBox::getY() const
{
    return m_y;
}

float BoundingBox::getZ() const
{
    return m_z;
}

void BoundingBox::setDepth( const float depth )
{
    m_depth = depth;
}

void BoundingBox::setWidth( const float width )
{
    m_width = width;
}

void BoundingBox::setHeight( const float height )
{
    m_height = height;
}

void BoundingBox::setX( const float x )
{
    m_x = x;
}

void BoundingBox::setY( const float y )
{
    m_y = y;
}

void BoundingBox::setZ( const float z )
{
    m_z = z;
}

bool BoundingBox::isPointInBoundingBox( const QVector3D& point )
{
    return pointInCube( point.x(),
                        point.y(),
                        point.z(),
                        m_x,
                        m_y,
                        m_z,
                        m_width,
                        m_height,
                        m_depth );
}

bool BoundingBox::arePointsInBoundingBox( const QVector<QVector3D> points, const int count )
{
    for ( int i = 0; i < count; ++i )
    {
        if ( !isPointInBoundingBox( points[i] ) )
        {
            return false;
        }
    }
    return true;
}

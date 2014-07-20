#include "../inc/BoundingGeometry.h"
#include "../../OpenGL/inc/Vertex.h"
#include "../../Collision/inc/Intersection.h"
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>


/*!
   \brief BoundingGeometry::BoundingGeometry
   Standardconstructor.
   Sets the position to the origin.
 */
BoundingGeometry::BoundingGeometry()
    : m_x( 0 )
    , m_y( 0 )
    , m_z( 0 )
{
}

/*!
   \brief BoundingGeometry::BoundingGeometry
   Constructs a BoundingGeometry at ( x, y, z ).
 */
BoundingGeometry::BoundingGeometry( const float x,
                                    const float y,
                                    const float z )
    : m_x( x )
    , m_y( y )
    , m_z( z )
{
}

/*!
   \brief BoundingGeometry::~BoundingGeometry
   Destroyes the object.
 */
BoundingGeometry::~BoundingGeometry()
{
}


/*!
   \brief BoundingGeometry::x
   Returns the x-component of the position.
 */
float BoundingGeometry::x() const
{
    return m_x;
}

/*!
   \brief BoundingGeometry::y
   Returns the y-component of the position.
 */
float BoundingGeometry::y() const
{
    return m_y;
}

/*!
   \brief BoundingGeometry::z
   Returns the z-component of the position.
 */
float BoundingGeometry::z() const
{
    return m_z;
}

/*!
   \brief BoundingGeometry::setX
   Sets the position's x-component to \a x.
 */
void BoundingGeometry::setX( const float x )
{
    m_x = x;
}

/*!
   \brief BoundingGeometry::setY
   Sets the position's y-component to \a y.
 */
void BoundingGeometry::setY( const float y )
{
    m_y = y;
}

/*!
   \brief BoundingGeometry::setZ
   Sets the position's z-component to \a z.
 */
void BoundingGeometry::setZ( const float z )
{
    m_z = z;
}

/*!
   \brief BoundingGeometry::arePointsInsideGeometry
    Returns true, if all points of \a points are inside the geometry.
 */
bool BoundingGeometry::arePointsInsideGeometry( const QVector<QVector3D>& points )
{
    return arePointsInsideGeometryV( points );
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


BoundingBox::BoundingBox()
    : BoundingGeometry()
    , m_width  ( 0.0f )
    , m_height ( 0.0f )
    , m_depth  ( 0.0f )
{
}

BoundingBox::BoundingBox( const QVector<QVector3D>& points,
                          const float deltaW,
                          const float deltaD,
                          const float deltaH )
{
    calculateBoundingBox( points,
                          deltaW,
                          deltaD,
                          deltaH );
}

BoundingBox::BoundingBox( const BoundingBox& other )
    : m_width ( other.m_width )
    , m_height( other.m_height )
    , m_depth( other.m_depth )
{
    m_x = other.x();
    m_y = other.y();
    m_z = other.z();
}

BoundingBox::~BoundingBox()
{
}

float BoundingBox::depth() const
{
    return m_depth;
}

float BoundingBox::width() const
{
    return m_width;
}

float BoundingBox::height() const
{
    return m_height;
}

/*!
   \brief BoundingBox::frontFaceTopLeftCorner
   Returns the top left conrer of the front face.
 */
QVector3D BoundingBox::frontFaceTopLeftCorner()
{
    return QVector3D( m_x - m_width / 2,
                      m_y - m_height / 2,
                      m_z + m_depth / 2 );
}

/*!
   \brief BoundingBox::frontFaceBottomRightCorner
   Returns the bottom right corner of the front face.
 */
QVector3D BoundingBox::frontFaceBottomRightCorner()
{
    return QVector3D( m_x + m_width / 2,
                      m_y + m_height / 2,
                      m_z + m_depth / 2 );
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


/*!
    /fn void BoundingBox::calculateBoundingGeometryV( const QVector<QVector3D>& poinst, const float deltaW, const float deltaD, const float deltaH )
    Computes this BoundingBox so that it encloses the data provided by \a points.
    The remaning parameters can be used to enlarge the dimensions of the BoundingBox.
 */
void BoundingBox::calculateBoundingBox( const QVector<QVector3D>& points,
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

/*!
    \fn BoundingBox::arePointsInsideGeometryV( const QVector<QVector3D>& points )
    \see BoundingGeometry::arePointsInsideGeometry
 */
bool BoundingBox::arePointsInsideGeometryV( const QVector<QVector3D>& points )
{
    for ( int i = 0; i < points.count(); ++i )
    {
        if ( !pointInCube( points[i].x(),
                           points[i].y(),
                           points[i].z(),
                           m_x,
                           m_y,
                           m_z,
                           m_width,
                           m_height,
                           m_depth ) )
        {
            return false;
        }
    }
    return true;
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/
/*!
   \class This class encapsulates a BoundingBox object and an unsigned int to hold
          the timestemp.
*/

/*!
   \fn BoundingGeometryWithTimeStamp::BoundingBoxWithTimeStamp
   Constructs a QSharedPointer with an empty BoundingGeometryWithTimeStamp.
   The timestemp is set to \b zero.
 */
BoundingGeometryWithTimeStamp::BoundingGeometryWithTimeStamp()
    : m_geometry( nullptr )
    , m_timestamp( 0 )
{

}

/*!
  \fn BoundingGeometryWithTimeStamp::BoundingBoxWithTimeStamp( BoundingBoxPtr& boudingBox, unsigned int timestamp )
   Constructs a new BoundingBoxWithTimeStamp object.
   The BoundingBox is set to \a boundingBox and the timestamp to \a timestamp.
 */
BoundingGeometryWithTimeStamp::BoundingGeometryWithTimeStamp(  BoundingGeometry* geometry,
                                                               unsigned int timestamp )
    : m_geometry( BoundingGeometryPtr( geometry ) )
    , m_timestamp( timestamp )
{
}

BoundingGeometryWithTimeStamp::BoundingGeometryWithTimeStamp( BoundingGeometryPtr& geometry,
                                                              unsigned int timestamp )
    : m_geometry( geometry )
    , m_timestamp( timestamp )
{
}



/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


// TODO: Implement a bounding sphere algoritm.
BoundingSphere::BoundingSphere( const QVector<QVector3D>& points,
                                const float delta )
{
    Q_UNUSED( points );
    Q_UNUSED( delta );
}

/*!
   \brief BoundingSphere::BoundingSphere
   Creates a Sphere at \a x, \a y, \a z and radius \a r.
 */
BoundingSphere::BoundingSphere( const float x,
                                const float y,
                                const float z,
                                const float r )
    : m_x( x )
    , m_y( y )
    , m_z( z )
    , m_r( r )
{
}

/*!
   \brief BoundingSphere::~BoundingSphere
   Destoryes the object.
 */
BoundingSphere::~BoundingSphere()
{

}

/*!
   \brief BoundingSphere::arePointsInsideGeometry
   \see BoundingGeometry::arePointsInsideGeometry
 */
bool BoundingSphere::arePointsInsideGeometryV( const QVector<QVector3D>& points )
{
    for ( int i = 0; i < points.count(); ++i )
    {
        if ( pointInSphere( points.at( i ).x(),
                            points.at( i ).y(),
                            points.at( i ).z(),
                            m_x,
                            m_y,
                            m_z,
                            m_r ) )
        {
             return true;

        }
    }
    return false;
}

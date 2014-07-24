#include "../inc/AMath.h"

float AMath::radToDegF(const float rad)
{
    return rad*factorRadianToDegree;
}

double AMath::radToDegD(const double rad)
{
    return rad*factorRadianToDegree;
}

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

AMath::Circle2D::Circle2D()
    : m_x( 0 )
    , m_y( 0 )
    , m_radius( 0 )
{
}

AMath::Circle2D::Circle2D( const float x,
                           const float y,
                           const float r )
    : m_x( x )
    , m_y( y )
    , m_radius( r )
{
}

AMath::Circle2D::~Circle2D()
{
}

float AMath::Circle2D::x() const
{
    return m_x;
}

float AMath::Circle2D::y() const
{
    return m_y;
}

float AMath::Circle2D::radius() const
{
    return m_radius;
}

void AMath::Circle2D::setX( const float x )
{
    m_x = x;
}

void AMath::Circle2D::setY( const float y )
{
    m_y = y;
}

void AMath::Circle2D::setRadius( const float radius )
{
    m_radius = radius;
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
   \brief AMath::Rectangle3D::Rectangle3D
   Constructs a rectangle with it's center at (0, 0, 0) with a width and heigt of zero.
 */
AMath::Rectangle3D::Rectangle3D()
    : m_x( 0 )
    , m_y( 0 )
    , m_z( 0 )
    , m_width( 0 )
    , m_height( 0 )
{

}

/*!
   \brief AMath::Rectangle3D::Rectangle3D
   Constructs a rectangle with it's center at ( \a x, \a y, \a z) with a height and
   width of zero.
 */
AMath::Rectangle3D::Rectangle3D( const float x,
                                 const float y,
                                 const float z )
    : m_x( x )
    , m_y( y )
    , m_z( z )
    , m_height( 0 )
    , m_width( 0 )
{

}

/*!
   \brief AMath::Rectangle3D::Rectangle3D
    Constructs a rectangle with it's center at ( \a x, \a y, \a z) and the given \a width
    and \a height.
 */
AMath::Rectangle3D::Rectangle3D( const float x,
                                 const float y,
                                 const float z,
                                 const float width,
                                 const float height )
    : m_x( x )
    , m_y( y )
    , m_z( z )
    , m_width( width )
    , m_height( height )
{
}

/*!
   \brief AMath::Rectangle3D::~Rectangle3D
   Destroyes the object.
 */
AMath::Rectangle3D::~Rectangle3D()
{

}

/*!
   \brief AMath::Rectangle3D::setByTopLeftAndBottomRight
 */
void AMath::Rectangle3D::setByTopLeftAndBottomRight( const QVector3D& topLeftCorner,
                                                     const QVector3D& bottomRightCorner )
{
    m_width  = fabs( topLeftCorner.x() - bottomRightCorner.x() );
    m_height = fabs( bottomRightCorner.y() - topLeftCorner.y() );
    m_x = topLeftCorner.x() + m_width / 2;
    m_y = topLeftCorner.y() - m_height / 2;
    m_z = topLeftCorner.z();
}

/*!
   \brief AMath::Rectangle3D::move
   Sets the center of the rectangle to (\a x, \a y, \a z).
 */
void AMath::Rectangle3D::move( const float x,
                               const float y,
                               const float z )
{
    m_x = x;
    m_y = y;
    m_z = z;
}

/*!
   \brief AMath::Rectangle3D::setWidth
   Sets the width to \a width.
 */
void AMath::Rectangle3D::setWidth( const float width )
{
    m_width = width;
}

/*!
   \brief AMath::Rectangle3D::setHeight
   Sets the height to \a height.
 */
void AMath::Rectangle3D::setHeight( const float height )
{
    m_height = height;
}

/*!
   \brief AMath::Rectangle3D::resize
   Sets the width to \a width and the height to \a height.
 */
void AMath::Rectangle3D::resize( const float width,
                                 const float height )
{
    m_width = width;
    m_height = height;
}

/*!
   \brief AMath::Rectangle3D::width
   Returns the width of the rectangle.
 */
float AMath::Rectangle3D::width() const
{
    return m_width;
}

/*!
   \brief AMath::Rectangle3D::height
   Returns the height of the rectangle.
 */
float AMath::Rectangle3D::height() const
{
    return m_height;
}

/*!
   \brief AMath::Rectangle3D::center
   Returns the coordinates of the center.
 */
QVector3D AMath::Rectangle3D::center() const
{
    return QVector3D( m_x, m_y, m_z );
}

/*!
   \brief AMath::Rectangle3D::topLeftCorner
   Returns the coordinates of the top left conrner.
 */
QVector3D AMath::Rectangle3D::topLeftCorner() const
{
    return QVector3D( m_x - m_width/2,
                      m_y + m_height/2,
                      m_z );
}

/*!
   \brief AMath::Rectangle3D::bottomRightCorner
   Returns the coordinates of the bottom right corner.
 */
QVector3D AMath::Rectangle3D::bottomRightCorner() const
{
    return QVector3D( m_x + m_width/2,
                      m_y - m_height/2,
                      m_z );
}


/*!
   \brief AMath::anglesFromSphericalCoordinates
  Computes the angles of \a direction in spherical coordinates and saves them
  into \a phi and \a theta.
 */
void AMath::anglesFromSphericalCoordinates( float& phi, float& theta, const QVector3D& direction )
{
    // http://de.wikipedia.org/wiki/Polarkoordinaten
    phi  = AMath::radToDegF( atan2( direction.z(), direction.x() ) );
    theta = AMath::radToDegF( asinf( direction.y() / direction.length() ) );
}

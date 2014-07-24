#include "../inc/Camera.h"
#include <QDebug>

Camera::Camera()
    : m_x( 0.0f )
    , m_y( 0.0f )
    , m_z( 0.0f )
    , m_roll( 0.0f )
    , m_pitch( 0.0f )
    , m_yaw( 0.0f )
    , m_recalculateMatrix( true )
    , m_position( 0.0f, 0.0f, 0.0f )
    , m_forward( 0.0f, 0.0f, -1.0f  ) // Looks
    , m_right( 1.0f, 0.0f, 0.0f  )
    , m_up( 0.0f, 1.0f, 0.0f )

{
    setObjectName( "Camera" );
    m_cameraMatrix.setToIdentity();
}

Camera::~Camera()
{

}

void Camera::setX( const float x )
{
    m_x = x;
    m_recalculateMatrix = true;
    emit xChanged();
}

void Camera::setY( const float y )
{
    m_y = y;
    m_recalculateMatrix = true;
    emit yChanged();
}

void Camera::setZ( const float z )
{
    m_z = z;
    m_recalculateMatrix = true;
    emit zChanged();
}

/*!
   \brief Camera::moveForward
   Moves the camerea by \a distance into the looking direction.
 */
void Camera::moveForward( const float distance )
{
    m_position += m_forward * distance;
    m_recalculateMatrix = true;
}

void Camera::setRoll( const float roll )
{
    m_roll = roll;
    updateOrientation();
    m_recalculateMatrix = true;
    emit rollChanged();
}

void Camera::setPitch( const float pitch )
{
    m_pitch = pitch;
    updateOrientation();
    m_recalculateMatrix = true;
    emit pitchChanged();
}

void Camera::setYaw( const float yaw )
{
    m_yaw = yaw;
    updateOrientation();
    m_recalculateMatrix = true;
    emit yawChanged();
}

void Camera::roll( const float angle )
{
    m_roll += angle ;
    updateOrientation();
    m_recalculateMatrix = true;
    emit rollChanged();
}

void Camera::pitch( const float angle )
{
    m_pitch += angle ;
    updateOrientation();
    m_recalculateMatrix = true;
    emit pitchChanged();
}

void Camera::yaw( const float angle )
{
    m_yaw += angle ;
    updateOrientation();
    m_recalculateMatrix = true;
    emit yawChanged();
}

void Camera::moveToPosition( const float x,
                             const float y,
                             const float z )
{
    setX( x );
    setY( y );
    setZ( z );
}

void Camera::moveUp( const float distance )
{
    m_position += m_up * distance;
    m_recalculateMatrix = true;
}

void Camera::stride( const float distance )
{
    m_position += m_right * distance;
    m_recalculateMatrix = true;
}

float Camera::x() const
{
    return m_x;
}

float Camera::y() const
{
    return m_y;
}

float Camera::z() const
{
    return m_z;
}

float Camera::roll() const
{
    return m_roll;
}

float Camera::pitch() const
{
    return m_pitch;
}

float Camera::yaw() const
{
    return m_yaw;
}

const QMatrix4x4& Camera::cameraMatrix() const
{
    if ( m_recalculateMatrix )
    {
        m_cameraMatrix.setToIdentity();
        m_cameraMatrix.translate( m_position );
        m_cameraMatrix = m_cameraMatrix * m_rotationMatrix;
        m_cameraMatrix = m_cameraMatrix.inverted();  // From camera matrix to view matrix.
        m_recalculateMatrix = false;
    }
    return m_cameraMatrix;
}

void Camera::updateOrientation()
{
    m_rotationMatrix.setToIdentity();
    m_rotationMatrix.rotate( m_roll, 0, 0, 1 );
    m_rotationMatrix.rotate( m_pitch, 1, 0, 0 );
    m_rotationMatrix.rotate( m_yaw, 0, 1, 0 );

    // TODO: Optimize this.
    m_forward = m_rotationMatrix * QVector3D( 0, 0, -1 );
    m_up      = m_rotationMatrix * QVector3D( 0, 1, 0 );
    m_right   = m_rotationMatrix * QVector3D( 1, 0, 0 );

    m_forward.normalize();
    m_up.normalize();
    m_right.normalize();
}

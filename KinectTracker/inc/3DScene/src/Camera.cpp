#include "../inc/Camera.h"


Camera::Camera()
    : m_x( 0.0f )
    , m_y( 0.0f )
    , m_z( 0.0f )
    , m_roll( 0.0f )
    , m_pitch( 0.0f )
    , m_yaw( 0.0f )
    , m_recalculateMatrix( true )

{
    setObjectName( "Camera" );
    m_cameraMatrix.setToIdentity();
}

Camera::~Camera()
{

}

void Camera::setX( const float x )
{
    if ( m_x != x )
    {
        m_x = x;
        m_recalculateMatrix = true;
        emit xChanged();
    }
}

void Camera::setY( const float y )
{
    if ( m_y != y )
    {
        m_y = y;
        m_recalculateMatrix = true;
        emit yChanged();
    }
}

void Camera::setZ( const float z )
{
    if ( m_z != z )
    {
        m_z = z;
        m_recalculateMatrix = true;
        emit zChanged();
    }
}

void Camera::moveX( const float x )
{
    m_x += x;
    m_recalculateMatrix = true;
    emit xChanged();
}

void Camera::moveY( const float y )
{
    m_y += y;
    m_recalculateMatrix = true;
    emit yChanged();
}

void Camera::moveZ( const float z )
{
    m_z += z;
    m_recalculateMatrix = true;
    emit zChanged();
}

void Camera::setRoll( const float roll )
{
    if ( m_roll != roll )
    {
        m_roll = roll;
        m_recalculateMatrix = true;
        emit rollChanged();
    }
}

void Camera::setPitch( const float pitch )
{
    if ( m_pitch != pitch )
    {
        m_pitch = pitch;
        m_recalculateMatrix = true;
        emit pitchChanged();
    }
}

void Camera::setYaw( const float yaw )
{
    if ( m_yaw != yaw)
    {
        m_yaw = yaw;
        m_recalculateMatrix = true;
        emit yawChanged();
    }
}

void Camera::roll( const float angle )
{
    m_roll += angle ;
    m_recalculateMatrix = true;
    emit rollChanged();
}

void Camera::pitch( const float angle )
{
    m_pitch += angle ;
    m_recalculateMatrix = true;
    emit pitchChanged();
}

void Camera::yaw( const float angle )
{
    m_yaw += angle ;
    m_recalculateMatrix = true;
    emit yawChanged();
}

void Camera::move( const float x,
                   const float y,
                   const float z )
{
    moveX( x );
    moveY( y );
    moveZ( z );
}

void Camera::moveToPosition( const float x,
                             const float y,
                             const float z )
{
    setX( x );
    setY( y );
    setZ( z );
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
        m_cameraMatrix.rotate( m_roll, 0.0f, 0.0f, 1.0f );
        m_cameraMatrix.rotate( m_yaw, 0.0f, 1.0f, 0.0f );
        m_cameraMatrix.rotate( m_pitch, 1.0f, 0.0f, 0.0f );
        QMatrix4x4 translation;
        translation.translate( m_x, m_y, m_z );
        m_cameraMatrix = m_cameraMatrix * translation;
        m_recalculateMatrix = false;
    }
    return m_cameraMatrix;
}

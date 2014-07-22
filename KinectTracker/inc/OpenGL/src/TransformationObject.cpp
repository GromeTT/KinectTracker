#include "../Inc/TransformationObject.h"


TransformationObject::TransformationObject( TransformationObject* parent )
    : QObject( parent )
    , mp_parent( parent )
    , m_roll( 0.0 )
    , m_pitch( 0.0f )
    , m_yaw( 0.0f )
    , m_x( 0.0f )
    , m_y( 0.0f )
    , m_z( 0.0f )
    , m_xScale( 1.0f )
    , m_yScale( 1.0f )
    , m_zScale( 1.0f )
    , m_recalculateMatrix( true )
    , m_visible( true )
{

}

TransformationObject::~TransformationObject()
{

}

void TransformationObject::setPosition( const QVector3D& position )
{
    m_x = position.x();
    m_y = position.y();
    m_z = position.z();
    m_recalculateMatrix = true;
}

void TransformationObject::setPosition( const float x,
                                        const float y,
                                        const float z )
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_recalculateMatrix = true;
}

void TransformationObject::setRollPitchYaw( const QVector3D& rotation )
{
    m_recalculateMatrix = true;
    m_roll  = rotation.x();
    m_pitch = rotation.y();
    m_yaw   = rotation.z();
}

void TransformationObject::rollPitchYaw( const QVector3D& rotation )
{
    m_recalculateMatrix = true;
    m_roll  += rotation.x();
    m_pitch += rotation.y();
    m_yaw   += rotation.z();
}

void TransformationObject::setScale( const QVector3D& scale )
{
    m_recalculateMatrix = true;
    m_xScale = scale.x();
    m_yScale = scale.y();
    m_zScale = scale.z();
}

void TransformationObject::setX( const float x )
{
    m_recalculateMatrix = true;
    m_x = x;
}

void TransformationObject::setY( const float y )
{
    m_recalculateMatrix = true;
    m_y = y;
}

void TransformationObject::setZ( const float z )
{
    m_recalculateMatrix = true;
    m_z = z;
}

void TransformationObject::setRoll( const float roll )
{
    m_recalculateMatrix = true;
    m_roll = roll;
}

void TransformationObject::setPitch( const float pitch )
{
    m_recalculateMatrix = true;
    m_pitch += pitch;
}

void TransformationObject::setYaw( const float yaw )
{
    m_recalculateMatrix = true;
    m_yaw = yaw;
}

void TransformationObject::setScaleX( const float xScale )
{
    m_recalculateMatrix = true;
    m_xScale = xScale;
}

void TransformationObject::setScaleY( const float yScale )
{
    m_recalculateMatrix = true;
    m_yScale = yScale;
}

void TransformationObject::setScaleZ( const float zScale )
{
    m_recalculateMatrix = true;
    m_zScale = zScale;
}

void TransformationObject::setScale( const float x,
                                     const float y,
                                     const float z )
{
    m_recalculateMatrix = true;
    m_xScale = x;
    m_yScale = y;
    m_zScale = z;
}

void TransformationObject::setVisible( const bool visible )
{
    if ( m_visible != visible )
    {
        m_visible = visible;
    }
}

float TransformationObject::x() const
{
    return m_x;
}

float TransformationObject::y() const
{
    return m_y;
}

float TransformationObject::z() const
{
   return m_z;
}

float TransformationObject::roll() const
{
   return m_roll;
}

float TransformationObject::pitch() const
{
   return m_pitch;
}

float TransformationObject::yaw() const
{
     return m_yaw;
}

float TransformationObject::scaleX() const
{
 return m_xScale;
}

float TransformationObject::scaleY() const
{
   return m_yScale;
}

float TransformationObject::scaleZ() const
{
   return m_zScale;
}

bool TransformationObject::visible() const
{
   return m_visible;
}

/**
 * @brief TransformationObject::getModelMatrix
 * Constructs a column major model model matrix.
 * @return
 * Column major model matrix.
 */
const QMatrix4x4& TransformationObject::getModelMatrix() const
{
    if ( m_recalculateMatrix )
    {
        m_modelMatrix.setToIdentity();
        QMatrix4x4 trans;
        trans.translate( m_x, m_y, m_z );
        QMatrix4x4 rot;
        rot.rotate( m_roll, 0.0f, 0.0f, 1.0f );
        rot.rotate( m_pitch, 1.0f, 0.0f, 0.0f );
        rot.rotate( m_yaw, 0.0f, 1.0f, 0.0f );
        QMatrix4x4 scale;
        scale.scale( m_xScale, m_yScale, m_zScale );
        m_modelMatrix = trans*rot*scale;
        m_recalculateMatrix = false;
    }
    return m_modelMatrix;
}


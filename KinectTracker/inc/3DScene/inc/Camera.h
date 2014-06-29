#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QMatrix4x4>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();
    virtual ~Camera();

    void setX( const float x );
    void setY( const float y );
    void setZ( const float z );
    void moveX( const float x );
    void moveY( const float y );
    void moveZ( const float z );
    void setRoll( const float roll );
    void setPitch( const float pitch );
    void setYaw( const float yaw );
    void roll( const float angle );
    void pitch( const float angle );
    void yaw( const float angle );
    void move( const float x,
               const float y,
               const float z );
    void moveToPosition( const float x,
                         const float y,
                         const float z );

    float x() const;
    float y() const;
    float z() const;
    float roll() const;
    float pitch() const;
    float yaw() const;
    const QMatrix4x4& cameraMatrix() const;

signals:
    void xChanged();
    void yChanged();
    void zChanged();
    void rollChanged();
    void pitchChanged();
    void yawChanged();

private:
    float m_x;
    float m_y;
    float m_z;
    float m_roll;
    float m_pitch;
    float m_yaw;
    mutable QMatrix4x4 m_cameraMatrix;
    mutable bool m_recalculateMatrix;


    Q_PROPERTY( float x MEMBER m_x
                READ x
                WRITE setX
                NOTIFY xChanged )
    Q_PROPERTY( float y MEMBER m_y
                READ y
                WRITE setY
                NOTIFY yChanged )
    Q_PROPERTY( float z MEMBER m_z
                READ z
                WRITE setZ
                NOTIFY zChanged )
    Q_PROPERTY( float roll MEMBER m_roll
                READ roll
                WRITE setRoll
                NOTIFY rollChanged )
    Q_PROPERTY( float pitch MEMBER m_pitch
                READ pitch
                WRITE setPitch
                NOTIFY pitchChanged )
    Q_PROPERTY( float yaw MEMBER m_yaw
                READ yaw
                WRITE setYaw
                NOTIFY yawChanged )
};

#endif // CAMERA_H

#ifndef TRANSFORMATIONOBJECT_H
#define TRANSFORMATIONOBJECT_H

#include <QObject>
#include <QMatrix4x4>

class TransformationObject : public QObject
{
    Q_OBJECT

public:
    TransformationObject( TransformationObject* parent );
    virtual ~TransformationObject();

    void setPosition( const QVector3D& position );
    void setPosition( const float x, const float y, const float z );
    void setRollPitchYaw( const QVector3D& rotation );
    void rollPitchYaw( const QVector3D& rotation );
    void setScale( const QVector3D& scale );
    void setX( const float x );
    void setY( const float y );
    void setZ( const float z );
    void setRoll( const float roll );
    void setPitch( const float pitch );
    void setYaw( const float yaw );
    void setScaleX( const float xScale );
    void setScaleY( const float yScale );
    void setScaleZ( const float zScale );
    void setScale( const float x, const float y, const float z );
    void setVisible( const bool visible );
    void setForward( const QVector3D& lookAt );
    void setUp( const QVector3D& up );
    void updateOrientation();

    float             x() const;
    float             y() const;
    float             z() const;
    float             roll() const;
    float             pitch() const;
    float             yaw() const;
    float             scaleX() const;
    float             scaleY() const;
    float             scaleZ() const;
    bool              visible() const;
    const QMatrix4x4& getModelMatrix() const;
    QVector3D         forward() const;
    QVector3D         up() const;
    QVector3D         right() const;

private:
    mutable QMatrix4x4    m_modelMatrix;
    QMatrix4x4            m_rot;
    TransformationObject* mp_parent;
    mutable bool          m_recalculateMatrix;
    bool                  m_visible;
    float                 m_x;
    float                 m_y;
    float                 m_z;
    float                 m_roll;
    float                 m_pitch;
    float                 m_yaw;
    float                 m_xScale;
    float                 m_yScale;
    float                 m_zScale;
    QVector3D             m_forward;
    QVector3D             m_up;
    QVector3D             m_right;

signals:
    void xChanged();
    void yChanged();
    void zChanged();
    void rollChanged();
    void pitchChanged();
    void yawChanged();
    void xScaleChanged();
    void yScaleChanged();
    void zScaleChanged();
    void visibleChanged();

private:
    Q_PROPERTY( float x MEMBER m_x
                READ x
                WRITE setX
                NOTIFY xChanged)

    Q_PROPERTY( float y MEMBER m_y
                READ y
                WRITE setY
                NOTIFY yChanged)

    Q_PROPERTY( float z MEMBER m_z
                READ z
                WRITE setZ
                NOTIFY zChanged )

    Q_PROPERTY( float roll MEMBER m_roll
                READ roll
                WRITE setRoll
                NOTIFY rollChanged )

    Q_PROPERTY( float yaw MEMBER m_yaw
                READ yaw
                WRITE setYaw
                NOTIFY yawChanged )

    Q_PROPERTY( float pitch MEMBER m_pitch
                READ pitch
                WRITE setPitch
                NOTIFY pitchChanged )

    Q_PROPERTY( float xScale MEMBER m_xScale
                READ scaleX
                WRITE setScaleX
                NOTIFY xScaleChanged )

    Q_PROPERTY( float yScale MEMBER m_yScale
                READ scaleY
                WRITE setScaleY
                NOTIFY yScaleChanged )

    Q_PROPERTY( float zScale MEMBER m_zScale
                READ scaleZ
                WRITE setScaleZ
                NOTIFY zScaleChanged )

    Q_PROPERTY( bool visible MEMBER m_visible
                READ visible
                WRITE setVisible
                NOTIFY visibleChanged )
};

#endif // TRANSFORMATIONOBJECT_H

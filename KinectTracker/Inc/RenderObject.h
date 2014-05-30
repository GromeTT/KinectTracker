#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <QOpenGLBuffer>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QObject>
#include <QSharedPointer>

class Vertex;
class QOpenGLShaderProgram;
class QOpenGLContext;

typedef QVector<Vertex> Vertices;
typedef QVector<unsigned int> Indices;
typedef QSharedPointer<QOpenGLContext> OpenGLContext;

class RenderObject : public QObject
{
    Q_OBJECT

public:
    RenderObject( OpenGLContext& context,
                  RenderObject* parent = nullptr );
    ~RenderObject();

    virtual void render( const QMatrix4x4& projection,
                         const QMatrix4x4& view );

    void setVertices( const Vertices& vertices );
    void setIndices( const Indices& indices );
    void setShaderProgram ( QOpenGLShaderProgram* program );
    void setPosition( const QVector3D& position );
    void setPosition( const float x, const float y, const float z );
    void setRollPitchYaw( const QVector3D& rotation );
    void rollPitchYaw( const QVector3D& rotation );
    void setScale( const QVector3D& scale );
    void setRenderMode( const GLenum renderMode );
    void setTexture( QOpenGLTexture* texture );
    void setTexture1( QOpenGLTexture* texture );
    void setUseTexture( const bool useTexture );
    void setUseTexutre1( const bool useTexture );
    void setWireFrameMode( const bool wireFrameMode );

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

    float getX() const;
    float getY() const;
    float getZ() const;
    float roll() const;
    float pitch() const;
    float yaw() const;
    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;
    bool  isVisible() const;

    // TODO: QVector3D durch float x, y, z ersetzen.
    //       Gedanken über eine generische Lösung machen,
    //       damit float durch double etc. ersetzt werden kann.
    const Vertices&     getVertices() const;
    const QMatrix4x4&   getModelMatrix() const;
    GLenum              getRenderMode() const;
    bool                getUseTexture() const;
    bool                isWireFrameModeOn() const;
    QOpenGLTexture*     getTexture();

public:
    RenderObject*               mp_parent;
    mutable bool                m_recalculateMatrix;
    bool                        m_useTexture;
    bool                        m_useTexture1;
    bool                        m_wireFrameMode;
    bool                        m_visible;
    QOpenGLVertexArrayObject    m_vao;
    QOpenGLShaderProgram*       mp_shaderProgram;
    QOpenGLBuffer               m_vertexBuffer;
    QOpenGLBuffer               m_indexBuffer;
    Vertices                    m_vertices;
    Indices                     m_indices;
    mutable QMatrix4x4          m_modelMatrix;
    GLenum                      m_renderMode;
    QOpenGLTexture*             mp_texture;
    QOpenGLTexture*             mp_texture1;
    OpenGLContext               m_context;

    float m_x, m_y, m_z;
    float m_roll, m_pitch, m_yaw;
    float m_xScale, m_yScale, m_zScale;

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
    void useWireFrameModeChanged();
    void visibleChanged();

private:
    Q_PROPERTY( float x MEMBER m_x
                READ getX
                WRITE setX
                NOTIFY xChanged)

    Q_PROPERTY( float y MEMBER m_y
                READ getY
                WRITE setY
                NOTIFY yChanged)

    Q_PROPERTY( float z MEMBER m_z
                READ getZ
                WRITE setZ
                NOTIFY zChanged)

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
                READ getScaleX
                WRITE setScaleX
                NOTIFY xScaleChanged )

    Q_PROPERTY( float yScale MEMBER m_yScale
                READ getScaleY
                WRITE setScaleY
                NOTIFY yScaleChanged )

    Q_PROPERTY( float zScale MEMBER m_zScale
                READ getScaleZ
                WRITE setScaleZ
                NOTIFY zScaleChanged )

    Q_PROPERTY( bool wireFrameMode MEMBER m_wireFrameMode
                READ isWireFrameModeOn
                WRITE setWireFrameMode
                NOTIFY useWireFrameModeChanged )

    Q_PROPERTY( bool visible MEMBER m_visible
                READ isVisible
                WRITE setVisible
                NOTIFY visibleChanged )
};

#endif // RENDEROBJECT_H

#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <QOpenGLBuffer>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QSharedPointer>
#include "RenderObjectInterface.h"

class Vertex;
class QOpenGLShaderProgram;
class QOpenGLContext;

typedef QSharedPointer<QOpenGLContext> OpenGLContext;
typedef QVector<Vertex> Vertices;
typedef QVector<unsigned int> Indices;
typedef QVector<QOpenGLTexture*> OpenGLTextures;

class RenderObject : public RenderObjectInterface
{
    Q_OBJECT

public:
    RenderObject( OpenGLContext& context,
                  RenderObject* parent = nullptr );
    virtual ~RenderObject();

    void setVertices( const Vertices& vertices );
    void setIndices( const Indices& indices );
    void setShaderProgram ( QOpenGLShaderProgram* program );
    void setRenderMode( const GLenum renderMode );
    void setTexture( QOpenGLTexture* texture, const int i );
    void updateTexture( const QOpenGLTexture::TextureFormat textureFormat,
                        const int width,
                        const int height,
                        const QOpenGLTexture::PixelFormat pixelFormat,
                        const QOpenGLTexture::PixelType pixelType,
                        const int texture,
                        void* data,
                        const QOpenGLTexture::Filter minificationFilter = QOpenGLTexture::Linear,
                        const QOpenGLTexture::Filter magnificationFilter = QOpenGLTexture::Linear );
    void setWireFrameMode( const bool wireFrameMode );
    void setUseTexture( const bool useTexture );
    void setTextureActive( const int i , const bool active );

    bool                useTexture() const;
    bool                textureActive( const int i ) const;
    const Vertices&     getVertices() const;
    GLenum              getRenderMode() const;
    bool                isWireFrameModeOn() const;
    QOpenGLTexture*     getTexture( const unsigned short i );

private:
    virtual void                renderV( const QMatrix4x4& projection,
                                         const QMatrix4x4& view );

    RenderObject*               mp_parent;
    QOpenGLVertexArrayObject    m_vao;
    QOpenGLShaderProgram*       mp_shaderProgram;
    QOpenGLBuffer               m_vertexBuffer;
    QOpenGLBuffer               m_indexBuffer;
    Vertices                    m_vertices;
    Indices                     m_indices;
    OpenGLContext               m_context;
    OpenGLTextures              m_textures;
    QVector<bool>               m_activeTextures;
    GLenum                      m_renderMode;
    bool                        m_useTexture;
    bool                        m_wireFrameMode;
    static const int            m_maxTexturesCount = 3;

signals:
    void useWireFrameModeChanged();
    void useTextureChanged();

private:
    Q_PROPERTY( bool wireFrameMode MEMBER m_wireFrameMode
                READ isWireFrameModeOn
                WRITE setWireFrameMode
                NOTIFY useWireFrameModeChanged )

    Q_PROPERTY( bool useTexture MEMBER m_useTexture
                READ useTexture
                WRITE setUseTexture
                NOTIFY useTextureChanged )
};


#endif // RENDEROBJECT_H

#include "../Inc/RenderObject.h"
#include "../Inc/Vertex.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QThread>
#include <QDebug>

RenderObject::RenderObject( OpenGLContext& context,
                            RenderObject* parent )
    : QObject( parent )
    , mp_parent( parent )
    , mp_shaderProgram( nullptr )
    , m_xRotation( 0.0 ), m_yRotation( 0.0f ), m_zRotation( 0.0f )
    , m_x( 0.0f ), m_y( 0.0f ), m_z( 0.0f )
    , m_xScale( 1.0f ), m_yScale( 1.0f ), m_zScale( 1.0f )
    , m_recalculateMatrix( true )
    , m_renderMode( GL_TRIANGLES )
    , m_vertexBuffer( QOpenGLBuffer::VertexBuffer )
    , m_indexBuffer( QOpenGLBuffer::IndexBuffer )
    , mp_texture( 0 )
    , mp_texture1( 0 )
    , m_useTexture( false )
    , m_useTexture1( false )
    , m_wireFrameMode( false )
    , m_context( context )
    , m_visible( true )
{
    m_vao.create();

    setPosition( QVector3D (0, 0, 0 ) );
}

RenderObject::~RenderObject()
{
}

void RenderObject::render( const QMatrix4x4& projection,
                           const QMatrix4x4& view )
{
    if ( !m_visible )
    {
        return;
    }
    if ( !mp_shaderProgram )
    {
        return;
    }
    m_vao.bind();
    mp_shaderProgram->bind();

    if ( mp_texture )
    {
        m_context->functions()->glActiveTexture( GL_TEXTURE0 );
        mp_texture->bind();
        m_context->functions()->glActiveTexture( GL_TEXTURE1 );
        mp_texture1->bind();
    }

    if ( m_wireFrameMode )
    {
        // Wireframe mode
        glPolygonMode( GL_FRONT, GL_LINE );
        glPolygonMode( GL_BACK, GL_LINE );
    }
    else
    {
        glPolygonMode( GL_FRONT, GL_FILL );
        glPolygonMode( GL_BACK, GL_FILL );
    }

    mp_shaderProgram->setUniformValue( "viewMatrix", view );
    mp_shaderProgram->setUniformValue( "projectionMatrix", projection );
    mp_shaderProgram->setUniformValue( "modelMatrix", getModelMatrix() );
    mp_shaderProgram->setUniformValue( "useTexture", m_useTexture );
    mp_shaderProgram->setUniformValue( "useSecondTexture", m_useTexture1 );

    glDrawElements( m_renderMode, m_indices.size(), GL_UNSIGNED_INT, 0 );

    m_vao.release();
}

void RenderObject::setVertices( const Vertices& vertices )
{
    m_vertices.clear();
    for ( int i = 0; i < vertices.count(); ++i )
    {
        m_vertices.append( vertices.at( i ) );
    }
    if ( !m_vertexBuffer.isCreated() )
    {
        m_vertexBuffer.create();
    }
    m_vao.bind();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate( m_vertices.data(), m_vertices.count() * sizeof( Vertex ) );
    m_vao.release();
}

void RenderObject::setIndices( const Indices& indices )
{
    m_indices.clear();
    for ( int i = 0; i < indices.count(); ++i )
    {
        m_indices.append( indices.at( i ) );
    }
    if ( !m_indexBuffer.isCreated() )
    {
        m_indexBuffer.create();
    }

    m_vao.bind();;
    m_indexBuffer.bind();
    m_indexBuffer.allocate( m_indices.data(), m_indices.count() * sizeof( unsigned int ) );
    m_vao.release();
}

void RenderObject::setShaderProgram( QOpenGLShaderProgram* program )
{
    Q_ASSERT( program );

    m_vao.bind();
    mp_shaderProgram = program;
    mp_shaderProgram->bind();

    m_vertexBuffer.bind();
    mp_shaderProgram->enableAttributeArray( "vertex" );
    mp_shaderProgram->setAttributeBuffer( "vertex", GL_FLOAT, 0, 3, sizeof( Vertex ) );
    mp_shaderProgram->enableAttributeArray( "color" );
    mp_shaderProgram->setAttributeBuffer( "color", GL_FLOAT, 12, 4, sizeof( Vertex ) );
    mp_shaderProgram->enableAttributeArray( "textCo" );
    mp_shaderProgram->setAttributeBuffer( "textCo", GL_FLOAT, 28, 2, sizeof( Vertex ) );
    mp_shaderProgram->enableAttributeArray( "pointSize" );
    mp_shaderProgram->setAttributeBuffer( "pointSize", GL_FLOAT, 36, 1, sizeof( Vertex ) );
    m_vao.release();
}

void RenderObject::setPosition( const QVector3D& position )
{
    m_x = position.x();
    m_y = position.y();
    m_z = position.z();
    m_recalculateMatrix = true;
}

void RenderObject::setPosition( const float x, const float y, const float z )
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_recalculateMatrix = true;
}

void RenderObject::setRotation( const QVector3D& rotation )
{
    m_recalculateMatrix = true;
    m_xRotation = rotation.x();
    m_yRotation = rotation.y();
    m_zRotation = rotation.z();
}

void RenderObject::rotate( const QVector3D& rotation )
{
    m_recalculateMatrix = true;
    m_xRotation += rotation.x();
    m_yRotation += rotation.y();
    m_zRotation += rotation.z();
}

void RenderObject::setScale( const QVector3D& scale )
{
    m_recalculateMatrix = true;
    m_xScale = scale.x();
    m_yScale = scale.y();
    m_zScale = scale.z();
}

void RenderObject::setRenderMode( const GLenum renderMode )
{
    m_renderMode = renderMode;
}

void RenderObject::setTexture( QOpenGLTexture* texture )
{
    m_vao.bind();
    mp_texture = texture;
    m_vao.release();
}

void RenderObject::setTexture1(QOpenGLTexture* texture)
{
    m_vao.bind();
    mp_texture1 = texture;
    m_vao.release();
}

void RenderObject::setUseTexture( const bool useTexture )
{
    m_useTexture = useTexture;
}

void RenderObject::setUseTexutre1(const bool useTexture)
{
    m_useTexture1 = useTexture;
}

void RenderObject::setWireFrameMode(const bool wireFrameMode)
{
    m_wireFrameMode = wireFrameMode;
}

void RenderObject::setX( const float x )
{
    m_recalculateMatrix = true;
    m_x = x;
}

void RenderObject::setY( const float y )
{
    m_recalculateMatrix = true;
    m_y = y;
}

void RenderObject::setZ( const float z )
{
    m_recalculateMatrix = true;
    m_z = z;
}

void RenderObject::setRotationX (const float xRotation )
{
    m_recalculateMatrix = true;
    m_xRotation = xRotation;
}

void RenderObject::setRotationY( const float yRotation )
{
    m_recalculateMatrix = true;
    m_yRotation = yRotation;
}

void RenderObject::setRotationZ( const float zRotation )
{
    m_recalculateMatrix = true;
    m_zRotation = zRotation;
}

void RenderObject::setScaleX( const float xScale )
{
    m_recalculateMatrix = true;
    m_xScale = xScale;
}

void RenderObject::setScaleY( const float yScale )
{
    m_recalculateMatrix = true;
    m_yScale = yScale;
}

void RenderObject::setScaleZ( const float zScale )
{
    m_recalculateMatrix = true;
    m_zScale = zScale;
}

void RenderObject::setScale( const float x,
                             const float y,
                             const float z )
{
    m_recalculateMatrix = true;
    m_xScale = x;
    m_yScale = y;
    m_zScale = z;
}

void RenderObject::setVisible( const bool visible )
{
    m_visible = visible;
}

float RenderObject::getX() const
{
    return m_x;
}

float RenderObject::getY() const
{
    return m_y;
}

float RenderObject::getZ() const
{
    return m_z;
}

float RenderObject::getRotationX() const
{
    return m_xRotation;
}

float RenderObject::getRotationY() const
{
    return m_yRotation;
}

float RenderObject::getRotationZ() const
{
    return m_zRotation;
}

float RenderObject::getScaleX() const
{
    return m_xScale;
}

float RenderObject::getScaleY() const
{
    return m_yScale;
}

float RenderObject::getScaleZ() const
{
    return m_zScale;
}

bool RenderObject::isVisible() const
{
    return m_visible;
}

const Vertices& RenderObject::getVertices() const
{
    return m_vertices;
}


/**
 * @brief RenderObject::getModelMatrix
 * Constructs a column major model model matrix.
 * @return
 * Column major model matrix.
 */
const QMatrix4x4& RenderObject::getModelMatrix() const
{
    if ( m_recalculateMatrix )
    {
        m_modelMatrix.setToIdentity();
        m_modelMatrix.translate( m_x, m_y, m_z );
        m_modelMatrix.rotate( m_xRotation, 1.0f, 0.0f, 0.0f );
        m_modelMatrix.rotate( m_yRotation, 0.0f, 1.0f, 0.0f );
        m_modelMatrix.rotate( m_zRotation, 0.0f, 0.0f, 1.0f );
        m_modelMatrix.scale( m_xScale, m_yScale, m_zScale );
        m_recalculateMatrix = false;
    }
    return m_modelMatrix;
}

GLenum RenderObject::getRenderMode() const
{
    return m_renderMode;
}

bool RenderObject::getUseTexture() const
{
    return m_useTexture;
}

bool RenderObject::isWireFrameModeOn() const
{
    return m_wireFrameMode;
}

QOpenGLTexture*RenderObject::getTexture()
{
    return mp_texture;
}

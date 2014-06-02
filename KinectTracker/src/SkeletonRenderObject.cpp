#include "../inc/SkeletonRenderObject.h"
#include "../inc/SkeletonData.h"
#include <QVector>
#include <QOpenGLShaderProgram>
#include "../inc/Vertex.h"

/*!
   \brief SkeletonRenderObject::SkeletonRenderObject
   Constructs an SkeletonRenderObject with no vertex data.
   All indices will be created for a point and line representation of the skeleton.
   To set vertex data use updateData().
 */
SkeletonRenderObject::SkeletonRenderObject()
    : mp_shaderProgram( nullptr )
    , m_vertexBuffer( QOpenGLBuffer::VertexBuffer )
    , m_lineIndexBuffer( QOpenGLBuffer::IndexBuffer )
    , m_pointIndexBuffer( QOpenGLBuffer::IndexBuffer )
{
    m_vao.create();
    setPosition( QVector3D( 0, 0, 0 ) );
    setVisible( true );

    // Set the buffer's usage patter.
    m_vertexBuffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_lineIndexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_pointIndexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );

    // Prepare index buffer to draw points.
    Indices pointIndex;
    pointIndex << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
    pointIndex << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19;

    m_vao.bind();
    m_pointIndexBuffer.create();
    m_pointIndexBuffer.bind();
    m_pointIndexBuffer.allocate( pointIndex.data(), pointIndex.count() * sizeof( unsigned int ) );

    // Prepare index buffer to draw lines.
    Indices lineIndex;
    // Right leg
    lineIndex << 19 << 18; // foot - ankle
    lineIndex << 18 << 17; // ankle - knee
    lineIndex << 17 << 16; // knee - hip right
    lineIndex << 16 << 0 ; // hip right - hip
    // Left leg
    lineIndex << 15 << 14; // foot - ankle
    lineIndex << 14 << 13; // ankle - knee
    lineIndex << 13 << 12; // knee - hip left
    lineIndex << 12 <<  0; // hip left - hip
    // Right arm
    lineIndex << 11 << 10; // hand - wrist
    lineIndex << 10 << 9;  // wrist - elbow
    lineIndex << 9  << 8;  // elbow - shoulder right
    lineIndex << 8  << 2;  // shoulder right - shoulder
    // Left arm
    lineIndex << 7  << 6;  // hand - wrist
    lineIndex << 6  << 5;  // wrist - elbow
    lineIndex << 5  << 4;  // elbow - shoulder left
    lineIndex << 4  << 2;  // shoulder left - shoulder
    // Middle segments
    lineIndex << 0  << 1;  // hip - spine
    lineIndex << 1  << 2;  // spine - shoulder
    lineIndex << 2  << 3;  // shoulder - head

    m_vao.bind();
    m_lineIndexBuffer.create();
    m_lineIndexBuffer.bind();
    m_lineIndexBuffer.allocate( lineIndex.data(), lineIndex.count() * sizeof( unsigned int ) );

    m_vertexBuffer.create();

    m_vao.release();
}

/*!
   \brief SkeletonRenderObject::~SkeletonRenderObject
   Destroyes the object.
 */
SkeletonRenderObject::~SkeletonRenderObject()
{

}

/*!
   \brief SkeletonRenderObject::updateData
   Updates the vertex buffer with \a data.
 */
void SkeletonRenderObject::updateData( const SkeletonData& data )
{
    m_vao.bind();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate( data.getJoints().data(), data.getJoints().count() * sizeof( QVector3D ) );
    m_vao.release();
}

/*!
   \brief SkeletonRenderObject::setShaderProgramm
   Set the shaderprogram to \a program.
 */
void SkeletonRenderObject::setShaderProgramm( QOpenGLShaderProgram* program )
{
    m_vao.bind();
    mp_shaderProgram = program;
    mp_shaderProgram->bind();

    m_vertexBuffer.bind();
    mp_shaderProgram->enableAttributeArray( "vertex" );
    mp_shaderProgram->setAttributeBuffer( "vertex", GL_FLOAT, 0, 3, sizeof( QVector3D ) );
    m_vao.release();
}

/*!
   \brief SkeletonRenderObject::renderV
   Renders the object, if visible is set to \b true.
   \param projection
   \param view
 */
void SkeletonRenderObject::renderV( const QMatrix4x4& projection,
                                    const QMatrix4x4& view )
{
    Q_ASSERT( mp_shaderProgram );

    if ( !visible() )
    {
        return;
    }
    glPolygonMode( GL_FRONT, GL_FILL );
    glPolygonMode( GL_BACK, GL_FILL );

    m_vao.bind();
    mp_shaderProgram->bind();

    mp_shaderProgram->setUniformValue( "viewMatrix", view );
    mp_shaderProgram->setUniformValue( "projectionMatrix", projection );
    mp_shaderProgram->setUniformValue( "modelMatrix", getModelMatrix() );
    mp_shaderProgram->setUniformValue( "useTexture", false  );
    mp_shaderProgram->setUniformValue( "useSecondTexture", false );

    m_lineIndexBuffer.bind();
    glDrawElements( GL_LINES, 38, GL_UNSIGNED_INT, 0 );

    m_pointIndexBuffer.bind();
    glDrawElements( GL_POINTS, 20, GL_UNSIGNED_INT, 0 );

    m_vao.release();
}

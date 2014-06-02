#include "../inc/SkeletonRenderObject.h"
#include "../inc/SkeletonData.h"
#include <QVector>
#include <QOpenGLShaderProgram>
#include "../inc/Vertex.h"


SkeletonRenderObject::SkeletonRenderObject()
    : mp_shaderProgram( nullptr )
    , m_vertexBuffer( QOpenGLBuffer::VertexBuffer )
    , m_lineIndexBuffer( QOpenGLBuffer::IndexBuffer )
//    , m_lineIndexBuffer( QOpenGLBuffer::IndexBuffer )
    , m_verticesSet( false )
{
    m_vao.create();
    setPosition( QVector3D( 0, 0, 0 ) );
    setVisible( true );
//    m_vertexBuffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
//    m_pointIndexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
//    m_lineIndexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );



//    QVector<int> pointIndex;
//    pointIndex << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
//    pointIndex << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19;
//    qDebug() << pointIndex.count();
//    m_vao.bind();

//    m_pointIndexBuffer.create();
//	m_pointIndexBuffer.bind();
//    m_pointIndexBuffer.allocate( pointIndex.data(), pointIndex.count() * sizeof( int ) );

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

    QVector<QVector3D> vertices;
    vertices << QVector3D( -1,  2, 0 );
    vertices << QVector3D(  1,  2, 0 );
    vertices << QVector3D(  1, -2, 0 );
    vertices << QVector3D( -1, -2, 0 );

    m_vao.bind();
    m_lineIndexBuffer.create();
    m_lineIndexBuffer.bind();
    m_lineIndexBuffer.allocate( lineIndex.data(), lineIndex.count() * sizeof( unsigned int ) );
    m_vao.release();

    setVertices( vertices );

    m_vao.release();
}

SkeletonRenderObject::~SkeletonRenderObject()
{

}

void SkeletonRenderObject::updateData( const SkeletonData& data )
{
    m_vao.bind();
    if ( !m_vertexBuffer.isCreated() )
    {
        m_vertexBuffer.create();
    }
//    for ( int i = 0; i < data.getJoints().count(); ++i )
//    {
//        m_data[ i ].x = data.getJoints().at( i ).x();
//        m_data[ i ].y = data.getJoints().at( i ).y();
//        m_data[ i ].z = data.getJoints().at( i ).z();
//    }
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate( data.getJoints().data(), 20 * sizeof( QVector3D ) );
    m_vao.release();

    m_verticesSet = true;
}

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

void SkeletonRenderObject::setVertices( QVector<QVector3D> vertices )
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
    m_vertexBuffer.allocate( m_vertices.data(), m_vertices.count() * sizeof( QVector3D ) );
    m_vao.release();
}

void SkeletonRenderObject::setIndices(const Indices& indices)
{
    m_indices.clear();
    for ( int i = 0; i < indices.count(); ++i )
    {
        m_indices.append( indices.at( i ) );
    }
    if ( !m_lineIndexBuffer.isCreated() )
    {
        m_lineIndexBuffer.create();
    }

    m_vao.bind();;
    m_lineIndexBuffer.bind();
    m_lineIndexBuffer.allocate( m_indices.data(), m_indices.count() * sizeof( unsigned int ) );
    m_vao.release();
}

void SkeletonRenderObject::renderV( const QMatrix4x4& projection,
                                    const QMatrix4x4& view )
{
    Q_ASSERT( mp_shaderProgram );
//    if ( !m_verticesSet )
//    {
//        return;
//    }

    glPolygonMode( GL_FRONT, GL_FILL );
    glPolygonMode( GL_BACK, GL_FILL );

    m_vao.bind();
    mp_shaderProgram->bind();

    mp_shaderProgram->setUniformValue( "viewMatrix", view );
    mp_shaderProgram->setUniformValue( "projectionMatrix", projection );
    mp_shaderProgram->setUniformValue( "modelMatrix", getModelMatrix() );
    mp_shaderProgram->setUniformValue( "useTexture", false  );
    mp_shaderProgram->setUniformValue( "useSecondTexture", false );

    glDrawElements( GL_POINTS, 20, GL_UNSIGNED_INT, 0 );

//    m_lineIndexBuffer.bind();
//    glDrawElements( GL_LINE, 38, GL_UNSIGNED_INT, 0 );

    m_vao.release();
}

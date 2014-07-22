#include "../Inc/Floor.h"
#include "../Inc/Vertex.h"
#include <QOpenGLContext>
#include <QVector3D>

Floor::Floor( RenderObject* parent )
    : RenderObject( parent )
    , m_size( 10 )
    , m_lineCount( 9 )
{
    setObjectName( "Floor");
    calculateFloor();
    setRenderMode( GL_LINES );
}

Floor::Floor( const float a,
              const float b,
              const float c,
              const float d,
              RenderObject* parent )
    : RenderObject( parent )
    , m_size( 10 )
    , m_lineCount( 9 )
{
    setObjectName( "Floor" );
    calculateFloor( a, b, c, d );
    setRenderMode( GL_QUADS );
}

Floor::~Floor()
{
}

void Floor::setSize( const float size )
{
    m_size = size;
    calculateFloor();
}

void Floor::setLineCount( const float lineCount )
{
    m_lineCount = lineCount;
    calculateFloor();
}

float Floor::getSize() const
{
    return m_size;
}

float Floor::getLineCount() const
{
    return m_lineCount;
}

void Floor::calculateFloor()
{
    Vertices vertices;
    Indices indices;
    float offset = m_size / m_lineCount;
    int j = 0;
    const float c_d = m_size/2;
    for ( int i = 0; i < c_d; ++i )
    {
        float d = c_d - i * offset;

        // Construct vertical lines
        vertices.append( Vertex( -d, 0, -c_d ) );
        vertices.append( Vertex( -d, 0,  c_d ) );
        indices << j << j+1;

        vertices.append( Vertex( d, 0, -c_d ) );
        vertices.append( Vertex( d, 0,  c_d ) );
        indices << j+2 << j+3;

        // Construct horizontal lines
        vertices.append( Vertex( -c_d, 0, -d ) );
        vertices.append( Vertex(  c_d, 0, -d ) );
        indices << j+4 << j+5;

        vertices.append( Vertex( -c_d, 0, d ) );
        vertices.append( Vertex(  c_d, 0,  d ) );
        indices << j+6 << j+7;

        j += 8;
    }
    setVertices( vertices );
    setIndices( indices );
}

/*!
   \brief Floor::calculateFloor
 */
void Floor::calculateFloor( const float a,
                            const float b,
                            const float c,
                            const float d )
{
    QVector3D stuetzvec ( 0, 0, -d/c );
    QVector3D dirvec1 ( 1, 0,   -a/c );
    QVector3D dirvec2 ( 0, 1,   -b/c );
    dirvec1.normalize();
    dirvec2.normalize();
    Vertices vertices;
    Indices indices;

    const float factor = 200;
    QVector3D p1 = stuetzvec - factor * dirvec1 - factor * dirvec2;
    QVector3D p2 = stuetzvec - factor * dirvec1 + factor * dirvec2;
    QVector3D p3 = stuetzvec + factor * dirvec1 + factor * dirvec2;
    QVector3D p4 = stuetzvec + factor * dirvec1 - factor * dirvec2;

    vertices.append( Vertex( p1.x(), p1.y(), p1.z() ) );
    vertices.append( Vertex( p2.x(), p2.y(), p2.z() ) );
    vertices.append( Vertex( p3.x(), p3.y(), p3.z() ) );
    vertices.append( Vertex( p4.x(), p4.y(), p4.z() ) );

    indices.append( 0 );
    indices.append( 1 );
    indices.append( 2 );
    indices.append( 3 );

    setVertices( vertices );
    setIndices( indices );
}

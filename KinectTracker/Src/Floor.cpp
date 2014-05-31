#include "../Inc/Floor.h"
#include "../Inc/Vertex.h"
#include <QOpenGLContext>

Floor::Floor( OpenGLContext& context,
              RenderObject* parent )
    : RenderObject( context, parent )
    , m_size( 10 )
    , m_lineCount( 9 )
{
    setObjectName( "floor");
    calculateFloor();
    setRenderMode( GL_LINES );
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

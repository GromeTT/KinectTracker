#include "../inc/Floor.h"
#include "../inc/Vertex.h"
#include "../../AMath/inc/AMath.h"
#include <QOpenGLContext>
#include <QVector3D>

Floor::Floor( RenderObject* parent )
    : RenderObject( parent )
    , m_size( 10 )
    , m_lineCount( 9 )
    , m_normalVector( 0, 1, 0 )
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
    , m_normalVector( a, b, c )
{
    setObjectName( "Floor" );
    calculateFloor( a, b, c, d );
    setRenderMode( GL_QUADS );
}

Floor::Floor( const float x,
              const float y,
              const float z,
              RenderObject* parent )
    : RenderObject( parent )
    , m_normalVector( 1, 0, 0 )
{
    setObjectName( "Floor" );
    calculateFloor( x, y, z );
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

QVector3D Floor::normalVector() const
{
    QMatrix4x4 rot;
    rot.rotate( 90, 0.0f, 0.0f, 1.0f );
    rot.rotate( 0, 1.0f, 0.0f, 0.0f );
    rot.rotate( 0,  0.0f, 1.0f, 0.0f );
    QVector3D n = rot * m_normalVector;
    n.normalize();
    return n;
}

QVector4D Floor::planeCoefficients() const
{
    QVector3D n = normalVector();
    float d = -n.x() * x() - n.y() * y() - n.z() * z();
    return QVector4D( n.x(),
                      n.y(),
                      n.z(),
                      d );
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

void Floor::calculateFloor( const float a,
                            const float b,
                            const float c )
{
    Vertices vertices;
    int cuts = 3;
    float offset = 2.0f / float( cuts + 1 );
    for ( float i = 1; i >= -1; i = i - offset )
    {
        for ( float j = 1; j >= -1; j = j - offset )
        {
            vertices.append( Vertex( 0, i, j ) );
        }
    }
    Indices indices;
    int i = 0;
    int size = ( cuts + 2 );
    size = size*size-1;

    // Make horizontal lines.
    while ( i < size )
    {
        int res = ( i+1 ) % ( cuts+2 );
        if ( res != 0 )
        {
            indices.append( i );
            indices.append( i+1 );
        }
        ++i;
    }
    // Make vertical lines.
    i = 0;
    size = (cuts+2)*cuts + (cuts+1);
    while ( i <= size )
    {
               indices.append( i );
        indices.append( i + cuts+2 );
        ++i;
    }
    // Set vertices.
    setVertices( vertices );
    // Set indices.
    setIndices( indices );

    // Derive the rotation from the normal vector n = (x, y, z).
    float roll;
    float pitch;
    AMath::anglesFromSphericalCoordinates( roll, pitch, QVector3D( a, b, c ) );
//    setYaw( roll );
//    setPitch( pitch );
    setRoll( 90 );
}

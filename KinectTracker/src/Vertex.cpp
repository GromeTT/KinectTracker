#include "../Inc/Vertex.h"

Vertex::Vertex()
    : x ( 0.0f ), y( 0.0f ), z( 0.0f )
    , r ( 1.0f ), g( 0.0f ), b( 0.0f ), a( 1.0f )
    , u ( 0.0f ), v( 0.0f )
    , pointSize( 5.0f )
{
}

Vertex::Vertex(const float x, const float y, const float z)
    : x( x ), y( y ), z( z )
    , r( 1.0f ), g( 1.0f ), b( 1.0f ), a( 1.0f )
    , u( 0.0f ), v( 0.0f )
    , pointSize ( 5.0 )
{

}

Vertex::Vertex(const float x, const float y, const float z,
               const float r, const float g, const float b , const float a,
               const float u, const float v)
    : x( x ), y( y ), z( z )
    , r( r ), g( g ), b( b ), a( a )
    , u( u ), v( v )
    , pointSize( 5.0f )
{
}

Vertex::~Vertex()
{
}

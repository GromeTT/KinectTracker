#ifndef VERTEX_H
#define VERTEX_H

#include <QVector>

class Vertex
{
public:
    Vertex();
    Vertex( const float x, const float y, const float z );
    Vertex( const float x, const float y, const float z,
            const float r, const float g, const float b, const float a = 1.0f,
            const float u = 0, const float v = 0);
    ~Vertex();

    float x, y, z;
    float r, g, b, a;
    float u, v;
    float pointSize;
};

typedef QVector<Vertex>Vertices;
#endif // VERTEX_H

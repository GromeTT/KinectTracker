#ifndef SKELETONRENDEROBJECT_H
#define SKELETONRENDEROBJECT_H

#include "RenderObjectInterface.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "Vertex.h"

typedef QVector<unsigned int> Indices;

class SkeletonData;
class QOpenGLShaderProgram;
class Vertex;

class SkeletonRenderObject : public RenderObjectInterface
{
public:
    SkeletonRenderObject();
    ~SkeletonRenderObject();

    void updateData( const SkeletonData& data );
    void setShaderProgramm( QOpenGLShaderProgram* program );
    void setVertices( QVector<QVector3D> vertices );
    void setIndices(const Indices& indices);

private:
    virtual void renderV( const QMatrix4x4 &projection,
                          const QMatrix4x4 &view );

    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram*    mp_shaderProgram;
    QOpenGLBuffer            m_vertexBuffer;
    QOpenGLBuffer            m_lineIndexBuffer;
    bool                     m_verticesSet;
    QVector<QVector3D> m_vertices;
    Indices  m_indices;
};

#endif // SKELETONRENDEROBJECT_H

#ifndef SKELETONRENDEROBJECT_H
#define SKELETONRENDEROBJECT_H

#include "RenderObjectInterface.h"
#include "SkeletonData.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

typedef QVector<unsigned int> Indices;

class QOpenGLShaderProgram;
class Vertex;

class SkeletonRenderObject : public RenderObjectInterface
{
public:
    SkeletonRenderObject();
    ~SkeletonRenderObject();

    void updateData( const SkeletonDataPtr& data );
    void setShaderProgramm( QOpenGLShaderProgram* program );

private:
    virtual void renderV( const QMatrix4x4 &projection,
                          const QMatrix4x4 &view );

    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram*    mp_shaderProgram;
    QOpenGLBuffer            m_vertexBuffer;
    QOpenGLBuffer            m_lineIndexBuffer;
    QOpenGLBuffer            m_pointIndexBuffer;
};

#endif // SKELETONRENDEROBJECT_H

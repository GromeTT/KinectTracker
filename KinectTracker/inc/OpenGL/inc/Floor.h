#ifndef FLOOR_H
#define FLOOR_H

#include "../Inc/RenderObject.h"

class Floor : public RenderObject
{
    Q_OBJECT

public:
    Floor( RenderObject* parent = nullptr );
    Floor( const float a,
           const float b,
           const float c,
           const float d,
           RenderObject* parent = nullptr );
    Floor( const float x,
           const float y,
           const float z,
           RenderObject* parent = nullptr );
    virtual ~Floor();

    void setSize( const float size );
    void setLineCount( const float lineCount );
    void calculateFloor();
    void calculateFloor( const float a,
                         const float b,
                         const float c,
                         const float d );
    void calculateFloor( const float a,
                         const float b,
                         const float c );
    float getSize() const ;
    float getLineCount() const;
    float m_size;
    QVector3D normalVector() const;
    QVector4D planeCoefficients() const;

private:
    float     m_lineCount;
    mutable QVector3D m_normalVector;

signals:
    void sizeChanged();
    void lineCountChanged();
};

#endif // FLOOR_H

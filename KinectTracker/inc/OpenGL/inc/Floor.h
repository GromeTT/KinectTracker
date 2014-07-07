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
    virtual ~Floor();

    void setSize( const float size );
    void setLineCount( const float lineCount );
    void calculateFloor();
    void calculateFloor( const float a,
                         const float b,
                         const float c,
                         const float d );
    float getSize() const ;
    float getLineCount() const;
    float m_size;

private:
    float m_lineCount;

signals:
    void sizeChanged();
    void lineCountChanged();

private:
//    Q_PROPERTY( float size MEMBER m_size
//                READ getSize
//                WRITE setSize
//                NOTIFY sizeChanged )

//    Q_PROPERTY( float lineCount MEMBER m_lineCount
//                READ getLineCount
//                WRITE setLineCount
//                NOTIFY lineCountChanged )
};

#endif // FLOOR_H

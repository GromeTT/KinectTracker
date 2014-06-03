#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QVector>
#include <QSharedPointer>
#include "Vertex.h"
#include "../inc/SkeletonData.h"

class QMatrix4x4;

typedef QVector<Vertex> Vertices;

struct BoundingBox
{
public:
    BoundingBox();
    BoundingBox( const QVector<QVector3D>& points,
                 const float deltaW = 0,
                 const float deltaD = 0,
                 const float deltaH = 0 );
    BoundingBox( const BoundingBox& other );
    ~BoundingBox();

    float getDepth() const;
    float getWidth() const;
    float getHeight() const;
    float getX() const;
    float getY() const;
    float getZ() const;

    void setDepth( const float depth );
    void setWidth( const float width );
    void setHeight( const float height );
    void setX( const float x );
    void setY( const float y );
    void setZ( const float z );

    bool isPointInBoundingBox( const QVector3D& point );
    bool arePointsInBoundingBox( const QVector<QVector3D> points, const int count );

private:
    float m_width;
    float m_height;
    float m_depth;
    float m_x;
    float m_y;
    float m_z;
};

typedef QSharedPointer<BoundingBox> BoundingBoxPtr;
#endif // BOUNDINGBOX_H

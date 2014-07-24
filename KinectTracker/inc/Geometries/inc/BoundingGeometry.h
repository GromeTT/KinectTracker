#ifndef BOUNDINGGEOMETRY_H
#define BOUNDINGGEOMETRY_H

#include <QVector>
#include <QSharedPointer>
#include "../../OpenGL/inc/Vertex.h"
#include "../../Kinect/inc/SkeletonData.h"

class QMatrix4x4;

typedef QVector<Vertex> Vertices;

class BoundingGeometry
{
public:
    BoundingGeometry();
    BoundingGeometry( const float x,
                      const float y,
                      const float z );
    BoundingGeometry( const QVector3D& position );
    virtual ~BoundingGeometry();

    float     x() const;
    float     y() const;
    float     z() const;
    QVector3D position() const;
    bool      arePointsInsideGeometry( const QVector<QVector3D>& points );

    void setX( const float x );
    void setY( const float y );
    void setZ( const float z );
    void setPosition( const QVector3D& position );

private:
    virtual bool arePointsInsideGeometryV( const QVector<QVector3D>& points ) = 0;

protected:
    QVector3D m_position;
};


typedef QSharedPointer<BoundingGeometry> BoundingGeometryPtr;

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class BoundingBox : public BoundingGeometry
{
public:
    BoundingBox();
    BoundingBox( const QVector<QVector3D>& points,
                 const float deltaW = 0,
                 const float deltaD = 0,
                 const float deltaH = 0 );
    BoundingBox( const BoundingBox& other );
    virtual ~BoundingBox();

    float depth() const;
    float width() const;
    float height() const;
    QVector3D frontFaceTopLeftCorner();
    QVector3D frontFaceBottomRightCorner();

    void setDepth( const float depth );
    void setWidth( const float width );
    void setHeight( const float height );
    void calculateBoundingBox( const QVector<QVector3D>& points,
                               const float deltaW = 0,
                               const float deltaD = 0,
                               const float deltaH = 0);
private:
    bool arePointsInsideGeometryV( const QVector<QVector3D>& points );


    float m_width;
    float m_height;
    float m_depth;
};

typedef QSharedPointer<BoundingBox> BoundingBoxPtr;

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class BoundingGeometryWithTimeStamp
{
public:
    // TODO: Rework.
    BoundingGeometryWithTimeStamp( );
    BoundingGeometryWithTimeStamp( BoundingGeometry* geometry,
                                   unsigned int timestamp );
    BoundingGeometryWithTimeStamp( BoundingGeometryPtr& geometry,
                                   unsigned int timestamp );
    BoundingGeometryPtr   m_geometry;
    unsigned int          m_timestamp;
};

typedef QSharedPointer<BoundingGeometryWithTimeStamp> BoundingGeometryWithTimeStampPtr;

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class BoundingSphere : public BoundingGeometry
{
public:
    BoundingSphere( const QVector<QVector3D>& points,
                    const float delta );
    BoundingSphere( const float x,
                    const float y,
                    const float z,
                    const float radius );
    BoundingSphere( const QVector3D& position,
                    const float radius );
    virtual ~BoundingSphere();

    void  setRadius( const float radius );
    float radius()       const;

private:
    virtual bool arePointsInsideGeometryV( const QVector<QVector3D>& points );

    float m_radius;
};

#endif // BOUNDINGGEOMETRY_H

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
    virtual ~BoundingGeometry();

    float x() const;
    float y() const;
    float z() const;

    void setX( const float x );
    void setY( const float y );
    void setZ( const float z );

    bool arePointsInsideGeometry( const QVector<QVector3D>& points );
    QVector3D frontFaceTopLeftCorner();
    QVector3D frontFaceBottomRightCorner();

private:
    virtual bool arePointsInsideGeometryV( const QVector<QVector3D>& points ) = 0;

protected:
    float m_x;
    float m_y;
    float m_z;
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
                    const float r );
    virtual ~BoundingSphere();

private:
    virtual bool arePointsInsideGeometryV( const QVector<QVector3D>& points );

    float m_x;
    float m_y;
    float m_z;

    float m_r;
};

#endif // BOUNDINGGEOMETRY_H

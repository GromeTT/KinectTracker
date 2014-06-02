#ifndef SKELETONANALYZER_H
#define SKELETONANALYZER_H

#include <QObject>
#include <QVector>
#include <QPair>
#include "BoundingBox.h"

class QVector3D;
class SkeletonData;
class BoundingBoxWithTimeStamp;

class SkeletonAnalyzer : public QObject
{
    Q_OBJECT

public:
    SkeletonAnalyzer();
    ~SkeletonAnalyzer();

    void update( const SkeletonData* skeleton,
                 const unsigned int timestamp );
    void setDeltaX( const float deltaX );
    void setDeltaY( const float deltaY );
    void setDeltaZ( const float deltaZ );

    float               deltaX() const;
    float               deltaY() const;
    float               deltaZ() const;
    bool                arePointsInLastBoundingBox( const SkeletonData& skeletonData );
    QVector3D           getVelocity( const unsigned int timestamp,
                                     const unsigned int ms );
    const BoundingBox*  getLastBoundingBox() const;

private:
    void addBoundingBox( BoundingBoxPtr& boundingBox,
                         const unsigned int timestamp );


    float m_deltaX;
    float m_deltaY;
    float m_deltaZ;

signals:
    void deltaXChanged();
    void deltaYChanged();
    void deltaZChanged();

private:
    // Nested class
    class BoundingBoxWidthTimeStamp
    {
    public:
        BoundingBoxWidthTimeStamp( BoundingBoxPtr& boudingBox,
                                   unsigned int timestamp );
        BoundingBoxPtr mp_box;
        unsigned int m_timestamp;
    };
    QVector<BoundingBoxWidthTimeStamp*> m_boxes;

    // PROPERTIES
private:
    Q_PROPERTY( float deltaX MEMBER m_deltaX
                READ deltaX
                WRITE setDeltaX
                NOTIFY deltaXChanged )

    Q_PROPERTY( float deltaY MEMBER m_deltaY
                READ deltaY
                WRITE setDeltaY
                NOTIFY deltaYChanged )

    Q_PROPERTY( float deltaZ MEMBER m_deltaZ
                READ deltaZ
                WRITE setDeltaZ
                NOTIFY deltaZChanged )
};

#endif // SKELETONANALYZER_H

#ifndef SKELETONANALYZER_H
#define SKELETONANALYZER_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QRect>
#include "BoundingBox.h"

class QVector3D;
class SkeletonData;

class SkeletonAnalyzer : public QObject
{
    Q_OBJECT

public:
    SkeletonAnalyzer();
    ~SkeletonAnalyzer();

    void update( const SkeletonDataPtr& skeleton,
                 const unsigned int timestamp );

    void setDeltaX( const float deltaX );
    void setDeltaY( const float deltaY );
    void setDeltaZ( const float deltaZ );
    void setPhi1( const float phi1 );
    void setPhi2( const float phi2 );
    void setKneelingThreshold( const float threshold );
    void setLyingThreshold( const float threshold );

    float               estimatedHeight() const;
    float               currentHeight() const;
    float               deltaX() const;
    float               deltaY() const;
    float               deltaZ() const;
    float               phi1() const;
    float               phi2() const;
    float               kneelingThreshold() const;
    float               lyingThreshold() const;
    QString             workerStatus() const;
    bool                arePointsInLastBoundingBox( const SkeletonDataPtr& skeletonData );
    QVector3D           getVelocity( const unsigned int timestamp,
                                     const unsigned int ms );
    const BoundingBox*    getLastBoundingBox() const;
    const BoundingBox*    getBoundingBoxWholeBody() const;
    const SkeletonDataPtr lastSkeletonData() const;
    const QVector<QVector3D>& regionOfInterest() const;

private:
    void calculateFeatureVector( const SkeletonDataPtr& skeletonData );
    void addBoundingBox( BoundingBoxPtr& boundingBox,
                         const unsigned int timestamp );
    bool calculateHeight( const SkeletonDataPtr skeletonData, float& height );

    float     m_estimatedHeight;
    float     m_currentHeight;
    float     m_deltaX;
    float     m_deltaY;
    float     m_deltaZ;
    float     m_phi1;
    float     m_phi2;
    float     m_kneelingThreshold;
    float     m_lyingThreshold;
    QString   m_workerStatus;
    QVector<QVector3D> m_regionOfInteres;

signals:
    void estimatedHeightChanged();
    void currentHeightChanged();
    void deltaXChanged();
    void deltaYChanged();
    void deltaZChanged();
    void phi1Changed();
    void phi2Changed();
    void kneelingThresholdChanged();
    void lyingThresholdChanged();
    void workerStatusChanged();

private:
    QVector<BoundingBoxWithTimeStamp*> m_boxes;
    BoundingBox                        m_boundingBox;
    SkeletonDataPtr                    m_skeletonData;

private:
    Q_PROPERTY( float estimatedHeight MEMBER m_estimatedHeight
                READ estimatedHeight
                NOTIFY estimatedHeightChanged )

    Q_PROPERTY( float currentHeight MEMBER m_currentHeight
                READ currentHeight
                NOTIFY currentHeightChanged )

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

    Q_PROPERTY( float phi1 MEMBER m_phi1
                READ phi1
                WRITE setPhi1
                NOTIFY phi1Changed )

    Q_PROPERTY( float phi2 MEMBER m_phi2
                READ phi2
                WRITE setPhi2
                NOTIFY phi1Changed )

    Q_PROPERTY( float kneelingThreshold MEMBER m_kneelingThreshold
                READ kneelingThreshold
                WRITE setKneelingThreshold
                NOTIFY kneelingThresholdChanged )

    Q_PROPERTY( float lyingThreshold MEMBER m_lyingThreshold
                READ lyingThreshold()
                WRITE setLyingThreshold
                NOTIFY lyingThresholdChanged )

    Q_PROPERTY ( QString workerStatus MEMBER m_workerStatus
                 READ workerStatus
                 NOTIFY workerStatusChanged )
};

#endif // SKELETONANALYZER_H

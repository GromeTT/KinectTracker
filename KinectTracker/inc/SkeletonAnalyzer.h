#ifndef SKELETONANALYZER_H
#define SKELETONANALYZER_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QRect>
#include <QSharedPointer>
#include "BoundingGeometry.h"
#include "MovementAnalyzer.h"
#include "AMath.h"

class QVector3D;
class SkeletonData;

class SkeletonAnalyzer : public QObject
{
    Q_OBJECT

public:
    SkeletonAnalyzer( QObject* parent = nullptr );
    virtual ~SkeletonAnalyzer();

    bool update( const SkeletonDataPtr skeleton,
                 const unsigned int timestamp );

    void setPhi1( const float phi1 );
    void setPhi2( const float phi2 );

    float                     estimatedHeight() const;
    float                     currentHeight() const;
    float                     phi1() const;
    float                     phi2() const;
    float                     kneelingThreshold() const;
    float                     lyingThreshold() const;
    QString                   workerStatus() const;
    const BoundingBox*        getBoundingBoxWholeBody() const;
    AMath::Rectangle3D        regionOfInterest() const;
    SkeletonDataPtr           skeleton() const;

private:
    void calculateFeatureVector( const SkeletonDataPtr& skeletonData );
    bool calculateHeight( const SkeletonDataPtr skeletonData, float& height );

    float               m_estimatedHeight;
    float               m_currentHeight;
    float               m_phi1;
    float               m_phi2;
    QString             m_workerStatus;
    AMath::Rectangle3D  m_regionOfInterest;
    SkeletonDataPtr     m_skeletonData;

signals:
    void estimatedHeightChanged();
    void currentHeightChanged();
    void phi1Changed();
    void phi2Changed();

private:
    BoundingBox m_boundingBox;

private:
    Q_PROPERTY( float estimatedHeight
                READ estimatedHeight
                NOTIFY estimatedHeightChanged )

    Q_PROPERTY( float currentHeight
                READ currentHeight
                NOTIFY currentHeightChanged )

    Q_PROPERTY( float phi1
                READ phi1
                WRITE setPhi1
                NOTIFY phi1Changed )

    Q_PROPERTY( float phi2
                READ phi2
                WRITE setPhi2
                NOTIFY phi1Changed )
};

typedef QSharedPointer<SkeletonAnalyzer> SkeletonAnalyzerPtr;

#endif // SKELETONANALYZER_H

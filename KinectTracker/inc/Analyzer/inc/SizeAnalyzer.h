#ifndef SIZEANALYZER_H
#define SIZEANALYZER_H

#include "../../Kinect/inc/SkeletonData.h"
#include "../../Kinect/inc/Kinect.h"
#include <QObject>
#include <QSharedPointer>
#include <QVector4D>

class SizeAnalyzer : public QObject
{
    Q_OBJECT

public:
    SizeAnalyzer( QObject* parent = nullptr );
    virtual ~SizeAnalyzer();

    void analyze( const KinectPtr kinect,
                  const SkeletonDataPtr& skeletonData );
    void setKneelingThreshold( const float threshold );
    void setLyingThreshold( const float threshold );
    void setWorkerStatus( const QString& status );
    void reset();

    float     estimatedBodySize() const;
    float     currentBodySize() const;
    float     kneelingThreshold() const;
    float     lyingThreshold() const;
    float     distanceHeadRightFood() const;
    float     distanceHeadLeftFood() const;
    float     distanceFloorHead() const;
    QString   workerStatus() const;
    bool      floorInitialized() const;
    QVector4D planeCoefficients() const;

protected:
    float   m_kneelingThreshold;
    float   m_lyingThreshold;
    float   m_estimatedBodySize;
    float   m_currentBodySize;
    float   m_distanceHeadRightFood;
    float   m_distanceHeadLeftFood;
    float   m_distanceFloorHead;
    QString m_workerStatus;

private:
    virtual void analyzeV( const SkeletonDataPtr& skeletonData ) = 0;
    virtual void resetV() = 0;

    QVector4D m_planeCoefficients;
    bool      m_floorInitialized;

signals:
    void estimatedBodySizeChanged();
    void currentBodySizeChanged();
    void workerStatusChanged();
    void kneelingThresholdChanged();
    void lyingThresholdChanged();
    void distanceHeadRightFoodChanged();
    void distanceHeadLeftFoodChanged();
    void distanceFloorHeadChanged();

private:
    Q_PROPERTY( float estimatedBodySize
                READ estimatedBodySize
                NOTIFY estimatedBodySizeChanged )

    Q_PROPERTY( float currentBodySize
                READ currentBodySize
                NOTIFY currentBodySizeChanged )

    Q_PROPERTY( QString workerStatus
                READ workerStatus
                NOTIFY workerStatusChanged )

    Q_PROPERTY( float kneelingThreshold MEMBER m_kneelingThreshold
                READ kneelingThreshold
                WRITE setKneelingThreshold
                NOTIFY kneelingThresholdChanged )

    Q_PROPERTY( float lyingThreshold MEMBER m_lyingThreshold
                READ lyingThreshold()
                WRITE setLyingThreshold
                NOTIFY lyingThresholdChanged )

    Q_PROPERTY( float distanceHeadRightFood
                READ distanceHeadRightFood
                NOTIFY distanceHeadRightFoodChanged )

    Q_PROPERTY( float distanceHeadLeftFood
                READ distanceHeadLeftFood
                NOTIFY distanceHeadLeftFoodChanged )

    Q_PROPERTY( float distanceFloorHead
                READ distanceFloorHead
                NOTIFY distanceFloorHeadChanged )
};

typedef QSharedPointer<SizeAnalyzer> SizeAnalyzerPtr;

#endif // SIZEANALYZER_H

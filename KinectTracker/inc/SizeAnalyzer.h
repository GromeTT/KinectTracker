#ifndef SIZEANALYZER_H
#define SIZEANALYZER_H

#include <QObject>
#include <QSharedPointer>
#include "SkeletonData.h"

class SizeAnalyzer : public QObject
{
    Q_OBJECT

public:
    SizeAnalyzer( QObject* parent = nullptr );
    virtual ~SizeAnalyzer();

    void analyze( const SkeletonDataPtr& skeletonData );
    void setKneelingThreshold( const float threshold );
    void setLyingThreshold( const float threshold );
    void setWorkerStatus( const QString& status );

    float   estimatedBodySize();
    float   currentBodySize();
    float   kneelingThreshold();
    float   lyingThreshold();
    QString workerStatus();

protected:
    float   m_kneelingThreshold;
    float   m_lyingThreshold;
    float   m_estimatedBodySize;
    float   m_currentBodySize;
    QString m_workerStatus;

private:
    virtual void analyzeV( const SkeletonDataPtr& skeletonData ) = 0;

signals:
    void estimatedBodySizeChanged();
    void currentBodySizeChanged();
    void workerStatusChanged();
    void kneelingThresholdChanged();
    void lyingThresholdChanged();

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
};

typedef QSharedPointer<SizeAnalyzer> SizeAnalyzerPtr;

#endif // SIZEANALYZER_H

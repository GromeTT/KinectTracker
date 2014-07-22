#ifndef SPHEREMOVEMENTANALYZER_H
#define SPHEREMOVEMENTANALYZER_H

#include "MovementAnalyzer.h"

class SphereMovementAnalyzer : public MovementAnalyzer
{
    Q_OBJECT

public:
    SphereMovementAnalyzer( QObject* parent = nullptr );
    virtual ~SphereMovementAnalyzer();

    void  setRadius( const float radius );
    float radius() const;

signals:
    void radiusChanged();

private:
    virtual void analyzerV( const SkeletonDataPtr skeleton,
                            const unsigned int timestamp );
    virtual void resetV();

    float m_radius;
    float m_radiusDelta;

private:
    Q_PROPERTY( float radius MEMBER m_radius
                READ radius
                WRITE setRadius
                NOTIFY radiusChanged )
};

typedef QSharedPointer<SphereMovementAnalyzer> SphereMovementAnalyzerPtr;

#endif // SPHEREMOVEMENTANALYZER_H

#ifndef SPHEREMOVEMENTANALYZER_H
#define SPHEREMOVEMENTANALYZER_H

#include "MovementAnalyzer.h"
#include <QVector3D>

class SphereMovementAnalyzer : public MovementAnalyzer
{
    Q_OBJECT

public:
    SphereMovementAnalyzer( QObject* parent = nullptr );
    virtual ~SphereMovementAnalyzer();

    void       setRadius( const float radius );
    float      radius() const;
    QVector3D  position() const;

signals:
    void radiusChanged();

private:
    virtual void analyzeV( const SkeletonDataPtr skeleton,
                           const unsigned int timestamp );
    virtual void resetV();

    float       m_radius;
    QVector3D   m_position;

private:
    Q_PROPERTY( float radius MEMBER m_radius
                READ radius
                WRITE setRadius
                NOTIFY radiusChanged )
};

typedef QSharedPointer<SphereMovementAnalyzer> SphereMovementAnalyzerPtr;

#endif // SPHEREMOVEMENTANALYZER_H

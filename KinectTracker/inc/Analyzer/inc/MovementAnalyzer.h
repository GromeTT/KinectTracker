#ifndef MOVEMENTANALYSER_H
#define MOVEMENTANALYSER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include "../../Geometries/inc/BoundingGeometry.h"

class MovementAnalyzer : public QObject
{
    Q_OBJECT

public:
    MovementAnalyzer( QObject* parent = nullptr );
    virtual ~MovementAnalyzer();

    void analyze( const SkeletonDataPtr& skeleton,
                  const unsigned int timestamp );
    void setRoll( const float roll );
    void setPitch( const float pitch );
    void setYaw( const float yaw );
    void setVelocityInterval( const int intervall );
    void setDataAvailable( const bool available );
    void setViewingDirection( const QString& direction );
    void reset();

    BoundingGeometryPtr                              getLatestBoudingGeomerty() const;
    const QVector<BoundingGeometryWithTimeStampPtr>& boundingGeometries() const;
    const float                                      roll() const;
    const float                                      pitch() const;
    const float                                      yaw() const;
    const int                                        velocityInterval() const;
    const float                                      velocity() const;
    const bool                                       dataAvailable() const;
    QString                                          viewingDirection() const;

private:
    virtual void anaylzeV( const SkeletonDataPtr skeleton,
                           const unsigned int timestamp ) = 0;
    virtual void resetV() = 0;
    void calculateOriantationAndVelocity( const int timestamp );
    void setVelocity( const float velocity );

    mutable float   m_roll;
    mutable float   m_pitch;
    mutable float   m_yaw;
    mutable float   m_velocity;
    unsigned int    m_velocityInterval;
    bool            m_dataAvaibale;
    QString         m_viewingDirection;

signals:
    void rollChanged();
    void pitchChanged();
    void yawChanged();
    void velocityIntervalChanged();
    void veloctiyChanged();
    void viewingDirectionChanged();

protected:
    bool arePointsInsideLatestBoudingGeomerty( const QVector<QVector3D>& points ) const;
    void addBoundingGeometry( BoundingGeometryPtr& boundingGeometry,
                              const unsigned int timestamp );


    QVector<BoundingGeometryWithTimeStampPtr> m_boudingGeometries;
    static const int                          m_maxBoudingGeometryCount = 200;

private:
    Q_PROPERTY( float roll
                READ roll
                NOTIFY rollChanged)

    Q_PROPERTY( float pitch
                READ pitch
                NOTIFY pitchChanged )

    Q_PROPERTY( float yaw
                READ yaw
                NOTIFY yawChanged )

    Q_PROPERTY( int velocityIntervall MEMBER m_velocityInterval
                READ velocityInterval
                WRITE setVelocityInterval
                NOTIFY velocityIntervalChanged )

    Q_PROPERTY( float velocity
                READ velocity
                NOTIFY veloctiyChanged )

    Q_PROPERTY( QString viewingDirection
                READ viewingDirection
                NOTIFY viewingDirectionChanged )
};

typedef QSharedPointer<MovementAnalyzer> MovementAnalyzerPtr;

#endif // MOVEMENTANALYSER_H

#ifndef ANALYSISRESULTS_H
#define ANALYSISRESULTS_H

#include <QObject>
#include <QVector3D>

class AnalysisResults : public QObject
{
    Q_OBJECT

public:
    AnalysisResults();
    ~AnalysisResults();

    void setWorkerStatus( const QString& status );
    void setRoll( const float angle );
    void setPitch( const float angle );
    void setYaw( const float angle );
    void setVelocity( const float velocity );
    void setValuesByVetcor( const QVector3D& vec );

    const QString workerStatus() const;
    const float   roll() const;
    const float   pitch() const;
    const float   yaw() const;
    const float   velocity() const;

signals:
    void workerStatusChanged();
    void rollChanged();
    void pitchChanged();
    void yawChanged();
    void velocityChanged();
    void vecChanged();

private:
    float   radToDeg( const float rad );
    QString m_workerStatus;
    float   m_roll;
    float   m_pitch;
    float   m_yaw;
    float   m_velocity;

private:
    Q_PROPERTY( QString workerStatus
                READ workerStatus
                NOTIFY workerStatusChanged )

    Q_PROPERTY( float roll
                READ roll
                NOTIFY rollChanged)

    Q_PROPERTY( float pitch
                READ pitch
                NOTIFY pitchChanged )

    Q_PROPERTY( float yaw
                READ yaw
                NOTIFY yawChanged )

    Q_PROPERTY( float velocity
                READ velocity
                NOTIFY velocityChanged )
};


#endif // ANALYSISRESULTS_H

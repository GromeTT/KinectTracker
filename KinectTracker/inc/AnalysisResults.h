#ifndef ANALYSISRESULTS_H
#define ANALYSISRESULTS_H

#include <QObject>

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

    QString workerStatus() const;
    float   roll() const;
    float   pitch() const;
    float   yaw() const;
    float   velocity() const;

signals:
    void workerStatusChanged();
    void rollChanged();
    void pitchChanged();
    void yawChanged();
    void velocityChanged();

private:
    float radToDeg( const float rad );
    QString m_workerStatus;
    float   m_roll;
    float   m_pitch;
    float   m_yaw;
    float   m_velocity;

    Q_PROPERTY( QString workerStatus MEMBER m_workerStatus
                READ workerStatus
                WRITE setWorkerStatus
                NOTIFY workerStatusChanged )

    Q_PROPERTY( float roll MEMBER m_roll
                READ roll
                WRITE setRoll
                NOTIFY rollChanged)

    Q_PROPERTY( float pitch MEMBER m_pitch
                READ pitch
                WRITE setPitch
                NOTIFY pitchChanged )

    Q_PROPERTY( float yaw MEMBER m_yaw
                READ yaw
                WRITE setYaw
                NOTIFY yawChanged )

    Q_PROPERTY( float velocity MEMBER m_velocity
                READ velocity
                WRITE setVelocity
                NOTIFY velocityChanged )
};


#endif // ANALYSISRESULTS_H

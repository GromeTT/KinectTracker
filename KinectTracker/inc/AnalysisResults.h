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
    void setDirectionX( const float directionX );
    void setDirectionY( const float directionY );
    void setDirectionZ( const float directionZ );
    void setVelocity( const float velocity );
    void setValuesByVetcor( const QVector3D& vec );

    QString workerStatus() const;
    float   directionX() const;
    float   directionY() const;
    float   directionZ() const;
    float   velocity() const;

signals:
    void workerStatusChanged();
    void directionXChanged();
    void directionYChanged();
    void directionZChanged();
    void velocityChanged();

private:
    float radToDeg( const float rad );
    QString m_workerStatus;
    float   m_directionX;
    float   m_directionY;
    float   m_directionZ;
    float   m_velocity;

    Q_PROPERTY( QString workerStatus MEMBER m_workerStatus
                READ workerStatus
                WRITE setWorkerStatus
                NOTIFY workerStatusChanged )
    Q_PROPERTY( float directionX MEMBER m_directionX
                READ directionX
                WRITE setDirectionX
                NOTIFY directionXChanged )
    Q_PROPERTY( float directionY MEMBER m_directionY
                READ directionY
                WRITE setDirectionY
                NOTIFY directionYChanged )
    Q_PROPERTY( float directionZ MEMBER m_directionZ
                READ directionZ
                WRITE setDirectionZ
                NOTIFY directionZChanged )
    Q_PROPERTY( float velocity MEMBER m_velocity
                READ velocity
                WRITE setVelocity
                NOTIFY velocityChanged )
};


#endif // ANALYSISRESULTS_H

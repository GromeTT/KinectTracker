#include "../inc/AnalysisResults.h"
#include "../inc/Defines.h"
#include <QVector3D>
#include <QDebug>

AnalysisResults::AnalysisResults()
    : m_roll( 0 )
    , m_yaw( 0 )
    , m_pitch( 0 )
    , m_velocity( 0 )
{
    setObjectName( "AnalysisResults" );
}

AnalysisResults::~AnalysisResults()
{

}

void AnalysisResults::setWorkerStatus( const QString& status )
{
    if ( m_workerStatus != status )
    {
        m_workerStatus = status;
        emit workerStatusChanged();
    }
}

void AnalysisResults::setRoll( const float angle )
{
    if ( m_roll != angle )
    {
        m_roll = angle;
        emit rollChanged();
    }
}

void AnalysisResults::setYaw( const float angle )
{
    if ( m_yaw != angle )
    {
        m_yaw = angle;
        emit yawChanged();
    }
}

void AnalysisResults::setPitch( const float angle )
{
    if ( m_pitch != angle )
    {
        m_pitch = angle;
        emit pitchChanged();
    }
}

void AnalysisResults::setVelocity( const float velocity )
{
    if ( m_velocity != velocity )
    {
        m_velocity = velocity;
        emit velocityChanged();
    }
}

void AnalysisResults::setValuesByVetcor( const QVector3D& vec )
{
    setVelocity( vec.length() );
    // http://de.wikipedia.org/wiki/Polarkoordinaten
    setYaw( radToDeg( atan2( vec.z(), vec.x() ) ) );
}

QString AnalysisResults::workerStatus() const
{
    return m_workerStatus;
}

float AnalysisResults::roll() const
{
    return m_roll;
}

float AnalysisResults::yaw() const
{
    return m_yaw;
}

float AnalysisResults::pitch() const
{
    return m_pitch;
}

float AnalysisResults::velocity() const
{
    return m_velocity;
}

float AnalysisResults::radToDeg(const float rad)
{
    return rad * factorRadianToDegree;
}


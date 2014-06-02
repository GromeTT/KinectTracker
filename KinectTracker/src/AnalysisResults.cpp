#include "../inc/AnalysisResults.h"
#include <QVector3D>
#include <QDebug>

#define PI 3.14159265359

AnalysisResults::AnalysisResults()
    : m_directionX( 0 )
    , m_directionY( 0 )
    , m_directionZ( 0 )
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

void AnalysisResults::setDirectionX( const float directionX )
{
    if ( m_directionX != directionX )
    {
        m_directionX = directionX;
        emit directionXChanged();
    }
}

void AnalysisResults::setDirectionY( const float directionY )
{
    if ( m_directionY != directionY )
    {
        m_directionY = directionY;
        emit directionYChanged();
    }
}

void AnalysisResults::setDirectionZ( const float directionZ )
{
    if ( m_directionZ != directionZ)
    {
        m_directionZ = directionZ;
        emit directionZChanged();
    }
}

void AnalysisResults::setVelocity(const float velocity)
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
    setDirectionY( radToDeg( atan2( vec.x(), vec.z() ) ) );
//    qDebug () << m_directionZ;
}

QString AnalysisResults::workerStatus() const
{
    return m_workerStatus;
}

float AnalysisResults::directionX() const
{
    return m_directionX;
}

float AnalysisResults::directionY() const
{
    return m_directionY;
}

float AnalysisResults::directionZ() const
{
    return m_directionZ;
}

float AnalysisResults::velocity() const
{
    return m_velocity;
}

float AnalysisResults::radToDeg(const float rad)
{
    return rad * 180 / PI;
}


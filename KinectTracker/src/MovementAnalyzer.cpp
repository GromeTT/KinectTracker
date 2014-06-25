#include "../inc/MovementAnalyzer.h"
#include "../inc/AMath.h"

/*!
   \brief MovementAnalyzer::MovementAnalyzer
   Standardconstructor.
 */
MovementAnalyzer::MovementAnalyzer( QObject* parent )
    : QObject( parent )
    , m_boudingGeometries( m_maxBoudingGeometryCount )
    , m_roll( 0 )
    , m_pitch( 0 )
    , m_yaw( 0 )
    , m_velocity( 0 )
    , m_velocityInterval( 10 )
{
}

/*!
   \brief MovementAnalyzer::~MovementAnalyzer
   Destroyes the object.
 */
MovementAnalyzer::~MovementAnalyzer()
{
}

/*!
   \brief MovementAnalyzer::analyze
   Analyzes the human's movement.
 */
void MovementAnalyzer::analyze( const SkeletonDataPtr& skeleton,
                                const unsigned int timestamp )
{
    anaylzeV( skeleton, timestamp );
    calculateOriantationAndVelocity( timestamp );
    m_dataAvaibale = true;
}

/*!
   \brief MovementAnalyzer::setRoll
   Sets the roll angle to \a roll.
 */
void MovementAnalyzer::setRoll( const float roll )
{
    m_roll = roll;
    emit rollChanged();
}

/*!
   \brief MovementAnalyzer::setPitch
   Sets the pitch angle to \a pitch.
 */
void MovementAnalyzer::setPitch( const float pitch )
{
    m_pitch = pitch;
    emit pitchChanged();
}

/*!
   \brief MovementAnalyzer::setYaw
   Sets the yaw angle to \a yaw.
 */
void MovementAnalyzer::setYaw(const float yaw)
{
    m_yaw = yaw;
    emit yawChanged();
}

/*!
   \brief MovementAnalyzer::setVelocityIntervall
   Sets the intervall over which the velocity will be calculated.
 */
void MovementAnalyzer::setVelocityInterval(const int interval )
{
    m_velocityInterval = interval;
    emit velocityIntervalChanged();
}

/*!
   \brief MovementAnalyzer::setDataAvailable
 */
void MovementAnalyzer::setDataAvailable( const bool available )
{
    m_dataAvaibale = available;
}

/*!
   \brief MovementAnalyzer::getLatestBoudingGeomerty
   Returns the latest inserted BoundingGeometryPtr.
 */
BoundingGeometryPtr MovementAnalyzer::getLatestBoudingGeomerty() const
{
    if ( !m_boudingGeometries.first() )
    {
        return BoundingBoxPtr( nullptr );
    }
    else
    {
        return m_boudingGeometries.first()->m_geometry;
    }
}

/*!
   \brief MovementAnalyzer::boundingGeometries
   Returns a QList with all BoundingGeometries calculated within this class.
 */
const QVector<BoundingGeometryWithTimeStampPtr>& MovementAnalyzer::boundingGeometries() const
{
    return m_boudingGeometries;
}

/*!
   \brief MovementAnalyzer::roll
   Returns the roll angle.
 */
const float MovementAnalyzer::roll() const
{
    return m_roll;
}

/*!
   \brief MovementAnalyzer::pitch
   Returns the pitch angle.
 */
const float MovementAnalyzer::pitch() const
{
    return m_pitch;
}

/*!
   \brief MovementAnalyzer::yaw
   Returns the yaw angle;
 */
const float MovementAnalyzer::yaw() const
{
    return m_yaw;
}

/*!
   \brief MovementAnalyzer::velocityIntervall
   Returns the size of the intervall over which the velocity will be calculated.
 */
const int MovementAnalyzer::velocityInterval() const
{
    return m_velocityInterval;
}

/*!
   \brief MovementAnalyzer::velocity
   Returns the velocity of the movement.
 */
const float MovementAnalyzer::velocity() const
{
    return m_velocity;
}

/*!
   \brief MovementAnalyzer::dataAvailable
   Returns true, if there a skeleton data available.
 */
const bool MovementAnalyzer::dataAvailable() const
{
    return m_dataAvaibale;
}

void MovementAnalyzer::calculateOriantationAndVelocity( const int timestamp )
{
    unsigned int d = timestamp - m_velocityInterval;
    for ( int i = 0; i < m_maxBoudingGeometryCount; ++i )
    {
        if ( m_boudingGeometries.at( i ) &&
             m_boudingGeometries.at( i )->m_timestamp < d )
        {
            // Calculate the catersian norm.
            QVector3D diff ( m_boudingGeometries.first()->m_geometry->x() - m_boudingGeometries.at( i )->m_geometry->x(),
                             m_boudingGeometries.first()->m_geometry->y() - m_boudingGeometries.at( i )->m_geometry->y(),
                             m_boudingGeometries.first()->m_geometry->z() - m_boudingGeometries.at( i )->m_geometry->z() );
            m_velocity =  diff.length();
            emit veloctiyChanged();
            // http://de.wikipedia.org/wiki/Polarkoordinaten
            m_yaw = AMath::radToDegF( atan2( diff.z(), diff.x() ) );
            emit yawChanged();
        }
    }
}

/*!
   \brief MovementAnalyzer::setVelocity
   Sets teh velocity to \a velocity.
 */
void MovementAnalyzer::setVelocity( const float velocity )
{
    m_velocity = velocity;
    emit veloctiyChanged();
}

/*!
   \brief MovementAnalyzer::arePointsInsideLatestBoudingGeomerty
   Returns true, if one of the points from \a points is within the first (latest inserted )
   BoundingGeometry.
   Otherwise false will be returned.
 */
bool MovementAnalyzer::arePointsInsideLatestBoudingGeomerty( const QVector<QVector3D>& points ) const
{
    if ( !m_boudingGeometries.first() )
    {
        return false;
    }
    else
    {
        return m_boudingGeometries.first()->m_geometry->arePointsInsideGeometry( points );
    }
    return false;
}

/*!
   \brief MovementAnalyzer::addBoundingGeometry
   Prepends \a boundingGeometry and \a timestamp into a vector.
   The vector will never be greater then m_maxBoudingGeometryCount.
 */
void MovementAnalyzer::addBoundingGeometry( BoundingGeometryPtr& boundingGeometry,
                                            const unsigned int timestamp )
{
    BoundingGeometryWithTimeStampPtr bb ( new BoundingGeometryWithTimeStamp( boundingGeometry,
                                                                             timestamp ) );
    m_boudingGeometries.prepend( bb );
    if ( m_boudingGeometries.count() > m_maxBoudingGeometryCount )
    {
        m_boudingGeometries.takeLast();
    }
}




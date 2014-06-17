#include "../inc/SkeletonAnalyzer.h"
#include "../inc/Skeleton.h"
#include "../inc/SkeletonData.h"
#include "../inc/Defines.h"
#include <QVector3D>

/*!
   \brief SkeletonAnalyzer::SkeletonAnalyzer
   Constructs a new SkeletonAnalzer.
   Extra space in each dimension is set to 0.1.r
 */
SkeletonAnalyzer::SkeletonAnalyzer()
    : m_boxes( QVector<BoundingBoxWithTimeStamp*>( 200 ) )
    , m_estimatedHeight( 0.0f )
    , m_deltaX( 0.1f )
    , m_deltaY( 0.1f )
    , m_deltaZ( 0.1f )
    , m_phi1( 0.0f )
    , m_phi2( 0.0f )
    , m_skeletonData( nullptr )
    , m_kneelingThreshold( 0.55f )
    , m_lyingThreshold( 0.4f )
{
    setObjectName( "SkeletonAnalyzer" );
    m_regionOfInteres.resize( 4 );
}

/*!
   \fn SkeletonAnalyzer::~SkeletonAnalyzer()
   Destroys this object.
 */
SkeletonAnalyzer::~SkeletonAnalyzer()
{
    qDeleteAll( m_boxes );
}

/*!
   \fn SkeletonAnalyzer::update
   This function updates the tracking results.
   For this purpose two bounding boxes will be constructed from \a skeleton. \n

   The first one surrounds the lower body that is the parts from the feets to the knees.
   This BoundingBox is used to derive the human movement pace and direction. \n

   The second BoundingBox surrounds the whole body, so that one can determine the basic
   pose of the tracked person. Furthermore the BoundingBox can be used to find out in which
   area of the image data the person is standing.
 */
void SkeletonAnalyzer::update( const SkeletonDataPtr& skeleton,
                               const unsigned int timestamp )
{
    m_skeletonData = SkeletonDataPtr( skeleton );
    QVector<QVector3D> lowerBody;
    lowerBody << skeleton->getJoint( SkeletonData::Joints::FootLeft );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::AnkleLeft );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::KneeLeft );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::FootRight);
    lowerBody << skeleton->getJoint( SkeletonData::Joints::AnkleRight );
    lowerBody << skeleton->getJoint( SkeletonData::Joints::KneeRight );

    // Update the bounding box for the lower body.
    if ( !m_boxes.first() ||
         !m_boxes.first()->m_box->arePointsInsideBoundingBox( lowerBody ) )
    {
        // Compute the BoundingBox if the vector of BoundingBoxes is empty
        // or if the person has left the previous one.
        BoundingBoxPtr bb ( new BoundingBox ( lowerBody,
                                              m_deltaX,
                                              m_deltaY,
                                              m_deltaZ ) );
        addBoundingBox( bb, timestamp );
    }
    else
    {
        // The person stayed in the volume of the previous BoundingBox,
        // only the timestamp has to be updated.
        BoundingBoxPtr bb ( m_boxes.first()->m_box );
        addBoundingBox( bb, timestamp );
    }

    // Compute the BoundingBox which encloses the whole body with no
    // extra space.
    m_boundingBox.calculateBoundingBox( skeleton->getJoints() );
    float z   = m_boundingBox.getZ() + m_boundingBox.getDepth() / 2;
    float x_p = m_boundingBox.getX() + m_boundingBox.getWidth() / 2;
    float x_n = m_boundingBox.getX() - m_boundingBox.getWidth() / 2;
    float y_p = m_boundingBox.getY() + m_boundingBox.getHeight() / 2;
    float y_n = m_boundingBox.getY() - m_boundingBox.getHeight() / 2;

    // Top right
    m_regionOfInteres[0].setX( x_p );
    m_regionOfInteres[0].setY( y_p );
    m_regionOfInteres[0].setZ( z );
    // Bottom right
    m_regionOfInteres[1].setX( x_p );
    m_regionOfInteres[1].setY( y_n );
    m_regionOfInteres[1].setZ( z );
    // Bottom left
    m_regionOfInteres[2].setX( x_n );
    m_regionOfInteres[2].setY( y_n );
    m_regionOfInteres[2].setZ( z );
    // Top left
    m_regionOfInteres[3].setX( x_n );
    m_regionOfInteres[3].setY( y_p );
    m_regionOfInteres[3].setZ( z );

    // Analyse the pose of the person on the basis of the BoundingBox height.
    if ( m_boundingBox.getHeight() > m_estimatedHeight &&
         m_boundingBox.getHeight() < 2.30f )
    {
        if ( m_estimatedHeight == 0 )
        {
            m_estimatedHeight = m_boundingBox.getHeight();
        }
        else
        {
            m_estimatedHeight += m_boundingBox.getHeight();
            m_estimatedHeight /= 2;
        }
        emit estimatedHeightChanged();
    }
    m_currentHeight = m_boundingBox.getHeight();
    emit currentHeightChanged();
    if ( m_currentHeight >= m_kneelingThreshold * m_estimatedHeight )
    {
        m_workerStatus = tr( "standing" );
    }
    else
    {
        if ( m_currentHeight < m_lyingThreshold * m_estimatedHeight )
        {
            m_workerStatus = tr( "lying" );
        }
        else
        {
            m_workerStatus = tr( "kneeling" );
        }
    }

    emit workerStatusChanged();

    // Compute feature vector.
    calculateFeatureVector( skeleton );
}

void SkeletonAnalyzer::setDeltaX( const float deltaX )
{
    m_deltaX = deltaX;
}

void SkeletonAnalyzer::setDeltaY(const float deltaY)
{
    m_deltaY = deltaY;
}

void SkeletonAnalyzer::setDeltaZ(const float deltaZ)
{
    m_deltaZ = deltaZ;
}

void SkeletonAnalyzer::setPhi1(const float phi1)
{
    if ( phi1 != m_phi1 )
    {
        m_phi1 = phi1;
        emit phi1Changed();
    }
}

void SkeletonAnalyzer::setPhi2(const float phi2)
{
    if ( phi2 != m_phi2 )
    {
        m_phi2 = phi2;
        emit phi2Changed();
    }
}

void SkeletonAnalyzer::setKneelingThreshold( const float threshold )
{
    if( m_kneelingThreshold != threshold )
    {
        m_kneelingThreshold = threshold;
        emit kneelingThresholdChanged();
    }
}

void SkeletonAnalyzer::setLyingThreshold( const float threshold )
{
    if ( m_lyingThreshold != threshold )
    {
        m_lyingThreshold = threshold;
        emit lyingThresholdChanged();
    }
}

float SkeletonAnalyzer::estimatedHeight() const
{
    return m_estimatedHeight;
}

float SkeletonAnalyzer::currentHeight() const
{
    return m_currentHeight;
}

float SkeletonAnalyzer::deltaX() const
{
    return m_deltaX;
}

float SkeletonAnalyzer::deltaY() const
{
    return m_deltaY;
}

float SkeletonAnalyzer::deltaZ() const
{
    return m_deltaZ;
}

float SkeletonAnalyzer::phi1() const
{
    return m_phi1;
}

float SkeletonAnalyzer::phi2() const
{
    return m_phi2;
}

float SkeletonAnalyzer::kneelingThreshold() const
{
    return m_kneelingThreshold;
}

float SkeletonAnalyzer::lyingThreshold() const
{
    return m_lyingThreshold;
}

QString SkeletonAnalyzer::workerStatus() const
{
    return m_workerStatus;
}

/*!
   \fn SkeletonAnalyzer::arePointsInLastBoundingBox
   Returns true, if all points from \a skeletonData are lying within the BoundingBox,
   that has been calculated at last.
   Otherwise false.
 */
bool SkeletonAnalyzer::arePointsInLastBoundingBox( const SkeletonDataPtr& skeletonData )
{
    if ( !m_boxes.first() )
    {
        return false;
    }
    else
    {
        return m_boxes.first()->m_box->arePointsInsideBoundingBox( skeletonData->getJoints() );
    }
}

/*!
    \fn SkeletonAnalyzer::getVelocity
    Uses \a timestamp and \a ms to calculate the avarage movement in the intervall from
    \b [ timestamp - ms , timestamp ].
 */
QVector3D SkeletonAnalyzer::getVelocity( const unsigned int timestamp,
                                         const unsigned int ms )
{
    Q_ASSERT( timestamp > ms );
    unsigned int d = timestamp - ms;
    for ( int i = 0; i < 200; ++i )
    {
        if ( m_boxes.at( i ) &&
             m_boxes.at( i )->m_timestamp < d )
        {
            return QVector3D( m_boxes.first()->m_box->getX() - m_boxes.at( i )->m_box->getX(),
                              m_boxes.first()->m_box->getY() - m_boxes.at( i )->m_box->getY(),
                              m_boxes.first()->m_box->getZ() - m_boxes.at( i )->m_box->getZ() );
        }
    }
    return QVector3D();
}

/*!
   \fn SkeletonAnalyzer::getLastBoundingBox
   Returns the BoundingBox, that has been calculated at last.
   If no BoundingBox is available \b nullptr will be returned.
 */
const BoundingBox* SkeletonAnalyzer::getLastBoundingBox() const
{
    if ( !m_boxes.first() )
    {
        return nullptr;
    }
    else
    {
        return m_boxes.first()->m_box.data();
    }
}

/*!
   \fn SkeletonAnalyzer::getBoundingBoxWholeBody
   Returns the BoundingBox enclosing the whole body from the last update() call.
 */
const BoundingBox* SkeletonAnalyzer::getBoundingBoxWholeBody() const
{
    return &m_boundingBox;
}

const SkeletonDataPtr SkeletonAnalyzer::lastSkeletonData() const
{
    return m_skeletonData;
}

const QVector<QVector3D>& SkeletonAnalyzer::regionOfInterest() const
{
    return m_regionOfInteres;
}

/*!
   \fn SkeletonAnalyzer::calculateFeatureVector
   Calculates a vector of features. \n
   Sources: \n
   1. Gestenbasierte Steuerung von interaktiven Umgebungen mithilfe der Microsoft Kinect - Ludwig Schmutzler \n
   2. Real-Time Classification of Dance Gestures from Skeleton Animation - Michais Raptis, Darko Kirovski, Hugues Hoppe \n
 */
void SkeletonAnalyzer::calculateFeatureVector( const SkeletonDataPtr& skeletonData )
{
    // Calculate the stable part between spine and shoulder center.
    // The vector is directed upwards.

    QVector3D center ( skeletonData->getJoint( SkeletonData::Joints::Spine ) -
                       skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter ) );
    QVector3D centerNormalized = center.normalized();
    float centerSquaredLength = center.lengthSquared();

    // Calulate angle for the left shoulder.
    QVector3D tmp ( skeletonData->getJoint( SkeletonData::Joints::ElbowLeft ) -
                    skeletonData->getJoint( SkeletonData::Joints::ShoulderLeft) );       // Left upper arm
    QVector3D tmpNormalized( tmp.normalized() );

    setPhi1( acosf( QVector3D::dotProduct( tmpNormalized, centerNormalized ) ) * factorRadianToDegree );
    QVector3D v1 = tmp - QVector3D::dotProduct( tmp, center )* center / centerSquaredLength;
    QVector3D v3 = QVector3D::crossProduct( tmpNormalized, centerNormalized );
    QVector3D v2 = QVector3D::crossProduct( centerNormalized, v3 );
    setPhi2( acosf( QVector3D::dotProduct( v1.normalized(), v2 ) ) * factorRadianToDegree );
}

/*!
    \fn SkeletonAnalyzer::addBoundingBox
    Enqueues \a boundingBox in the list of BoundingBoxes with \a timestamp.
 */
void SkeletonAnalyzer::addBoundingBox( BoundingBoxPtr& boundingBox,
                                       const unsigned int timestamp )
{
    m_boxes.prepend( new BoundingBoxWithTimeStamp ( boundingBox, timestamp ) );
    if ( m_boxes.count( ) > 200 )
    {
        BoundingBoxWithTimeStamp* bbw = m_boxes.takeLast();
        delete bbw;
        bbw = nullptr;
    }
}

bool SkeletonAnalyzer::calculateHeight( const SkeletonDataPtr skeletonData, float& height )
{
    // http://www.codeproject.com/Tips/380152/Kinect-for-Windows-Find-User-Height-Accurately

    if ( skeletonData->jointTrackState( SkeletonData::Joints::Head ) == SkeletonData::TrackState::Tracked &&
         skeletonData->jointTrackState( SkeletonData::Joints::ShoulderCenter ) == SkeletonData::TrackState::Tracked  &&
         skeletonData->jointTrackState( SkeletonData::Joints::Spine ) == SkeletonData::TrackState::Tracked  &&
         skeletonData->jointTrackState( SkeletonData::Joints::Hip ) == SkeletonData::TrackState::Tracked )
    {
        if ( skeletonData->jointTrackState( SkeletonData::Joints::AnkleLeft) == SkeletonData::TrackState::Tracked &&
             skeletonData->jointTrackState( SkeletonData::Joints::KneeLeft ) == SkeletonData::TrackState::Tracked )
        {
            height    = skeletonData->getJoint( SkeletonData::Joints::Head ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::Spine ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::Hip ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::AnkleLeft ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::KneeLeft ).length();
            return true;
        }
        else if ( skeletonData->jointTrackState( SkeletonData::Joints::AnkleLeft) == SkeletonData::TrackState::Tracked &&
                  skeletonData->jointTrackState( SkeletonData::Joints::KneeLeft ) == SkeletonData::TrackState::Tracked )
        {
            height    = skeletonData->getJoint( SkeletonData::Joints::Head ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::ShoulderCenter ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::Spine ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::Hip ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::AnkleLeft ).length();
            height   += skeletonData->getJoint( SkeletonData::Joints::KneeLeft ).length();
            return true;
        }
    }
    return false;
}


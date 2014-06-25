#include "../inc/SkeletonAnalyzer.h"
#include "../inc/SkeletonData.h"
#include "../inc/Defines.h"
#include "../inc/AMath.h"
#include "../inc/BBMovementAnalyzer.h"
#include <QVector3D>

/*!
   \brief SkeletonAnalyzer::SkeletonAnalyzer
   Constructs a new SkeletonAnalzer.
   Extra space in each dimension is set to 0.1.r
 */
SkeletonAnalyzer::SkeletonAnalyzer( QObject* parent )
    : QObject( parent )
    , m_estimatedHeight( 0.0f )
    , m_phi1( 0.0f )
    , m_phi2( 0.0f )
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
}

/*!
   \fn SkeletonAnalyzer::update
   This function updates the tracking results.
   For this purpose two bounding boxes will be constructed from \a skeleton. \n

   The second BoundingBox surrounds the whole body, so that one can determine the basic
   pose of the tracked person. Furthermore the BoundingBox can be used to find out in which
   area of the image data the person is standing.
 */
bool SkeletonAnalyzer::update( const SkeletonDataPtr skeleton,
                               const unsigned int timestamp )
{
    Q_UNUSED( timestamp );

    if ( !skeleton ||
         !skeleton->areMajorPointsTracked() )
    {
        return false;
    }
    // Compute the BoundingBox which encloses the whole body with no
    // extra space.
    m_boundingBox.calculateBoundingBox( skeleton->getJoints() );

    // Calculate a region of interest.
    float z   = m_boundingBox.z() + m_boundingBox.depth() / 2;
    float x_p = m_boundingBox.x() + m_boundingBox.width() / 2;
    float x_n = m_boundingBox.x() - m_boundingBox.width() / 2;
    float y_p = m_boundingBox.y() + m_boundingBox.height() / 2;
    float y_n = m_boundingBox.y() - m_boundingBox.height() / 2;

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

    // Compute feature vector.
//    calculateFeatureVector( skeleton );

    return true;
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

float SkeletonAnalyzer::estimatedHeight() const
{
    return m_estimatedHeight;
}

float SkeletonAnalyzer::currentHeight() const
{
    return m_currentHeight;
}

float SkeletonAnalyzer::phi1() const
{
    return m_phi1;
}

float SkeletonAnalyzer::phi2() const
{
    return m_phi2;
}


QString SkeletonAnalyzer::workerStatus() const
{
    return m_workerStatus;
}

/*!
   \fn SkeletonAnalyzer::getBoundingBoxWholeBody
   Returns the BoundingBox enclosing the whole body from the last update() call.
 */
const BoundingBox* SkeletonAnalyzer::getBoundingBoxWholeBody() const
{
    return &m_boundingBox;
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

    setPhi1( acosf( QVector3D::dotProduct( tmpNormalized, centerNormalized ) ) * AMath::factorRadianToDegree );
    QVector3D v1 = tmp - QVector3D::dotProduct( tmp, center )* center / centerSquaredLength;
    QVector3D v3 = QVector3D::crossProduct( tmpNormalized, centerNormalized );
    QVector3D v2 = QVector3D::crossProduct( centerNormalized, v3 );
    setPhi2( acosf( QVector3D::dotProduct( v1.normalized(), v2 ) ) * AMath::factorRadianToDegree );
}

bool SkeletonAnalyzer::calculateHeight( const SkeletonDataPtr skeletonData, float& height )
{
    // http://www.codeproject.com/Tips/380152/Kinect-for-Windows-Find-User-Height-Accurately
    return true;

}


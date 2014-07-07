#include "../inc/SkeletonAnalyzer.h"
#include "../inc/BBMovementAnalyzer.h"
#include "../../AMath/inc/AMath.h"
#include "../../../Defines.h"
#include <QVector3D>

/*!
   \brief SkeletonAnalyzer::SkeletonAnalyzer
   Constructs a new SkeletonAnalzer.
   Extra space in each dimension is set to 0.1.r
 */
SkeletonAnalyzer::SkeletonAnalyzer( QObject* parent )
    : QObject( parent )
    , m_phi1( 0.0f )
    , m_phi2( 0.0f )
    , m_userToClose( false )
    , m_hipTracked( false )
    , m_spineTracked( false )
    , m_shoulderCenterTracked( false )
    , m_headTracked( false )
    , m_shoulderLeftTracked( false )
    , m_elbowLeftTracked( false )
    , m_wristLeftTracked( false )
    , m_handLeftTracked( false )
    , m_shoulderRightTracked( false )
    , m_elbowRightTracked( false )
    , m_wristRightTracked( false )
    , m_handRightTracked( false )
    , m_hipLeftTracked( false )
    , m_kneeLeftTracked( false )
    , m_ankleLeftTracked( false )
    , m_footLeftTracked( false )
    , m_hipRightTracked( false )
    , m_kneeRightTracked( false )
    , m_ankleRightTracked( false )
    , m_footRightTracked( false )
{
    setObjectName( "SkeletonAnalyzer" );
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
         !skeleton->majorPointsTracked() )
    {
        return false;
    }
    updateJointTrackingState( skeleton );
    // Compute the BoundingBox which encloses the whole body with no
    // extra space.
    m_boundingBox.calculateBoundingBox( skeleton->getJoints() );

    // Calculate a region of interest.

    // Front of the box.
    m_regionOfInterest.setByTopLeftAndBottomRight( m_boundingBox.frontFaceTopLeftCorner(),
                                                   m_boundingBox.frontFaceBottomRightCorner() );

    // Compute feature vector.
    calculateFeatureVector( skeleton );

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

void SkeletonAnalyzer::setJoint(const SkeletonData::Joints joint)
{
    m_joint = joint;
}

/*!
   \brief SkeletonAnalyzer::setUserLooksTowardsCamera
 */
void SkeletonAnalyzer::setUserLooksTowardsCamera( const bool b )
{
    m_userLooksTowardsCamera = b;
    emit userLooksTowardsCameraChanged();
}

void SkeletonAnalyzer::updateJointTrackingState( const SkeletonDataPtr skeleton )
{
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::Hip,
                         m_hipTracked );
    emit hipTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::Spine,
                         m_spineTracked );
    emit spineTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::ShoulderCenter,
                         m_shoulderCenterTracked );
    emit shoulderCenterTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::Head,
                         m_headTracked);
    emit headTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::ShoulderLeft,
                         m_shoulderLeftTracked );
    emit shoulderLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::ElbowLeft,
                         m_elbowLeftTracked);
    emit elbowLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::WristLeft,
                         m_wristLeftTracked );
    emit wristLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::HandLeft,
                         m_handLeftTracked );
    emit handLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::ShoulderRight,
                         m_shoulderRightTracked );
    emit shoulderRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::ElbowRight,
                         m_elbowRightTracked );
    emit elbowRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::WristRight,
                         m_wristRightTracked );
    emit wristRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::HandRight,
                         m_handRightTracked );
    emit handRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::HipLeft,
                         m_hipLeftTracked );
    emit hipLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::KneeLeft,
                         m_kneeLeftTracked );
    emit kneeLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::AnkleLeft,
                         m_ankleLeftTracked );
    emit ankleLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::FootLeft,
                         m_footLeftTracked );
    emit footLeftTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::HipRight,
                         m_hipRightTracked );
    emit hipRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::KneeRight,
                         m_kneeRightTracked );
    emit kneeRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::AnkleRight,
                         m_ankleRightTracked );
    emit ankleRightTrackedChanged();
    trackingStateToBool( skeleton,
                         SkeletonData::Joints::FootRight,
                         m_footRightTracked );
    emit footRightTrackedChanged();
}

void SkeletonAnalyzer::trackingStateToBool( const SkeletonDataPtr skeleton,
                                            const SkeletonData::Joints joint,
                                            bool& state )
{
    if ( skeleton->jointTrackState( joint ) != SkeletonData::TrackState::Tracked )
    {
        state = false;
    }
    else
    {
        state = true;
    }
}

/*!
   \brief SkeletonAnalyzer::findMinimalDistanceFromCamera
   Returns the distance of the joint closest to the camera.
 */
float SkeletonAnalyzer::findMinimalDistanceFromCamera( const SkeletonDataPtr skeleton )
{
    float minDist = skeleton->getJoints().at( 0 ).z();
    for ( int i = 1; i < skeleton->getJoints().count(); ++i )
    {
        if ( minDist > skeleton->getJoints().at( i ).z() )
        {
            minDist = skeleton->getJoints().at( i ).z();
        }
    }
    return minDist;
}

float SkeletonAnalyzer::phi1() const
{
    return m_phi1;
}

float SkeletonAnalyzer::phi2() const
{
    return m_phi2;
}

/*!
   \fn SkeletonAnalyzer::getBoundingBoxWholeBody
   Returns the BoundingBox enclosing the whole body from the last update() call.
 */
const BoundingBox* SkeletonAnalyzer::getBoundingBoxWholeBody() const
{
    return &m_boundingBox;
}

/*!
   \brief SkeletonAnalyzer::regionOfInterest
   Returns a rectangle which encloses the whole body.
 */
AMath::Rectangle3D SkeletonAnalyzer::regionOfInterest() const
{
    return m_regionOfInterest;
}

SkeletonData::Joints SkeletonAnalyzer::joint() const
{
    return m_joint;
}

/*!
   \brief SkeletonAnalyzer::userToClose
   Returns true, if the user is to close to the camera.
   Otherwise false.
 */
bool SkeletonAnalyzer::userToClose() const
{
    return m_userToClose;
}

/*!
   \brief SkeletonAnalyzer::userLooksTowardsCamera
   Returns true, if the user looks towards the camera.
   False otherwise.
 */
bool SkeletonAnalyzer::userLooksTowardsCamera()
{
    return m_userLooksTowardsCamera;
}

/*!
   \brief SkeletonAnalyzer::hipTracked
   \return
 */
bool SkeletonAnalyzer::hipTracked() const
{
    return m_hipTracked;
}

bool SkeletonAnalyzer::spineTracked() const
{
    return m_spineTracked;
}

bool SkeletonAnalyzer::shoulderCenterTracked() const
{
    return m_shoulderCenterTracked;
}

bool SkeletonAnalyzer::headTracked() const
{
    return m_headTracked;
}

bool SkeletonAnalyzer::shoulderLeftTracked() const
{
    return m_shoulderLeftTracked;
}

bool SkeletonAnalyzer::elbowLeftTracked() const
{
    return m_elbowLeftTracked;
}

bool SkeletonAnalyzer::wristLeftTracked() const
{
    return m_wristLeftTracked;
}

bool SkeletonAnalyzer::handLeftTracked() const
{
    return m_handLeftTracked;
}

bool SkeletonAnalyzer::shoulderRightTracked() const
{
    return m_shoulderRightTracked;
}

bool SkeletonAnalyzer::elbowRightTracked() const
{
    return m_elbowRightTracked;
}

bool SkeletonAnalyzer::wristRightTracked() const
{
    return m_wristRightTracked;
}

bool SkeletonAnalyzer::handRightTracked() const
{
    return m_handRightTracked;
}

bool SkeletonAnalyzer::hipLeftTracked() const
{
    return m_hipLeftTracked;
}

bool SkeletonAnalyzer::kneeLeftTracked() const
{
    return m_kneeLeftTracked;
}

bool SkeletonAnalyzer::ankleLeftTracked() const
{
    return m_ankleLeftTracked;
}

bool SkeletonAnalyzer::footLeftTracked() const
{
    return m_footLeftTracked;
}

bool SkeletonAnalyzer::hipRightTracked() const
{
    return m_hipRightTracked;
}

bool SkeletonAnalyzer::kneeRightTracked() const
{
    return m_kneeRightTracked;
}

bool SkeletonAnalyzer::ankleRightTracked() const
{
    return m_ankleRightTracked;
}

bool SkeletonAnalyzer::footRightTracked() const
{
    return m_footRightTracked;
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

    // Checks if the user is to close to the camera.
    if ( findMinimalDistanceFromCamera( skeletonData ) < 0.7 )
    {
        m_userToClose = true;
    }
    else
    {
        m_userToClose = false;
    }
    emit userToCloseChanged();
}


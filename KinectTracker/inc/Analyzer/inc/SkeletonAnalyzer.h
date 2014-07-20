#ifndef SKELETONANALYZER_H
#define SKELETONANALYZER_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QRect>
#include <QSharedPointer>
#include "MovementAnalyzer.h"
#include "../../Geometries/inc/BoundingGeometry.h"
#include "../../AMath/inc/AMath.h"
#include "../../Kinect/inc/SkeletonData.h"

class QVector3D;
class SkeletonData;

class SkeletonAnalyzer : public QObject
{
    Q_OBJECT
    Q_ENUMS( SkeletonData::Joints )

public:
    SkeletonAnalyzer( QObject* parent = nullptr );
    virtual ~SkeletonAnalyzer();

    bool update( const SkeletonDataPtr skeleton,
                 const unsigned int timestamp );

    void setPhi1( const float phi1 );
    void setPhi2( const float phi2 );
    void setJoint( const SkeletonData::Joints joint );
    void setUserLooksTowardsCamera( const bool b );
    void updateJointTrackingState( const SkeletonDataPtr skeleton );
    void trackingStateToBool( const SkeletonDataPtr skeleton,
                              const SkeletonData::Joints joint,
                              bool& state );

    float                     findMinimalDistanceFromCamera( const SkeletonDataPtr skeleton );
    float                     estimatedHeight() const;
    float                     currentHeight() const;
    float                     phi1() const;
    float                     phi2() const;
    float                     kneelingThreshold() const;
    float                     lyingThreshold() const;
    QString                   workerStatus() const;
    const BoundingBox*        getBoundingBoxWholeBody() const;
    AMath::Rectangle3D        regionOfInterest() const;
    SkeletonData::Joints      joint() const;
    bool                      userToClose() const;
    bool                      userLooksTowardsCamera();

    bool                      hipTracked() const;
    bool                      spineTracked() const;
    bool                      shoulderCenterTracked() const;
    bool                      headTracked() const;
    bool                      shoulderLeftTracked() const;
    bool                      elbowLeftTracked() const;
    bool                      wristLeftTracked() const;
    bool                      handLeftTracked() const;
    bool                      shoulderRightTracked() const;
    bool                      elbowRightTracked() const;
    bool                      wristRightTracked() const;
    bool                      handRightTracked() const;
    bool                      hipLeftTracked() const;
    bool                      kneeLeftTracked() const;
    bool                      ankleLeftTracked() const;
    bool                      footLeftTracked() const;
    bool                      hipRightTracked() const;
    bool                      kneeRightTracked() const;
    bool                      ankleRightTracked() const;
    bool                      footRightTracked() const;

private:
    void calculateFeatureVector( const SkeletonDataPtr& skeletonData );

    float                m_phi1;
    float                m_phi2;
    bool                 m_userToClose;
    AMath::Rectangle3D   m_regionOfInterest;
    SkeletonDataPtr      m_skeletonData;
    SkeletonData::Joints m_joint;
    bool                 m_userLooksTowardsCamera;

    bool                 m_hipTracked;
    bool                 m_spineTracked;
    bool                 m_shoulderCenterTracked;
    bool                 m_headTracked;
    bool                 m_shoulderLeftTracked;
    bool                 m_elbowLeftTracked;
    bool                 m_wristLeftTracked;
    bool                 m_handLeftTracked;
    bool                 m_shoulderRightTracked;
    bool                 m_elbowRightTracked;
    bool                 m_wristRightTracked;
    bool                 m_handRightTracked;
    bool                 m_hipLeftTracked;
    bool                 m_kneeLeftTracked;
    bool                 m_ankleLeftTracked;
    bool                 m_footLeftTracked;
    bool                 m_hipRightTracked;
    bool                 m_kneeRightTracked;
    bool                 m_ankleRightTracked;
    bool                 m_footRightTracked;

signals:
    void phi1Changed();
    void phi2Changed();
    void jointChanged();
    void userToCloseChanged();
    void userLooksTowardsCameraChanged();

    void hipTrackedChanged();
    void spineTrackedChanged();
    void shoulderCenterTrackedChanged();
    void headTrackedChanged();
    void shoulderLeftTrackedChanged();
    void elbowLeftTrackedChanged();
    void wristLeftTrackedChanged();
    void handLeftTrackedChanged();
    void shoulderRightTrackedChanged();
    void elbowRightTrackedChanged();
    void wristRightTrackedChanged();
    void handRightTrackedChanged();
    void hipLeftTrackedChanged();
    void kneeLeftTrackedChanged();
    void ankleLeftTrackedChanged();
    void footLeftTrackedChanged();
    void hipRightTrackedChanged();
    void kneeRightTrackedChanged();
    void ankleRightTrackedChanged();
    void footRightTrackedChanged();

private:
    BoundingBox m_boundingBox;

private:
    Q_PROPERTY( SkeletonData::Joints joint
                WRITE setJoint
                READ joint
                NOTIFY jointChanged )

    Q_PROPERTY( bool userToClose MEMBER m_userToClose
                READ userToClose
                NOTIFY userToCloseChanged )

    Q_PROPERTY( bool userLooksTowardsCamera
                READ userLooksTowardsCamera
                NOTIFY userLooksTowardsCameraChanged )

    Q_PROPERTY( bool hipTracked
                READ hipTracked
                NOTIFY hipTrackedChanged )

    Q_PROPERTY( bool spineTracked
                READ spineTracked
                NOTIFY spineTrackedChanged )

    Q_PROPERTY( bool shoulderCenterTracked
                READ shoulderCenterTracked
                NOTIFY shoulderCenterTrackedChanged )

    Q_PROPERTY( bool headTracked
                READ headTracked
                NOTIFY headTrackedChanged )

    Q_PROPERTY( bool shoulderLeftTracked
                READ shoulderLeftTracked
                NOTIFY shoulderLeftTrackedChanged )

    Q_PROPERTY( bool elbowLeftTracked
                READ elbowLeftTracked
                NOTIFY elbowLeftTrackedChanged )

    Q_PROPERTY( bool wristLeftTracked
                READ wristLeftTracked
                NOTIFY wristLeftTrackedChanged )

    Q_PROPERTY( bool handLeftTracked
                READ handLeftTracked
                NOTIFY handLeftTrackedChanged )

    Q_PROPERTY( bool shoulderRightTracked
                READ shoulderRightTracked
                NOTIFY shoulderRightTrackedChanged )

    Q_PROPERTY( bool elbowRightTracked
                READ elbowRightTracked
                NOTIFY elbowRightTrackedChanged )

    Q_PROPERTY( bool wristRightTracked
                READ wristRightTracked
                NOTIFY wristRightTrackedChanged )

    Q_PROPERTY( bool handRightTracked
                READ handRightTracked
                NOTIFY handRightTrackedChanged )

    Q_PROPERTY( bool hipLeftTracked
                READ hipLeftTracked
                NOTIFY hipLeftTrackedChanged )

    Q_PROPERTY( bool kneeLeftTracked
                READ kneeLeftTracked
                NOTIFY kneeLeftTrackedChanged )

    Q_PROPERTY( bool ankleLeftTracked
                READ ankleLeftTracked
                NOTIFY ankleLeftTrackedChanged )

    Q_PROPERTY( bool footLeftTracked
                READ footLeftTracked
                NOTIFY footLeftTrackedChanged )

    Q_PROPERTY( bool hipRightTracked
                READ hipRightTracked
                NOTIFY hipRightTrackedChanged )

    Q_PROPERTY( bool kneeRightTracked
                READ kneeRightTracked
                NOTIFY kneeRightTrackedChanged )

    Q_PROPERTY( bool ankleRightTracked
                READ ankleRightTracked
                NOTIFY ankleRightTrackedChanged )

    Q_PROPERTY( bool footRightTracked
                READ footRightTracked
                NOTIFY footRightTrackedChanged )

    Q_PROPERTY( float phi1
                READ phi1
                WRITE setPhi1
                NOTIFY phi1Changed )

    Q_PROPERTY( float phi2
                READ phi2
                WRITE setPhi2
                NOTIFY phi1Changed )
};

typedef QSharedPointer<SkeletonAnalyzer> SkeletonAnalyzerPtr;

#endif // SKELETONANALYZER_H

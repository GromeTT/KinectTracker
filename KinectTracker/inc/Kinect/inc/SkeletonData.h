#ifndef SKELETONDATA_H
#define SKELETONDATA_H

#include <QObject>
#include <Windows.h>
#include <NuiApi.h>
#include <QVector3D>
#include <QVector>
#include <QSharedPointer>

class QString;

class SkeletonData : public QObject
{
    Q_OBJECT
    Q_ENUMS( Joints )

public:
    enum class Joints : char
       {
           Hip = 0,
           Spine = 1,
           ShoulderCenter = 2 ,
           Head = 3,
           ShoulderLeft = 4,
           ElbowLeft = 5,
           WristLeft = 6,
           HandLeft = 7,
           ShoulderRight = 8,
           ElbowRight = 9,
           WristRight = 10,
           HandRight = 11,
           HipLeft = 12,
           KneeLeft = 13,
           AnkleLeft = 14,
           FootLeft = 15,
           HipRight = 16,
           KneeRight = 17,
           AnkleRight = 18,
           FootRight = 19
       };

    enum class TrackState : char
        {
           Not_Tracked = NUI_SKELETON_NOT_TRACKED,
           Infered     = NUI_SKELETON_POSITION_INFERRED,
           Tracked     = NUI_SKELETON_POSITION_TRACKED
        };

    enum class Quality : char
        {
            Clipped_Right  = NUI_SKELETON_QUALITY_CLIPPED_RIGHT,
            Clipped_Left   = NUI_SKELETON_QUALITY_CLIPPED_LEFT,
            Clipped_Top    = NUI_SKELETON_QUALITY_CLIPPED_TOP,
            Clipped_Bottom = NUI_SKELETON_QUALITY_CLIPPED_BOTTOM
        };

public:
    SkeletonData();
    SkeletonData( const NUI_SKELETON_DATA& skeletonData );
    SkeletonData( const SkeletonData& other );
    ~SkeletonData();

    void setSkeletonBySkeletonData( const NUI_SKELETON_DATA& skeletonData );

    const QVector<QVector3D>& getJoints() const;
    const QVector3D&          getJoint( const Joints joint ) const;
    const TrackState          jointTrackState( const Joints joint ) const;
    const Quality             quality() const;
    int                       numberOfTrackedPoints() const;
    bool                      majorPointsTracked() const;
    bool                      allPointsTracked() const;

private:
    void initialize();

    QVector<QVector3D>  m_joints;
    QVector<TrackState> m_jointTrackState;
    Quality             m_quality;
    short               m_numberOfTrackedPoints;
};

void    copy( const Vector4& source, QVector3D& target );
QString jointToString( const SkeletonData::Joints joint );

typedef QSharedPointer<SkeletonData> SkeletonDataPtr;

#endif // SKELETONDATA_H

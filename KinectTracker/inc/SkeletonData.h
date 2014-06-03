#ifndef SKELETONDATA_H
#define SKELETONDATA_H

#include <QObject>
#include <Windows.h>
#include <NuiApi.h>
#include <QVector3D>
#include <QVector>

class SkeletonData
{

public:
    enum class Joints
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

public:
    SkeletonData();
    SkeletonData( const NUI_SKELETON_DATA& skeletonData );
    ~SkeletonData();

    void setSkeletonBySkeletonData( const NUI_SKELETON_DATA& skeletonData );

    const QVector<QVector3D>& getJoints() const;
    const QVector3D&          getJoint( const Joints joint ) const;

private:

    QVector<QVector3D> m_joints;
};

void copy( const Vector4& source, QVector3D& target );

#endif // SKELETONDATA_H

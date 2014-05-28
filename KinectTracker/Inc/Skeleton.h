#ifndef SKELETON_H
#define SKELETON_H

#include <QVector3D>
#include <Windows.h>
#include <NuiApi.h>
#include <QVector>
#include "../Inc/Vertex.h"

class Skeleton
{
public:
    enum Joints
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
    explicit Skeleton();
    explicit Skeleton( const NUI_SKELETON_DATA& skeletonData );
    ~Skeleton();

    void setSkeletonBySkeletonData( const NUI_SKELETON_DATA& skeletonData );
    const Vertex    getJoint( const Joints joint ) const;
    const Vertices& getJoints() const;

private:
    Vertices m_vertices;
};


void fillVertex( Vertex& vec, const Vector4& other );



#endif // SKELETON_H

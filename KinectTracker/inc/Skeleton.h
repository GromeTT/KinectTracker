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


public:
    explicit Skeleton();
    explicit Skeleton( const NUI_SKELETON_DATA& skeletonData );
    ~Skeleton();

private:
};

#endif // SKELETON_H

#ifndef RENDEROBJECTINTERFACE_H
#define RENDEROBJECTINTERFACE_H

#include "TransformationObject.h"

class QMatrix4x4;

class RenderObjectInterface : public TransformationObject
{
public:
    RenderObjectInterface( TransformationObject* parent = 0 );
    virtual ~RenderObjectInterface();

    void render( const QMatrix4x4& projection,
                 const QMatrix4x4& view );

private:
    virtual void renderV( const QMatrix4x4& projection,
                          const QMatrix4x4& view ) = 0;
};

#endif // RENDEROBJECTINTERFACE_H

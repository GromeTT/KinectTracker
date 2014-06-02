#include "../inc/RenderObjectInterface.h"


RenderObjectInterface::RenderObjectInterface( TransformationObject* parent )
    : TransformationObject( parent )
{
}

RenderObjectInterface::~RenderObjectInterface()
{

}

void RenderObjectInterface::render( const QMatrix4x4& projection,
                                    const QMatrix4x4& view )
{
    renderV( projection, view );
}

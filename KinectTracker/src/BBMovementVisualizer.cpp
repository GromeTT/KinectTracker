#include "../inc/BBMovementVisualizer.h"
#include "../inc/OpenGLWindow.h"
#include "../inc/RenderObject.h"

/*!
   \brief BBMovementVisualizer::BBMovementVisualizer
   Constructor.
 */
BBMovementVisualizer::BBMovementVisualizer( BBMovementAnalyzerPtr& movementAnalyzer,
                                            OpenGLWindow* window )
    : Visualizer( window )
    , m_movementAnalyzer( movementAnalyzer )
{
    window->makeContextCurrent();
    mp_boundingBoxLowerBody = window->getScene()->createCube();
    mp_boundingBoxLowerBody->setObjectName( "BoundingBoxLowerBody" );
    mp_boundingBoxLowerBody->setWireFrameMode( true );
}

/*!
   \brief BBMovementVisualizer::~BBMovementVisualizer
   Destroyes the object.
 */
BBMovementVisualizer::~BBMovementVisualizer()
{
    mp_window->getScene()->deleteObject( mp_boundingBoxLowerBody );
}

/*!
   \brief BBMovementVisualizer::renderV
 */
void BBMovementVisualizer::renderV()
{
    if ( m_movementAnalyzer->dataAvailable() )
    {

        mp_window->makeContextCurrent();
        mp_boundingBoxLowerBody->setVisible( true );
        BoundingBox* boundingBox = dynamic_cast<BoundingBox*>( m_movementAnalyzer->getLatestBoudingGeomerty().data() );
        if ( boundingBox )
        {
            mp_boundingBoxLowerBody->setPosition( boundingBox->x(),
                                                  boundingBox->y(),
                                                  boundingBox->z() );
            mp_boundingBoxLowerBody->setScale( boundingBox->width(),
                                               boundingBox->height(),
                                               boundingBox->depth() );
        }
    }
    else
    {
        mp_boundingBoxLowerBody->setVisible( false );
    }

}

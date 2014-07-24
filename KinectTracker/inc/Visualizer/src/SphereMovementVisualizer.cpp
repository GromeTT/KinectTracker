#include "../inc/SphereMovementVisualizer.h"
#include "../../OpenGL/inc/RenderObject.h"
#include "../../OpenGL/inc/OpenGLWindow.h"

SphereMovementVisualizer::SphereMovementVisualizer( SphereMovementAnalyzerPtr& movementAnalyzer,
                                                    OpenGLWindow* window )
    : Visualizer( window )
    , m_sphereMovementAnalyzer( movementAnalyzer )
{
    window->makeContextCurrent();
    mp_sphere = window->getScene()->loadObjectFromFile( "../KinectTracker/res/Sphere/sphere.obj" );
    mp_sphere->setObjectName( "Spehere" );
    mp_sphere->setWireFrameMode( true );
    mp_sphere->setVisible( false );
}

SphereMovementVisualizer::~SphereMovementVisualizer()
{

}

void SphereMovementVisualizer::renderV()
{
    if ( m_sphereMovementAnalyzer->dataAvailable() )
    {
        mp_window->makeContextCurrent();
        mp_sphere->setVisible( true );
        BoundingSphere* sphere = dynamic_cast<BoundingSphere*>( m_sphereMovementAnalyzer->getLatestBoudingGeomerty().data() );
        if ( sphere )
        {
            mp_sphere->setPosition( sphere->position() );
            mp_sphere->setScale( sphere->radius(),
                                 sphere->radius(),
                                 sphere->radius() );
        }
        else
        {
            mp_sphere->setVisible( false );
        }
    }
}

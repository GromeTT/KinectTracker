#include "../inc/SphereMovementAnalyzer.h"


SphereMovementVisualizer::SphereMovementVisualizer( SphereMovementAnalyzerPtr& movementAnalyzer,
                                                    QOpenGLWindow* window )
    : Visualizer( window )
    , m_sphereMovementAnalyzer( movementAnalyzer )
{
    window->makeContextCurrent();
    mp_sphere = window->getScene()->createSphere();
    mp_sphere->setObjectName( "Spehere" );
    mp_sphere->setWireFrameMode( true );
}

SphereMovementVisualizer::~SphereMovementVisualizer()
{

}

void SphereMovementVisualizer::renderV()
{

}

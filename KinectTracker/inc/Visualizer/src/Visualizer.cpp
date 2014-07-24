#include "../inc/Visualizer.h"
#include "../../OpenGL/inc/RenderObject.h"
#include "../../OpenGL/inc/OpenGLWindow.h"

/*!
   \brief Visualizer::Visualizer
   Constructor.
 */
Visualizer::Visualizer ( OpenGLWindow* window )
    : mp_window( window )
{
    mp_arrow = mp_window->getScene()->loadObjectFromFile( "../KinectTracker/res/Arrow/arrow.obj" );
    mp_arrow->setObjectName( "Arrow" );
    mp_arrow->setVisible( false );
    mp_arrow->setScale( QVector3D( 0.2f, 0.2f, 0.2f ) );
}

/*!
   \brief Visualizer::~Visualizer
   Destroyes the object.
 */
Visualizer::~Visualizer()
{

}

void Visualizer::render()
{
    renderV();
}

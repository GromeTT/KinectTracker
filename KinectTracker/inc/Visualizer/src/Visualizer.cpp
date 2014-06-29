#include "../inc/Visualizer.h"

/*!
   \brief Visualizer::Visualizer
   Constructor.
 */
Visualizer::Visualizer ( OpenGLWindow* window )
    : mp_window( window )
{
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

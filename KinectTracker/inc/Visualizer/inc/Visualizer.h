#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QSharedPointer>

class OpenGLWindow;
class RenderObject;

class Visualizer
{
public:
    Visualizer( OpenGLWindow* window );
    virtual ~Visualizer();

    void render();

private:
    virtual void renderV() = 0;

protected:
    OpenGLWindow* mp_window;
    RenderObject* mp_arrow;
};

typedef QSharedPointer<Visualizer> VisualizerPtr;

#endif // VISUALIZER_H

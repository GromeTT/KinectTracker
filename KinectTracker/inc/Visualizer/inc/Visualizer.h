#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QSharedPointer>

class OpenGLWindow;

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
};

typedef QSharedPointer<Visualizer> VisualizerPtr;

#endif // VISUALIZER_H

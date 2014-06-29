#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWindow>
#include "3DScene/inc/BasicUsageScene.h"

class QOpenGLContext;

typedef QSharedPointer<QOpenGLContext> OpenGLContext;

class OpenGLWindow : public QWindow
{
    Q_OBJECT

public:
    explicit OpenGLWindow( QScreen* screen = 0);
    ~OpenGLWindow();

    void init();
    ScenePtr getScene() { return m_scene; }

public:
    void resizeGL();
    void paintGL();
    void updateScene();
    void makeContextCurrent();
    OpenGLContext& getOpenGLContext();

private:
    void initializeGL();
    void keyPressEvent( QKeyEvent* event );
    void keyReleaseEvent( QKeyEvent* event );

    OpenGLContext    m_context;
    ScenePtr         m_scene;
    bool             m_strgPressed;
};

#endif // OPENGLWINDOW_H

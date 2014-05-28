#include "../Inc/OpenGLWindow.h"
#include "../Inc/BasicUsageScene.h"
#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

OpenGLWindow::OpenGLWindow( QScreen* screen )
    : QWindow( screen )
    , m_context( new QOpenGLContext )
    , m_scene( new BasicUsageScene( this ) )
    , m_strgPressed( false )
{
    setSurfaceType( OpenGLSurface );

    QSurfaceFormat format;
    format.setDepthBufferSize( 24 );
    format.setSamples( 4 );
    format.setProfile( QSurfaceFormat::CoreProfile );

    resize( 640, 480 );
    setFormat( format );
    create();

    m_context->setFormat( format );
    m_context->create();
    m_context->makeCurrent( this );

    QOpenGLFunctions* functions = m_context->functions();
    if ( !functions )
    {
        qDebug() << "OpenGL version object not available.";
    }

    initializeGL();

    connect( this, &OpenGLWindow::heightChanged, this, &OpenGLWindow::resizeGL );
    connect( this, &OpenGLWindow::widthChanged, this, &OpenGLWindow::resizeGL );
    resizeGL();
}

OpenGLWindow::~OpenGLWindow()
{
    qDebug() << "RenderWidget deleted";
}

void OpenGLWindow::resizeGL()
{
    m_context->makeCurrent( this );
    m_scene->resize( width(), height() );
}

void OpenGLWindow::paintGL()
{
    if ( !isExposed() )
    {
        return;
    }
    m_context->makeCurrent( this );
    m_scene->render();
    m_context->swapBuffers( this );
}

void OpenGLWindow::updateScene()
{
    m_scene->update( 0.0f );
    paintGL();
}

void OpenGLWindow::makeContextCurrent()
{
    m_context->makeCurrent( this );
}

OpenGLContext& OpenGLWindow::getOpenGLContext()
{
    return m_context;
}

void OpenGLWindow::initializeGL()
{
    m_scene->initialize();
}

void OpenGLWindow::keyPressEvent(QKeyEvent* event)
{
    const float stepSize = 0.2f;
    const float angle = 2.0f;

    if ( event->key() == Qt::Key_Right )
    {
        m_scene->moveCamera( stepSize, 0, 0 );
    }
    if ( event->key() == Qt::Key_Left)
    {
        m_scene->moveCamera( -stepSize, 0, 0 );
    }
    if ( event->key() == Qt::Key_Up )
    {
        m_scene->moveCamera( 0, -stepSize, 0 );
    }
    if ( event->key() == Qt::Key_Down )
    {
        m_scene->moveCamera( 0, stepSize, 0 );
    }
    if ( event->key() == Qt::Key_Minus )
    {
        m_scene->moveCamera( 0, 0, -stepSize );
    }
    if ( event->key() == Qt::Key_Plus )
    {
        m_scene->moveCamera( 0, 0, stepSize );
    }
    if ( event->key() == Qt::Key_Q )
    {
        m_scene->yawCamera( -angle );
    }
    if ( event->key() == Qt::Key_R )
    {
        m_scene->yawCamera( angle );
    }
    if ( event->key() == Qt::Key_W)
    {
        m_scene->pitchCamera( -angle );
    }
    if ( event->key() == Qt::Key_S )
    {
        m_scene->pitchCamera( angle );
    }
    if (event->key() == Qt::Key_1 )
    {
        if ( m_strgPressed )
        {
            m_scene->moveCameraToPosition( 0, 0, 10 );
            m_scene->setCameraPitch( 0 );
            m_scene->setCameraRoll( 0 );
            m_scene->setCameraYaw( -180 );
        }
        else
        {
            m_scene->moveCameraToPosition( 0, 0, -10 );
            m_scene->setCameraPitch( 0 );
            m_scene->setCameraRoll( 0 );
            m_scene->setCameraYaw( 0 );
        }
    }
    if (event->key() == Qt::Key_3 )
    {
        if ( m_strgPressed )
        {
            m_scene->moveCameraToPosition( 10, 0, 0 );
            m_scene->setCameraPitch( 0 );
            m_scene->setCameraRoll( 0 );
            m_scene->setCameraYaw( 90 );
        }
        else
        {
            m_scene->moveCameraToPosition( -10, 0, 0 );
            m_scene->setCameraPitch( 0 );
            m_scene->setCameraRoll( 0 );
            m_scene->setCameraYaw( -90 );
        }
    }
    if ( event->key() == Qt::Key_7 )
    {
        if ( m_strgPressed )
        {
            m_scene->moveCameraToPosition( 0, -10, 0 );
            m_scene->setCameraPitch( 90 );
            m_scene->setCameraRoll( 0 );
            m_scene->setCameraYaw( 0 );
        }
        else
        {
            m_scene->moveCameraToPosition( 0, 10, 0 );
            m_scene->setCameraPitch( -90 );
            m_scene->setCameraRoll( 0 );
            m_scene->setCameraYaw( 0 );
        }
    }
    if ( event->key() == Qt::Key_Control )
    {
        m_strgPressed = true;
    }

}

void OpenGLWindow::keyReleaseEvent(QKeyEvent* event)
{
    if ( event->key() == Qt::Key_Control )
    {
        m_strgPressed = false;
    }
}

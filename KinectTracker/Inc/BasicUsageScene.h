#ifndef BASICUSAGESCENE_H
#define BASICUSAGESCENE_H

#include <QOpenGLShaderProgram>
#include <QSharedPointer>
#include <QOpenGLVersionFunctions>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QFileSystemWatcher>
#include "Camera.h"
#include "Kinect.h"

class RenderObject;
class QOpenGLTexture;
class OpenGLWindow;
class QOpenGLContext;


typedef QSharedPointer<QOpenGLContext> OpenGLContext;
typedef QVector<QOpenGLShaderProgram*> ShaderPrograms;
typedef QVector<RenderObject*> RenderObjects;
typedef QVector<QOpenGLTexture*> OpenGLTextures;

class BasicUsageScene : public QObject
{
    Q_OBJECT

public:
    BasicUsageScene( OpenGLWindow* parent );
    ~BasicUsageScene();

    void initialize();
    void update( float t );
    void render();
    void resize( const int width,
                 const int height );

    void moveCameraToPosition( const float x,
                               const float y,
                               const float z );
    void moveCamera( const float x,
                     const float y,
                     const float z );
    void setCameraRoll( const float angle );
    void rollCamera( const float angle );
    void setCameraPitch( const float angle );
    void pitchCamera( const float angle );
    void setCameraYaw( const float angle );
    void yawCamera( const float angle );

    QOpenGLShaderProgram* getShaderProgram( const unsigned short i ) const;
    RenderObject* loadObjectFromFile( const QString filename );
    RenderObject* createPlane();
    RenderObject* createCube();
    RenderObject* createAxis();
    void createFloor();
    void takeSnapshot();

    RenderObject*        getRenderObject( const int index );
    const RenderObject*  getRenderObject( const int index ) const;
    RenderObject*        getRenderObjectByName( const QString& name );
    const RenderObjects& getRenderObjects() const;
    QObject*             getObjectByName( const QString& name );
    QObject*             getCamera();

signals:
    void objectHasBeenAdded( const RenderObject& object );

private:
    void prepareShaderProgram();
    void prepareTextures();

    QOpenGLShaderProgram* createShaderProgram ( const QString vertexShader,
                                                const QString fragmentShader );

    ShaderPrograms              m_shaderPrograms;
    QMatrix4x4                  m_projectionMatrix;
    RenderObjects               m_renderObjects;
    OpenGLTextures              m_textures;
    QImage*                     mp_snapshot;
    QFileSystemWatcher          m_fileSystemWatcher;
    OpenGLWindow*               mp_window;
    Camera                      m_camera;
    bool                        m_takeSnapshot;

    static const QString pathToVertexShader;
    static const QString pathToFragmentShader;
};

typedef QSharedPointer<BasicUsageScene> Scene;

#endif // BASICUSAGESCENE_H

#include "../Inc/BasicUsageScene.h"
#include "../Inc/RenderObject.h"
#include "../Inc/Vertex.h"
#include "../Inc/OpenGLWindow.h"
#include "../Inc/Floor.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QFileInfo>

const QString BasicUsageScene::pathToVertexShader =  "../KinectTracker/Shader/VertexShader.vert";
const QString BasicUsageScene::pathToFragmentShader =  "../KinectTracker/Shader/FragmentShader.frag";

/**
 * @brief BasicUsageScene::BasicUsageScene
 * Standardkonstruktor.
 */
BasicUsageScene::BasicUsageScene( OpenGLWindow* parent )
    : QObject( parent )
    , m_shaderProgram()
    , mp_texture( nullptr )
    , mp_texture1( nullptr )
    , mp_snapshot( nullptr )
    , m_takeSnapshot( false )
    , mp_window( parent )
{
    m_projectionMatrix.perspective( 45.0f, 4.0f/3.0f, 0.1f, 100.0f );
    m_camera.moveToPosition( 0.0f, 0.0f, -0.1f );

    connect( &m_fileSystemWatcher, &QFileSystemWatcher::fileChanged, this, &BasicUsageScene::updateShaderPrograms );
}

/**
 * @brief BasicUsageScene::~BasicUsageScene
 * Destruktor.
 */
BasicUsageScene::~BasicUsageScene()
{
    qDeleteAll( m_renderObjects );
}


void BasicUsageScene::initialize()
{
    prepareShaderProgram();
    prepareTextures();
}

void BasicUsageScene::update(float t)
{
    Q_UNUSED( t );
}

/**
 * @brief BasicUsageScene::render
 *
 * @param w
 * @param h
 */
void BasicUsageScene::render()
{
    mp_window->makeContextCurrent();

    glClearColor( 0, 0, 0, 1 );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );
    glEnable( GL_BLEND );

    const QMatrix4x4 m = m_camera.cameraMatrix();
    for ( int i = 0; i < m_renderObjects.count(); ++i )
    {
        RenderObject* object = m_renderObjects.at( i );
        object->render( m_projectionMatrix,
                        m_camera.cameraMatrix() );
    }
}

/**
 * @brief BasicUsageScene::resize
 * Refreshes the viewport dimensions.
 * @param width
 * Current width.
 * @param height
 * Current height.
 */
void BasicUsageScene::resize( const int width,
                              const int height )
{
    glViewport( 0, 0, width, height );
}

void BasicUsageScene::moveCameraToPosition( const float x,
                                            const float y,
                                            const float z )
{
    m_camera.moveToPosition( x, y, z );
}

/**
 * @brief BasicUsageScene::moveCamera
 * Moves the camera by \a x, \a y, \a z units.
 * @param x
 * @param y
 * @param z
 */
void BasicUsageScene::moveCamera( const float x,
                                  const float y,
                                  const float z )
{
    m_camera.moveX( x );
    m_camera.moveY( y );
    m_camera.moveZ( z );
}

void BasicUsageScene::setCameraRoll( const float angle )
{
    m_camera.setRoll( angle );
}

void BasicUsageScene::rollCamera( const float angle )
{
    m_camera.roll( angle );
}

void BasicUsageScene::setCameraPitch( const float angle )
{
    m_camera.setPitch( angle );
}

void BasicUsageScene::pitchCamera( const float angle )
{
    m_camera.pitch( angle );
}

void BasicUsageScene::setCameraYaw( const float angle )
{
    m_camera.setYaw( angle );
}

void BasicUsageScene::yawCamera( const float angle )
{
    m_camera.yaw( angle );
}

/**
 * @brief BasicUsageScene::addRenderObject
 * Adds \a object to the scene.
 * @param object
 */
void BasicUsageScene::addRenderObject( RenderObject* object )
{
    object->setShaderProgram( &m_shaderProgram );
    m_renderObjects.append( object );
    emit objectHasBeenAdded( *object );
}


RenderObject* BasicUsageScene::createPlane()
{
    mp_window->makeContextCurrent();

    Vertices vertices;
//    vertices.append( Vertex( -1,  1, 0, ) );
//    vertices.append( Vertex(  1,  1, 0 ) );
//    vertices.append( Vertex(  1, -1, 0 ) );
//    vertices.append( Vertex( -1, -1, 0 ) );

    vertices.append( Vertex( -1,  1, 0,
                              1,  1, 1, 1,
                              0,  0) );
    vertices.append( Vertex(  1,  1, 0,
                              1,  1, 1, 1,
                              1,  0) );
    vertices.append( Vertex(  1, -1, 0,
                              1,  1, 1, 1,
                              1,  1) );
    vertices.append( Vertex( -1, -1, 0,
                              1,  1, 1, 1,
                              0,  1) );

    Indices indices;
    indices << 0 << 1 << 2 << 3;

    RenderObject* object = new RenderObject( mp_window->getOpenGLContext() );
    object->setObjectName( "Plane" );
    object->setVertices( vertices );
    object->setIndices( indices );
    object->setRenderMode( GL_QUADS );
    object->setShaderProgram( &m_shaderProgram );
    object->setTexture( mp_texture );
    object->setTexture1( mp_texture1 );
    object->setUseTexture( true );

    m_renderObjects << object;

    return object;
}

RenderObject* BasicUsageScene::createCube()
{
    mp_window->makeContextCurrent();

    Vertices vertices;
    // Front-Top-Right
    vertices.append( Vertex(  0.5f,  0.5f, 0.5f ) );
    // Front-Top-Left
    vertices.append( Vertex( -0.5f,  0.5f, 0.5f ) );
    // Front-Bottom-Left
    vertices.append( Vertex( -0.5f, -0.5f, 0.5f ) );
    // Front-Bottom-Right
    vertices.append( Vertex( 0.5f, -0.5f, 0.5f ) );

    // Back-Top-Right
    vertices.append( Vertex(  0.5f,  0.5f, -0.5f ) );
    // Back-Top-Right
    vertices.append( Vertex( -0.5f,  0.5f, -0.5f ) );
    // Back-Bottom-Left
    vertices.append( Vertex( -0.5f,  -0.5f, -0.5f ) );
    // Back-Bottom-Right
    vertices.append( Vertex( 0.5f,  -0.5f, -0.5f ) );

    Indices indices;
    indices << 0 << 3 << 2 << 1; // Front
    indices << 5 << 6 << 7 << 4; // Back
    indices << 5 << 4 << 0 << 1; // Top
    indices << 2 << 3 << 7 << 6; // Bottom
    indices << 0 << 4 << 7 << 3; // Right
    indices << 1 << 2 << 6 << 5; // Left

    RenderObject* object = new RenderObject( mp_window->getOpenGLContext() );
    object->setObjectName( "Cube" );
    object->setVertices( vertices );
    object->setIndices( indices );
    object->setRenderMode( GL_QUADS );
    object->setShaderProgram( &m_shaderProgram );

    m_renderObjects << object;

    return object;
}

RenderObject* BasicUsageScene::createAxis()
{
    mp_window->makeContextCurrent();

    Vertices vertices;
    vertices.append( Vertex( 0, 0, 0,
                             1, 0, 0 ) );
    vertices.append( Vertex( 1.0, 0.0, 0.0,
                             1, 0, 0 ) );

    vertices.append( Vertex( 0.0, 1.0, 0.0,
                             0, 1, 0 ) );
    vertices.append( Vertex( 0, 0, 0,
                             0, 1, 0 ) );

    vertices.append( Vertex( 0.0, 0.0, 1.0,
                             0, 0, 1 ) );
    vertices.append( Vertex( 0, 0, 0,
                             0, 0, 1 ) );


    Indices indices;
    indices << 0 << 1 << 2 << 3 << 4 << 5;

    RenderObject* object = new RenderObject( mp_window->getOpenGLContext() );
    object->setObjectName( "Axis" );
    object->setVertices( vertices );
    object->setIndices( indices );
    object->setRenderMode( GL_LINES );
    object->setShaderProgram( &m_shaderProgram );

    m_renderObjects << object;

    return object;
}

void BasicUsageScene::createFloor()
{
    mp_window->makeContextCurrent();

    Floor* floor = new Floor( mp_window->getOpenGLContext() );
    floor->setShaderProgram( &m_shaderProgram );
    m_renderObjects << floor;
}

void BasicUsageScene::takeSnapshot()
{
    m_takeSnapshot = true;
}


RenderObject*BasicUsageScene::getRenderObject( const int index )
{
    return m_renderObjects.at( index );
}

const RenderObject* BasicUsageScene::getRenderObject( const int index ) const
{
    return m_renderObjects.at( index );
}

RenderObject*BasicUsageScene::getRenderObjectByName( const QString& name )
{
    for ( int i = 0; i < m_renderObjects.count(); ++i )
    {
        RenderObject* o = m_renderObjects.at( i );
        if ( o->objectName() == name )
        {
            return o;
        }
    }
    return nullptr;
}

const RenderObjects& BasicUsageScene::getRenderObjects() const
{
    return m_renderObjects;
}

QObject* BasicUsageScene::getObjectByName( const QString& name )
{
    if ( m_camera.objectName() == name )
    {
        return &m_camera;
    }
    else
    {
        return getRenderObjectByName( name );
    }
}

QObject* BasicUsageScene::getCamera()
{
    return &m_camera;
}

void BasicUsageScene::prepareShaderProgram()
{
    updateShaderPrograms( QString() );

    m_fileSystemWatcher.addPath( "../KinectTracker/Shader/VertexShader.vert" );
    m_fileSystemWatcher.addPath( "../KinectTracker/Shader/FragmentShader.frag" );
}

void BasicUsageScene::prepareTextures()
{
    bool result;
    QOpenGLContext::currentContext()->functions()->glActiveTexture( GL_TEXTURE0 );
    mp_texture  = new QOpenGLTexture( QImage( "C:/Users/c3p0/Desktop/Rockbell.jpg" ) );
    mp_texture->setMinMagFilters( QOpenGLTexture::Linear, QOpenGLTexture::Linear );
    result = mp_texture->create();
    if ( !result )
    {
        qDebug() << "Couldn't create texture";
    }
    QOpenGLContext::currentContext()->functions()->glActiveTexture( GL_TEXTURE1 );
    mp_texture1 = new QOpenGLTexture( QImage( "C:/Users/c3p0/Desktop/mask.jpg" ) );
    mp_texture1->setMinMagFilters( QOpenGLTexture::Linear, QOpenGLTexture::Linear );
    result = mp_texture1->create();
    if ( !result )
    {
        qDebug() << "Couldn't create texture";
    }

}

void BasicUsageScene::updateShaderPrograms( const QString& path )
{
    Q_UNUSED( path );

    m_shaderProgram.removeAllShaders();
    bool result;
    result = m_shaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex,
                                                      pathToVertexShader );
    if ( !result )
    {
        qDebug() << "Can't compile vertex shader. \n" << m_shaderProgram.log();
    }
    result = m_shaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment,
                                                      pathToFragmentShader );
    if ( !result )
    {
        qDebug() << "Can't compile fragment shader. \n" << m_shaderProgram.log();
    }

    result = m_shaderProgram.link();
    if ( !result )
    {
        qDebug() << "Can't link shader program. \n" << m_shaderProgram.log();
    }
    m_fileSystemWatcher.addPath( "../KinectTracker/Shader/VertexShader.vert" );
    m_fileSystemWatcher.addPath( "../KinectTracker/Shader/FragmentShader.frag" );
}


#include "../inc/BasicUsageScene.h"
#include "../inc/RenderObject.h"
#include "../inc/Vertex.h"
#include "../inc/OpenGLWindow.h"
#include "../inc/Floor.h"
#include "../inc/ObjectLoader.h"
#include "../inc/SkeletonRenderObject.h"
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
    , mp_snapshot( nullptr )
    , m_takeSnapshot( false )
    , mp_window( parent )
{
    m_projectionMatrix.perspective( 45.0f, 4.0f/3.0f, 0.1f, 100.0f );
    m_camera.moveToPosition( 0.0f, 0.0f, -0.1f );
}

/**
 * @brief BasicUsageScene::~BasicUsageScene
 * Destruktor.
 */
BasicUsageScene::~BasicUsageScene()
{
    qDeleteAll( m_renderObjects );
}

/*!
   \brief BasicUsageScene::initialize
   Initializes a basic shaderprogram and a texture.
 */
void BasicUsageScene::initialize()
{
    prepareShaderProgram();
    prepareTextures();
}

void BasicUsageScene::update( float t )
{
    Q_UNUSED( t );
}

/**
 * @brief BasicUsageScene::render
 */
void BasicUsageScene::render()
{
    mp_window->makeContextCurrent();

    glClearColor( 0, 0, 0, 1 );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );
    glEnable( GL_BLEND );
    glEnable( GL_DEPTH_TEST );

    int c = m_renderObjects.count();
    for ( int i = 0; i < m_renderObjects.count(); ++i )
    {
        RenderObjectInterface* object = m_renderObjects.at( i );
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

/*!
   \brief BasicUsageScene::createShaderProgram
   Creates a QOpenGLVertexShaderProgram with a vertex sahder and a fragment shader.
   \param vertexShader
   Path to vertex shader.
   \param fragmentShader
   Path to framgent shader.
 */
QOpenGLShaderProgram* BasicUsageScene::createShaderProgram( const QString vertexShader,
                                                            const QString fragmentShader )
{
    bool result;
    QOpenGLShaderProgram* shaderProgram  = new QOpenGLShaderProgram();
    result = shaderProgram->addShaderFromSourceFile( QOpenGLShader::Vertex,
                                                      vertexShader );
    if ( !result )
    {
        qWarning() << "Can't compile vertex shader. \n" << shaderProgram->log();
    }
    result = shaderProgram->addShaderFromSourceFile( QOpenGLShader::Fragment,
                                                     fragmentShader );
    if ( !result )
    {
        qWarning() << "Can't compile fragment shader. \n" << shaderProgram->log();
    }

    result = shaderProgram->link();
    if ( !result )
    {
        qWarning() << "Can't link shader program. \n" << shaderProgram->log();
    }
    m_shaderPrograms.append( shaderProgram );
    return shaderProgram;
}

/*!
   \brief BasicUsageScene::getShaderProgram
   \param i
   \return
 */
QOpenGLShaderProgram* BasicUsageScene::getShaderProgram( const unsigned short i ) const
{
    return m_shaderPrograms.at( i );
}

/**
 * @brief BasicUsageScene::loadObjectFromFile
 * Constructs an RenderObject from the file specified by \a filename.
 * If the procedure went wrong because of an invalid file or filename,
 * nullptr will be returned.
 */
RenderObject* BasicUsageScene::loadObjectFromFile( const QString filename )
{
    ObjectLoader objectLoader( filename );
    LoaderObjectPtr tmp ( objectLoader.load() );
    if ( tmp.isNull() )
    {
        return nullptr;
    }
    mp_window->makeContextCurrent();
    RenderObject* object = new RenderObject();
    object->setVertices( tmp->getVertices() );
    object->setIndices( tmp->getIndices() );
    object->setRenderMode( GL_TRIANGLES );
    object->setVisible( true );
    object->setShaderProgram( m_shaderPrograms.at( 0 ) );

    m_renderObjects << object;
    return object;
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

    RenderObject* object = new RenderObject();
    object->setObjectName( "Plane" );
    object->setVertices( vertices );
    object->setIndices( indices );
    object->setRenderMode( GL_QUADS );
    object->setShaderProgram( m_shaderPrograms.at( 0 ) );
    object->setTexture( m_textures.at( 0 ), 0 );

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

    RenderObject* object = new RenderObject();
    object->setObjectName( "Cube" );
    object->setVertices( vertices );
    object->setIndices( indices );
    object->setRenderMode( GL_QUADS );
    object->setShaderProgram( m_shaderPrograms.at( 0 ) );

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

    RenderObject* object = new RenderObject();
    object->setObjectName( "Axis" );
    object->setVertices( vertices );
    object->setIndices( indices );
    object->setRenderMode( GL_LINES );
    object->setShaderProgram( m_shaderPrograms.at( 0 ) );

    m_renderObjects << object;

    return object;
}

SkeletonRenderObject* BasicUsageScene::createSkeletonRenderObject()
{
    mp_window->makeContextCurrent();

    SkeletonRenderObject* object = new SkeletonRenderObject();
    object->setShaderProgramm( m_shaderPrograms.at( 1 ) );
    object->setObjectName( "Skeleton" );

    m_renderObjects << object;
    return object;
}

Floor* BasicUsageScene::createFloor()
{
    mp_window->makeContextCurrent();
    Floor* floor = new Floor();
    floor->setShaderProgram( m_shaderPrograms.at( 0 ) );
    m_renderObjects << floor;
    return floor;
}
/*!
   \brief BasicUsageScene::createFloor
   \param a
   \param b
   \param c
   \param d
 */
Floor* BasicUsageScene::createFloor( const float a,
                                     const float b,
                                     const float c,
                                     const float d )
{
    mp_window->makeContextCurrent();
    Floor* floor = new Floor( a, b, c, d );
    floor->setShaderProgram( m_shaderPrograms.at( 0 ) );
    m_renderObjects << floor;
    return floor;
}

void BasicUsageScene::takeSnapshot()
{
    m_takeSnapshot = true;
}


RenderObjectInterface* BasicUsageScene::getRenderObject( const int index )
{
    return m_renderObjects.at( index );
}

const RenderObjectInterface* BasicUsageScene::getRenderObject( const int index ) const
{
    return m_renderObjects.at( index );
}

RenderObjectInterface* BasicUsageScene::getRenderObjectByName( const QString& name )
{
    for ( int i = 0; i < m_renderObjects.count(); ++i )
    {
        RenderObjectInterface* o = m_renderObjects.at( i );
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

/*!
   \brief BasicUsageScene::getCamera
   Returns the camera.
 */
QObject* BasicUsageScene::getCamera()
{
    return &m_camera;
}

/*!
   \brief BasicUsageScene::deleteObject
   Deletes \a object.
 */
bool BasicUsageScene::deleteObject( RenderObject* object )
{
    for ( int i = 0; i < m_renderObjects.count(); ++i )
    {
        if ( m_renderObjects.at( i ) == object )
        {
            m_renderObjects.removeAt( i );
            return true;
        }
    }
    return false;
}

/*!
   \brief BasicUsageScene::deleteAllRenderObjects
   Deletes all RenderObjects.
 */
void BasicUsageScene::deleteAllRenderObjects()
{
    qDeleteAll( m_renderObjects );
}

void BasicUsageScene::prepareShaderProgram()
{
    createShaderProgram( pathToVertexShader,
                         pathToFragmentShader );
    createShaderProgram( "../KinectTracker/shader/SkeletonVertexShader.vert",
                         "../KinectTracker/shader/SkeletonFragmentShader.frag" );

    m_fileSystemWatcher.addPath( "../KinectTracker/shader/VertexShader.vert" );
    m_fileSystemWatcher.addPath( "../KinectTracker/shader/FragmentShader.frag" );
}

/*!
   \brief BasicUsageScene::prepareTextures
   Constructs all textures that are going to be used in the scene.
 */
void BasicUsageScene::prepareTextures()
{
    bool result;
    QOpenGLTexture* texture  = new QOpenGLTexture( QImage( "C:/Users/c3p0/Desktop/Rockbell.jpg" ) );
    texture->setMinMagFilters( QOpenGLTexture::Linear, QOpenGLTexture::Linear );
    result = texture->create();
    if ( !result )
    {
        qWarning() << "Couldn't create texture";
    }
    m_textures.append( texture );
    texture = new QOpenGLTexture( QImage( "C:/Users/c3p0/Desktop/mask.jpg" ) );
    texture->setMinMagFilters( QOpenGLTexture::Linear, QOpenGLTexture::Linear );
    result = texture->create();
    if ( !result )
    {
        qWarning() << "Couldn't create texture";
    }
    m_textures.append( texture );
}

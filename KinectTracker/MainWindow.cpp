#include "MainWindow.h"
#include "inc/OpenGL/inc/OpenGLWindow.h"
#include "inc/OpenGL/inc/RenderObject.h"
#include "inc/OpenGL/inc/BasicUsageScene.h"
#include "inc/OpenGL/inc/Floor.h"
#include "inc/OpenGL/inc/SkeletonRenderObject.h"
#include "inc/Dialogs/inc/KinectInitializeDialog.h"
#include "inc/ProcessingPipelines/inc/HOGFeatureDetector.h"
#include "inc/ProcessingPipelines/inc/DepthProcessingPipeline.h"
#include "inc/ProcessingPipelines/inc/HighLevelProcessingPipeline.h"
#include "inc/ProcessingPipelines/inc/SASDProcessingPipeline.h"
#include "inc/Visualizer/inc/BBMovementVisualizer.h"
#include "inc/Visualizer/inc/SphereMovementVisualizer.h"
#include "inc/Analyzer/inc/BBMovementAnalyzer.h"
#include "inc/Dialogs/inc/ImageAnalysisDialog.h"
#include <QMdiSubWindow>
#include <QKeyEvent>
#include <QMetaObject>
#include <QMetaProperty>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QImage>
#include <QFileInfo>
#include <QDockWidget>
#include <QVector4D>
#include <QDebug>

#include "ui_MainWindow.h"

// cvType is explained at:
// http://docs.opencv.org/modules/core/doc/basic_structures.html#Mat::Mat%28%29
// Tutorial about background subtraction at:
// http://docs.opencv.org/trunk/doc/tutorials/video/background_subtraction/background_subtraction.html

using namespace cv;

/*!
  \class MainWindow
   MainWindow derives from QMainWindow.
*/

/*!
    \fn MainWindow::MainWindow( QWidget *parent )
    Creates a MainWindow.
*/
MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , mp_openGLWindow( nullptr )
    , mp_openGLRenderWidget( nullptr )
    , mp_rgbViewerWindow( nullptr )
    , mp_rgbViewerWidget( nullptr )
    , mp_depthViewerWindow( nullptr )
    , mp_depthViewerWidget( nullptr )
    , m_kinect( new Kinect() )
    , mp_rgbViewObject( nullptr )
    , mp_depthViewObject( nullptr )
    , mp_skeletonRenderObject( nullptr )
    , m_lastTiming( 0 )
    , m_floorInitialized( false )
    , mp_floor( nullptr )
{
    ui->setupUi(this);

    // Construct explorer and it's dockWidget.
    mp_explorerDockWidget = new QDockWidget( "Explorer", this );
    mp_explorerDockWidget->setMinimumWidth( 350 );
    addDockWidget( Qt::LeftDockWidgetArea, mp_explorerDockWidget );
    mp_explorer = new PropertyBrowser( mp_explorerDockWidget );
    mp_explorerDockWidget->setWidget( mp_explorer );
    mp_explorerDockWidget->setVisible( false );

    // Construct skeleton analyser
    mp_analyserDockWidget = new QDockWidget( "SkeletonAnlyser" );
    addDockWidget(Qt::LeftDockWidgetArea, mp_analyserDockWidget );
    mp_analyzerBrowser = new PropertyBrowser( mp_analyserDockWidget );
    mp_analyserDockWidget->setWidget( mp_analyzerBrowser );
    mp_analyserDockWidget->setVisible( false );

    // Construct SizeAnalyzer
    mp_sizeAnalyzerDockWidget = new QDockWidget( "SizeAnalyzer" );
    addDockWidget(Qt::LeftDockWidgetArea, mp_sizeAnalyzerDockWidget );
    mp_sizeAnalyzerBrowser = new PropertyBrowser( mp_sizeAnalyzerDockWidget );
    mp_sizeAnalyzerDockWidget->setWidget( mp_sizeAnalyzerBrowser );
    mp_sizeAnalyzerDockWidget->setVisible( false );

    // Construct scenegraph ant it's dockWidget.
    mp_sceneDockWidget = new QDockWidget( "Scenegraph", this );
    addDockWidget( Qt::LeftDockWidgetArea, mp_sceneDockWidget );
    mp_sceneGraph = new SceneGraphWidget( mp_sceneDockWidget );
    mp_sceneDockWidget->setWidget( mp_sceneGraph );
    mp_sceneDockWidget->setVisible( false );

    mp_movementAnalyzerDockWidget = new QDockWidget( "Movementanalyzer", this );
    addDockWidget( Qt::LeftDockWidgetArea, mp_movementAnalyzerDockWidget );
    mp_movementExplorer = new PropertyBrowser( mp_movementAnalyzerDockWidget );
    mp_movementAnalyzerDockWidget->setWidget( mp_movementExplorer );

    openKinectStream();

    // Construct openglwindows and widgets.
    constructOpenGLRenderWidget();
    constructRGBViewer();
    constructDepthViewer();

    // Setup mdiArea.
    ui->mdiArea->tileSubWindows();

    // Connect timer
    connect( &m_timer, &QTimer::timeout, this, &MainWindow::updateScenes );
    // Connect mechanics
    connect( mp_sceneGraph, &SceneGraphWidget::selectionChanged, this, &MainWindow::selectObject );
    connect( mp_sceneGraph, &SceneGraphWidget::sceneChanged, this, &MainWindow::switchCatergoryOnSceneGraph );
    // Connect actions
    connect( ui->actionQuit, &QAction::triggered, this, &MainWindow::close );
    connect( ui->actionOpenKinectStream, &QAction::triggered, this, &MainWindow::showKinectDialog );
    connect( ui->actionOpenGLRender, &QAction::toggled, this, &MainWindow::actionOpenGLRenderWidgetChecked );
    connect( ui->actionTakeScreenshot, &QAction::triggered, this, &MainWindow::takeScreenshot );
    connect( ui->actionSASDMode, &QAction::toggled, this, &MainWindow::activateSASDMode );
    connect( ui->actionSABSSDMode, &QAction::toggled, this, &MainWindow::activateSABSSDMode );
    connect( ui->actionStartCapturing, &QAction::toggled, this, &MainWindow::toggleCapturing );
    connect( ui->actionImageAnalysisTool, &QAction::triggered, this, &MainWindow::openImageAnalysisDialog );
    connect( ui->actionReset, &QAction::triggered, this, &MainWindow::reset );
    connect( ui->actionSaveAsPointCloud, &QAction::triggered, this, &MainWindow::savePointCloud );
    connect( ui->actionInitializeFloor, &QAction::triggered, this, &MainWindow::initializeFloor );
    connect( ui->actionLoadPointCloud, &QAction::triggered, this, &MainWindow::loadPointCloud );
    connect( ui->actionProcessingEnabled, &QAction::toggled, this, &MainWindow::enableProcessing );

    ui->actionSASDMode->setChecked( true );
    ui->actionStartCapturing->setChecked( true );

    ui->mdiArea->activateNextSubWindow();

    switchCatergoryOnSceneGraph( SceneGraphWidget::ActiveScene::RGBProcessingPipeline );
}

/*!
    \fn MainWindow::~MainWindow

    Standarddestructor.
*/
MainWindow::~MainWindow()
{
    m_timer.stop();
    delete ui;
}

/*!
    \fn MainWindow::updateScenes

    Updates the scenes.
*/
void MainWindow::updateScenes()
{
    float dt_ns = ( m_elpasedTimer.nsecsElapsed() - m_lastTiming );
    m_lastTiming = m_elpasedTimer.nsecsElapsed();
    int timestamp = m_lastTiming / 1000000;
    float dt_ms = dt_ns / 1000000;
    float fps = 1000000000 / dt_ns;

    if ( m_kinect->isInitialized() &&
         !m_highLvlProcessingPipeline.isNull() )
    {
        bool processed = m_highLvlProcessingPipeline->process( timestamp );
        if ( processed )
        {
            SkeletonDataPtr data = m_highLvlProcessingPipeline->skeletonData();
            if ( !data.isNull() )
            {
                // case: Skeleton data is available.
                if ( m_highLvlProcessingPipeline->sizeAnalyzer()->floorInitialized() &&
                     !m_floorInitialized )
                {
                    QVector4D floorEquation = m_highLvlProcessingPipeline->sizeAnalyzer()->planeCoefficients();
                    if ( floorEquation.x() != 0 &&
                         floorEquation.y() != 0 &&
                         floorEquation.z() != 0 &&
                         floorEquation.w() != 0 )
                    {
                        mp_floor = mp_openGLWindow->getScene()->createFloor( floorEquation.x(),
                                                                             floorEquation.y(),
                                                                             floorEquation.z(),
                                                                             floorEquation.w() );
                        qDebug()<< "Floor has been initialized.";
                        m_floorInitialized = true;
                        mp_floor->setVisible( false );
                    }
                }
                mp_openGLWindow->makeContextCurrent();
                mp_skeletonRenderObject->setVisible( true );
                mp_skeletonRenderObject->updateData( data.data() );
            }
            else
            {
                // case: No skleton data availabe.

                // No need to draw the skeleton.
                mp_skeletonRenderObject->setVisible( false );
                return;
            }
        }
        // Update rgb data.
        mp_rgbViewerWindow->makeContextCurrent();
        mp_rgbViewObject->updateTexture( QOpenGLTexture::RGB8_UNorm,
                                         m_kinect->rgbStreamResolution().width(),
                                         m_kinect->rgbStreamResolution().height(),
                                         QOpenGLTexture::PixelFormat::BGR,
                                         QOpenGLTexture::PixelType::UInt8,
                                         0,
                                         m_highLvlProcessingPipeline->rgbImage(),
                                         QOpenGLTexture::Linear,
                                         QOpenGLTexture::Linear );
        // Update depth data.
        mp_depthViewerWindow->makeContextCurrent();
        mp_depthViewObject->updateTexture( QOpenGLTexture::RGB8_UNorm,
                                           m_kinect->rgbStreamResolution().width(),
                                           m_kinect->rgbStreamResolution().height(),
                                           QOpenGLTexture::PixelFormat::Luminance,
                                           QOpenGLTexture::PixelType::Int16,
                                           0,
                                           m_highLvlProcessingPipeline->depthImage(),
                                           QOpenGLTexture::Linear,
                                           QOpenGLTexture::Linear );
        if ( !m_visualizer.isNull() )
        {
            m_visualizer->render();
        }
    }

    for ( int i = 0; i < m_renderWindows.count(); ++i )
    {
        m_renderWindows.at( i )->paintGL();
    }

    ui->statusBar->showMessage( QStringLiteral( "Update Time: %1 ms Framerat: %2")
                                .arg(dt_ms)
                                .arg(fps));
}

void MainWindow::actionOpenGLRenderWidgetChecked( bool checked )
{
    if ( checked )
    {
        constructOpenGLRenderWidget();
    }
    else
    {
        Q_ASSERT( mp_openGLRenderWidget );
        mp_openGLWindow->close();
    }
}

/*!
   \brief MainWindow::takeScreenshot
   Causes the HighLevelProcessingPipeline to save the current color and depth
   image.
 */
void MainWindow::takeScreenshot()
{
    m_highLvlProcessingPipeline->takeScreenShot();
}

/*!
   \brief MainWindow::openImageAnalysisDialog
   Opens the ImageAnalysisDialog.
 */
void MainWindow::openImageAnalysisDialog()
{
    ui->actionStartCapturing->setChecked( false );
    ImageAnalysisDialog dial;
    dial.exec();
}

/*!
   \brief MainWindow::toggleCapturing
   Stops and starts the capturing.
 */
void MainWindow::toggleCapturing( bool checked )
{
    if ( checked )
    {
        m_timer.start();
    }
    else
    {
        m_timer.stop();
    }
}

/*!
   \brief MainWindow::enableProcessing
    Starts and stops the data processing by the HighLevelProcessingPipline.
 */
void MainWindow::enableProcessing( bool checked )
{
    if ( !m_highLvlProcessingPipeline.isNull() )
    {
        m_highLvlProcessingPipeline->enableProcessing( checked );
    }
}

/*!
   \brief MainWindow::activateSASDMode
   Construct all relvant objects for working in SASDMode.
 */
void MainWindow::activateSASDMode( bool checked )
{
    Q_UNUSED( checked );
    if ( checked )
    {
        mp_analyzerBrowser->setObject( nullptr );
        mp_sizeAnalyzerBrowser->setObject( nullptr );
        m_highLvlProcessingPipeline = HighLevelProcessingPipelinePtr( new SASDProcessingPipeline( m_kinect ) );
        setVisualizer();
        mp_analyzerBrowser->setObject( m_highLvlProcessingPipeline->skeletonAnalyzer().data() );
        mp_sizeAnalyzerBrowser->setObject( m_highLvlProcessingPipeline->sizeAnalyzer().data() );
        mp_movementExplorer->setObject( m_highLvlProcessingPipeline->movementAnalyzer().data() );
        switchCatergoryOnSceneGraph( mp_sceneGraph->activeScene() );
        ui->actionSABSSDMode->setChecked( false );
    }

}

/*!
   \brief MainWindow::activateSABSSDMode
   Construct all relvant object for working in SABSSDMode.
 */
void MainWindow::activateSABSSDMode( bool checked )
{
    Q_UNUSED( checked );
    if ( checked )
    {
        mp_analyzerBrowser->setObject( nullptr );
        mp_sizeAnalyzerBrowser->setObject( nullptr );
//        m_highLvlProcessingPipeline = HighLevelProcessingPipelinePtr( new SABSSDProcessingPipeline( m_kinect ) );
        setVisualizer();
        mp_analyzerBrowser->setObject( m_highLvlProcessingPipeline->skeletonAnalyzer().data() );
        mp_sizeAnalyzerBrowser->setObject( m_highLvlProcessingPipeline->sizeAnalyzer().data() );
        switchCatergoryOnSceneGraph( mp_sceneGraph->activeScene() );
        ui->actionSASDMode->setChecked( false );
    }
}

/*!
   \brief MainWindow::setVisualizer
   Sets the proper visualizer.
 */
void MainWindow::setVisualizer()
{
    BBMovementAnalyzerPtr bb_analyzer( m_highLvlProcessingPipeline->movementAnalyzer().dynamicCast<BBMovementAnalyzer>() );
    if ( !bb_analyzer.isNull() )
    {
         m_visualizer = VisualizerPtr( new BBMovementVisualizer( bb_analyzer, mp_openGLWindow ) );
    }
    SphereMovementAnalyzerPtr sp_analyzer ( m_highLvlProcessingPipeline->movementAnalyzer().dynamicCast<SphereMovementAnalyzer>() );
    if ( !sp_analyzer.isNull() )
    {
        m_visualizer = VisualizerPtr( new SphereMovementVisualizer( sp_analyzer, mp_openGLWindow ) );
    }

}

/*!
   \brief MainWindow::switchCatergoryOnSceneGraph
   Adjusts the content in the SceneGraph.
 */
void MainWindow::switchCatergoryOnSceneGraph( SceneGraphWidget::ActiveScene scene )
{
    mp_sceneGraph->clearTreeWidget();
    switch ( scene )
    {
        case SceneGraphWidget::ActiveScene::RGBProcessingPipeline:
        {
            // case: RGBProcessingPipeline
            QList<QObject*> objectList;
            QList<LowLevelProcessingPipelinePtr> tmp = m_highLvlProcessingPipeline->rgbProcessingPipelines();
            objectList.append( m_highLvlProcessingPipeline.data() );
            for ( int i = 0; i < tmp.count(); ++i )
            {
                objectList.append( tmp.at( i ).data() );
            }
            mp_sceneGraph->addObjects( objectList );
            break;
        }
        case SceneGraphWidget::ActiveScene::DepthProcessingPipeline:
        {
            // case: DepthProcessingPipeline
            mp_sceneGraph->addObject( m_highLvlProcessingPipeline->depthProcessingPipeline().data() );
            mp_sceneGraph->addObjects( m_highLvlProcessingPipeline->depthProcessingPipeline()->getComponents() );
            break;
        }
        case SceneGraphWidget::ActiveScene::RenderScene:
        {
            // case: RenderScene
            mp_sceneGraph->addObjects( mp_openGLWindow->getScene()->getRenderObjects() );
            break;
        }
    }
}

void MainWindow::reset()
{
//    mp_openGLWindow->getScene()->deleteObject( mp_floor );
//    mp_floor = nullptr;
//    m_highLvlProcessingPipeline->reset();
    m_floorInitialized = false;
}

/*!
   \brief MainWindow::savePointCloud
    Saves the current frame as point cloud.
 */
void MainWindow::savePointCloud()
{
    m_highLvlProcessingPipeline->savePointCloud();
}

/*!
   \brief MainWindow::initializeFloor
   If the floor has not been initialized yet it is
   done now.
 */
void MainWindow::initializeFloor()
{
    if ( !m_floorInitialized )
    {
        mp_floor = mp_openGLWindow->getScene()->createFloor( 0, 1, 0 );
        m_floorInitialized = true;
        // Update the plane cofficient in the SizeAnalyzer.
        m_highLvlProcessingPipeline->sizeAnalyzer()->setPlaneCoefficients( QVector4D( 1, 0, 0, 0 ) );
    }
}

/*!
   \brief MainWindow::loadPointCloud
 */
void MainWindow::loadPointCloud()
{
    OpenGLWindow* pointCloudWindow = new OpenGLWindow;
    pointCloudWindow->setTitle( "PointCloud" );
    pointCloudWindow->setObjectName( "PointCloudWindow" );
    m_renderWindows.append( pointCloudWindow );
    RenderObject* o = pointCloudWindow->getScene()->loadObjectFromFile( "PointCloud.txt" );
    if ( !o )
    {
        qDebug() << "Could not create an object for the point cloud";
    }
    else
    {
        qDebug() << "Loading point cloud was successful.";
    }
    pointCloudWindow->getScene()->moveCameraForward( -4.0f );
    pointCloudWindow->show();
    connect( pointCloudWindow, &OpenGLWindow::visibleChanged, this, &MainWindow::removeRenderWindowFromRenderList );
}

/*!
   \brief MainWindow::removeRenderWindowFromRenderList
   If the sender is an OpenGLWindow it will be removed from
   the lists of OpenGLWindow whose paintGL function is called
   during the update routine.
 */
void MainWindow::removeRenderWindowFromRenderList()
{
    OpenGLWindow* window = qobject_cast<OpenGLWindow*>( sender() );
    if ( window )
    {
        qDebug() << QStringLiteral( " %1 was closed." ).arg( window->objectName() );
        m_renderWindows.removeAll( window );
    }
}

/*!
   \fn MainWindow::showKinectDialog
   Opeens a dialog to configure connections to usb devices.
 */
void MainWindow::showKinectDialog()
{
    KinectInitializeDialog dial( m_kinect );
    dial.exec();
}

/*!
   \fn MainWindow::openKinectStream
   Initializes the kinect and opens a rgb stream and a depth stream.
 */
void MainWindow::openKinectStream()
{
    HRESULT res = m_kinect->initialize( NUI_INITIALIZE_FLAG_USES_COLOR |
                                        NUI_INITIALIZE_FLAG_USES_DEPTH |
                                        NUI_INITIALIZE_FLAG_USES_SKELETON );
    if ( res != S_OK )
    {
        switch ( res )
        {
            case Kinect::NO_SENSOR:
            {
                qDebug() << "No kinect sensor.";
                break;
            }
            case Kinect::OUT_OF_MEMORY:
            {
                qDebug() << "Not enough memory available to connect the kinect.";
                break;
            }
            case Kinect::POINTER:
            {
                qDebug() << "Invalid handle to hNextFrameEvent.";
                break;
            }
        }
    }
    else
    {
        res= m_kinect->openRGBStream( NUI_IMAGE_RESOLUTION_640x480,
                                      0,
                                      2,
                                      NULL );
        switch ( res )
        {
            case Kinect::FAIL:
            {
                qDebug() << "OpenColorStream: An unspecified error occured.";
                break;
            }
            case Kinect::INVALIDARG:
            {
                qDebug() << "OpenColorStream: Value of dwFlags parameter is NULL.";
                break;
            }
            case Kinect::DEVICE_NOT_READY:
            {
                qDebug() << "OpenColorStream: Kinect has not been initialized.";
                break;
            }
            case Kinect::OUT_OF_MEMORY:
            {
                qDebug() << "OpenColorStream: The allocation failed.";
                break;
            }
            case Kinect::POINTER:
            {
                qDebug() << "OpenColorStream: The hNextFrameEvent parameter is an invalid handle.";
            }
        }

        res = m_kinect->openDepthStream( NUI_IMAGE_RESOLUTION_640x480,
                                         0,
                                         2,
                                         NULL );
        switch ( res )
        {
            case Kinect::FAIL:
            {
                qDebug() << "DepthStream: An unspecified error occured.";
                break;
            }
            case Kinect::INVALIDARG:
            {
                qDebug() << "DepthStream: Value of dwFlags parameter is NULL.";
                break;
            }
            case Kinect::DEVICE_NOT_READY:
            {
                qDebug() << "DepthStream: Kinect has not been initialized.";
                break;
            }
            case Kinect::OUT_OF_MEMORY:
            {
                qDebug() << "DepthStream: The allocation failed.";
                break;
            }
            case Kinect::POINTER:
            {
                qDebug() << "DepthStream: The hNextFrameEvent parameter is an invalid handle.";
            }
        }
    }
}

/*!
   \brief MainWindow::selectObject
 */
void MainWindow::selectObject( const QString& text )
{
    if ( mp_sceneGraph->activeScene() == SceneGraphWidget::ActiveScene::RenderScene )
    {
        mp_explorer->setObject( mp_openGLWindow->getScene()->getObjectByName( text ) );
    }
    else
    {
        mp_explorer->setObject( mp_sceneGraph->getCurrentObject() );
    }
}

void MainWindow::constructOpenGLRenderWidget()
{
    // Construct OpenGLRenderWidget.
    mp_openGLWindow = new OpenGLWindow();
    m_renderWindows.append( mp_openGLWindow );
    mp_openGLWindow->setObjectName( "OpenGLView" );
    mp_openGLRenderWidget = QWidget::createWindowContainer( mp_openGLWindow, this );
    QMdiSubWindow* subWindow = new QMdiSubWindow( this );
    subWindow->setWidget( mp_openGLRenderWidget );
    mp_openGLRenderWidget->setWindowTitle( "OpenGLRender" );
    mp_openGLWindow->getScene()->createAxis();
    ui->mdiArea->addSubWindow( subWindow );
    mp_openGLWindow->setVisible( true );
    // Initialize scene.
    mp_openGLWindow->getScene()->moveCameraForward( -10.0f );
    // Skeleton
    mp_skeletonRenderObject = mp_openGLWindow->getScene()->createSkeletonRenderObject();
}

void MainWindow::constructRGBViewer()
{
    mp_rgbViewerWindow  = new OpenGLWindow();
    m_renderWindows.append( mp_rgbViewerWindow );
    mp_rgbViewerWindow->setObjectName( "RGBView" );
    mp_rgbViewerWidget = QWidget::createWindowContainer( mp_rgbViewerWindow, this );
    mp_rgbViewerWidget->setWindowTitle( "RGBViewer" );
    mp_rgbViewerWindow->getScene()->moveCameraForward( -4.0f );
    ui->mdiArea->addSubWindow( mp_rgbViewerWidget );
    mp_rgbViewerWindow->setVisible( true );

    mp_rgbViewObject = mp_rgbViewerWindow->getScene()->createPlane();
    mp_rgbViewObject->setUseTexture( true );
    mp_rgbViewObject->setTextureActive( 0, true );
}

void MainWindow::constructDepthViewer()
{
    mp_depthViewerWindow = new OpenGLWindow();
    m_renderWindows.append( mp_depthViewerWindow );
    mp_depthViewerWindow->setObjectName( "DeptViewer");
    mp_depthViewerWidget = QWidget::createWindowContainer( mp_depthViewerWindow, this );
    mp_depthViewerWidget->setWindowTitle( "DepthViewer" );
    mp_depthViewerWindow->getScene()->moveCameraForward( -4.0f );
    ui->mdiArea->addSubWindow( mp_depthViewerWidget );
    mp_depthViewerWindow->setVisible( true );

    mp_depthViewObject = mp_depthViewerWindow->getScene()->createPlane();
    mp_depthViewObject->setUseTexture( true );
    mp_depthViewObject->setTextureActive( 0, true );
}

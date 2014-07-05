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
#include "inc/ProcessingPipelines/inc/SABSSDProcessingPipeline.h"
#include "inc/Visualizer/inc/BBMovementVisualizer.h"
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
{
    ui->setupUi(this);

//    if( ! faceClassifier.load( "../KinectTracker/Resources/haarcascade_frontalface_alt.xml" ) )
//    {
//        qDebug() << tr( "Couldn't find classifier file. " );
//    }
    // Construct explorer and it's dockWidget.
    mp_explorerDockWidget = new QDockWidget( "Explorer", this );
    mp_explorerDockWidget->setMinimumWidth( 350 );
    addDockWidget( Qt::LeftDockWidgetArea, mp_explorerDockWidget );
    mp_explorer = new PropertyBrowser( mp_explorerDockWidget );
    mp_explorerDockWidget->setWidget( mp_explorer );

    // Construct skeleton analyser
    mp_analyserDockWidget = new QDockWidget( "SkeletonAnlyser" );
    addDockWidget(Qt::LeftDockWidgetArea, mp_analyserDockWidget );
    mp_analyzerBrowser = new PropertyBrowser( mp_analyserDockWidget );
    mp_analyserDockWidget->setWidget( mp_analyzerBrowser );

    // Construct SizeAnalyzer
    mp_sizeAnalyzerDockWidget = new QDockWidget( "SizeAnalyzer" );
    addDockWidget(Qt::LeftDockWidgetArea, mp_sizeAnalyzerDockWidget );
    mp_sizeAnalyzerBrowser = new PropertyBrowser( mp_sizeAnalyzerDockWidget );
    mp_sizeAnalyzerDockWidget->setWidget( mp_sizeAnalyzerBrowser );

    // Construct scenegraph ant it's dockWidget.
    mp_sceneDockWidget = new QDockWidget( "Scenegraph", this );
    addDockWidget( Qt::LeftDockWidgetArea, mp_sceneDockWidget );
    mp_sceneGraph = new SceneGraphWidget( mp_sceneDockWidget );
    mp_sceneDockWidget->setWidget( mp_sceneGraph );

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
        m_highLvlProcessingPipeline->process( timestamp );
        SkeletonDataPtr data = m_highLvlProcessingPipeline->skeletonData();
        if ( !data.isNull() )
        {

            mp_openGLWindow->makeContextCurrent();
            mp_skeletonRenderObject->setVisible( true );
            mp_skeletonRenderObject->updateData( data.data() );
        }
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

    mp_openGLWindow->paintGL();
    mp_rgbViewerWindow->paintGL();
    mp_depthViewerWindow->paintGL();

    ui->statusBar->showMessage( QStringLiteral( "Update Time: %1 ms Framerat: %2")
                                .arg(dt_ms)
                                .arg(fps));
}

/*!
   \fn MainWindow::processSkeletonData
   Gets skeleton data from the kinect sensor and perfoms it's analysis.
 */
void MainWindow::processSkeletonData( const unsigned int timestamp )
{
    Q_UNUSED( timestamp );
    QList<SkeletonDataPtr> skeletons;
//    HRESULT res = m_kinect->getSkeleton( skeletons );

//    if ( res != S_OK )
//    {
//        return;
//    }

    if ( skeletons.count() > 0 )
    {
        // Skeleton detected.
        mp_openGLWindow->makeContextCurrent();

        // Update the skeleton render.
        mp_skeletonRenderObject->setVisible( true );

//        SkeletonDataPtr skeleton ( skeletons.at( 0 ) );
//        mp_skeletonRenderObject->updateData( skeleton );

        // Perfomr analysis
//         m_skeletonAnalyzer.update( skeleton,
//                                    timestamp );

         // Update BoundingBox for the lower body.
//         mp_boundingBoxLowerBody->setVisible( true );
//         const BoundingBox* boundingBox = m_skeletonAnalyzer.getLastBoundingBox();
//         if ( boundingBox )
//         {
//             mp_boundingBoxLowerBody->setPosition( QVector3D( boundingBox->x(),
//                                                              boundingBox->y(),
//                                                              boundingBox->z() ) );
//             mp_boundingBoxLowerBody->setScale( QVector3D( boundingBox->width(),
//                                                           boundingBox->height(),
//                                                           boundingBox->depth() ) );

//             mp_arrowObject->setPosition( boundingBox->x(),
//                                          boundingBox->y() + 2.0f,
//                                          boundingBox->z() );
//         }
//         m_analysisResults.setValuesByVetcor( m_skeletonAnalyzer.getVelocity( timestamp, 10 ) );
//         if ( m_analysisResults.yaw() == 0 )
//         {
            // Case: Person is not moving.

            // Indicates standing person by making the arrow pointing up.
//            mp_arrowObject->setYaw( 0 );
//            mp_arrowObject->setRoll( 90 );
//         }
//         else
//         {
             // Case: Person is moving.

             // Let the arrow point in the direction of the movement.
//             mp_arrowObject->setYaw( m_analysisResults.yaw() );
//             mp_arrowObject->setRoll( 0 );
//         }

         // Update BoundingBox for the whole body.
//         mp_boundingBoxWholeBody->setVisible( true );
//         boundingBox = m_skeletonAnalyzer.getBoundingBoxWholeBody();
//         if ( boundingBox )
//         {
//             mp_boundingBoxWholeBody->setPosition( QVector3D( boundingBox->x(),
//                                                              boundingBox->y(),
//                                                              boundingBox->z() ) );
//             mp_boundingBoxWholeBody->setScale( QVector3D( boundingBox->width(),
//                                                           boundingBox->height(),
//                                                           boundingBox->depth() ) );
//         }
    }
    else
    {
        // Case: Recived Skeletonframe, but no skeleton detected.

        // Turn all objects invisible.
//        mp_boundingBoxLowerBody->setVisible( false );
    }
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
        m_highLvlProcessingPipeline = HighLevelProcessingPipelinePtr( new SABSSDProcessingPipeline( m_kinect ) );
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
    BBMovementAnalyzerPtr analyzer( m_highLvlProcessingPipeline->movementAnalyzer().dynamicCast<BBMovementAnalyzer>() );
    if ( !analyzer.isNull() )
    {
         m_visualizer = VisualizerPtr( new BBMovementVisualizer( analyzer, mp_openGLWindow ) );
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
            mp_sceneGraph->addObjects( m_highLvlProcessingPipeline->rgbProcessingPipeline()->getComponents() );
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
    mp_openGLWindow->setObjectName( "OpenGLView" );
    mp_openGLRenderWidget = QWidget::createWindowContainer( mp_openGLWindow, this );
    mp_openGLRenderWidget->setWindowTitle( "OpenGLRender" );
    mp_openGLWindow->getScene()->moveCamera( 0, 0, -8 );
    ui->mdiArea->addSubWindow( mp_openGLRenderWidget );
    mp_openGLWindow->setVisible( true );

    // Initialize scene.

    // Skeleton
    mp_skeletonRenderObject = mp_openGLWindow->getScene()->createSkeletonRenderObject();
    // BoundingBoxWholeBody

    // Arrow
//    mp_arrowObject = mp_openGLWindow->getScene()->loadObjectFromFile( "../KinectTracker/res/Arrow/arrow.obj" );
//    mp_arrowObject->setObjectName( "Arrow" );
//    mp_arrowObject->setVisible( true );
//    mp_arrowObject->setScale( QVector3D( 0.2f, 0.2f, 0.2f ) );
}

void MainWindow::constructRGBViewer()
{
    mp_rgbViewerWindow  = new OpenGLWindow();
    mp_rgbViewerWindow->setObjectName( "RGBView" );
    mp_rgbViewerWidget = QWidget::createWindowContainer( mp_rgbViewerWindow, this );
    mp_rgbViewerWidget->setWindowTitle( "RGBViewer" );
    mp_rgbViewerWindow->getScene()->moveCamera( 0, 0, -4 );
    ui->mdiArea->addSubWindow( mp_rgbViewerWidget );
    mp_rgbViewerWindow->setVisible( true );

    mp_rgbViewObject = mp_rgbViewerWindow->getScene()->createPlane();
    mp_rgbViewObject->setUseTexture( true );
    mp_rgbViewObject->setTextureActive( 0, true );
}

void MainWindow::constructDepthViewer()
{
    mp_depthViewerWindow = new OpenGLWindow();
    mp_depthViewerWindow->setObjectName( "DeptViewer");
    mp_depthViewerWidget = QWidget::createWindowContainer( mp_depthViewerWindow, this );
    mp_depthViewerWidget->setWindowTitle( "DepthViewer" );
    mp_depthViewerWindow->getScene()->moveCamera( 0, 0, -4 );
    ui->mdiArea->addSubWindow( mp_depthViewerWidget );
    mp_depthViewerWindow->setVisible( true );

    mp_depthViewObject = mp_depthViewerWindow->getScene()->createPlane();
    mp_depthViewObject->setUseTexture( true );
    mp_depthViewObject->setTextureActive( 0, true );
}

void detect_blobs(Mat& current)
{
    cv::Mat grayFrame;
    cv::cvtColor( current, grayFrame, COLOR_BGR2GRAY );
    cv::SimpleBlobDetector detector;
    //    detector.create( )
}


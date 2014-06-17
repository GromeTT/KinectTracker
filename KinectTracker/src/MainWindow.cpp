#include "../inc/MainWindow.h"
#include "../inc/OpenGLWindow.h"
#include "../inc/RGBWidget.h"
#include "../inc/RenderObject.h"
#include "../inc/BasicUsageScene.h"
#include "../inc/Vertex.h"
#include "../inc/KinectInitializeDialog.h"
#include "../inc/Skeleton.h"
#include "../inc/BoundingBox.h"
#include "../inc/Floor.h"
#include "../inc/Explorer.h"
#include "../inc/SceneGraphWidget.h"
#include "../inc/Floor.h"
#include "../inc/SignalBlocker.h"
#include "../inc/DepthViewerWidget.h"
#include "../inc/ObjectLoader.h"
#include "../inc/SkeletonRenderObject.h"
#include "../inc/HOGFeatureDetector.h"
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
    , mp_boundingBoxWholeBody( nullptr )
    , mp_boundingBoxLowerBody( nullptr )
    , mp_arrowObject( nullptr )
    , m_backgroundSubtractor( new BackgroundSubtractorMOG )
    , m_lastTiming( 0 )
    , m_backGroundSubtraction( false )
    , mp_rgbData( nullptr )
    , mp_depthData( nullptr )
    , m_updateSkeletonData( true )
    , m_updateRGBData( true )
    , m_updateDepthData( true )
    , m_takeSnapshot( true )
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

    // Construct Skeleton analysere
    mp_skeletonAnalyserDockWidget = new QDockWidget( "SkeletonAnlyser" );
    addDockWidget(Qt::LeftDockWidgetArea, mp_skeletonAnalyserDockWidget );
    mp_skeletonAnalyserExplorer = new PropertyBrowser( mp_skeletonAnalyserDockWidget );
    mp_skeletonAnalyserDockWidget->setWidget( mp_skeletonAnalyserExplorer );
    mp_skeletonAnalyserExplorer->setObject( &m_skeletonAnalyzer );

    // Construct result explorer and it's dockWidget.
    mp_resultExpDockWidget = new QDockWidget( "Anlysis", this );
    addDockWidget( Qt::LeftDockWidgetArea, mp_resultExpDockWidget );
    mp_resultExp = new PropertyBrowser( mp_resultExpDockWidget );
    mp_resultExpDockWidget->setWidget( mp_resultExp );
    mp_resultExp->setObject( &m_analysisResults );

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

    mp_rgbData   = new uchar [ m_kinect->getRGBStreamResoultion().width() * m_kinect->getRGBStreamResoultion().height() * 3 ];
    mp_depthData = new uchar [ m_kinect->getDepthStreamResolution().width() * m_kinect->getDepthStreamResolution().height() * 3 ];

    // Connect signals and slots.
    connect( ui->actionQuit, &QAction::triggered, this, &MainWindow::close );
    connect( ui->actionOpenKinectStream, &QAction::triggered, this, &MainWindow::showKinectDialog );
    connect( mp_sceneGraph, &SceneGraphWidget::selectionChanged, this, &MainWindow::selectObject );
    connect( ui->actionOpenGLRender, &QAction::toggled, this, &MainWindow::actionOpenGLRenderWidgetChecked );
    connect( ui->actionBackground_Subtraction, &QAction::triggered, this, &MainWindow::actionBackgroundSubtractionToggled );
    connect( ui->actionTake_snapshot, &QAction::triggered, this, &MainWindow::takeSnapshot );
    connect( &m_timer, &QTimer::timeout, this, &MainWindow::updateScenes );

    connect ( ui->actionKeep_Skeleton_up_to_date, &QAction::toggled, this, &MainWindow::setUpdateSkeltonData );
    connect ( ui->actionKeep_rgb_up_to_date, &QAction::toggled, this, &MainWindow::setUpdateRGBData );
    connect ( ui->actionKeep_depth_up_to_date, &QAction::toggled, this, &MainWindow::setUpdateDepthData );

    connect ( ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::subWindowActivated );

    ui->actionKeep_Skeleton_up_to_date->setChecked( m_updateSkeletonData );
    ui->actionKeep_rgb_up_to_date->setChecked( m_updateRGBData );
    ui->actionKeep_depth_up_to_date->setChecked( m_updateDepthData );

    ui->mdiArea->activateNextSubWindow();

    time.start();
    m_timer.start( 0 );
    m_elpasedTimer.start();
}

/*!
    \fn MainWindow::~MainWindow

    Standarddestructor.
*/
MainWindow::~MainWindow()
{
    delete [] mp_rgbData;
    delete [] mp_depthData;
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

    if ( m_kinect->isInitialized() )
    {
        // Process skeleton data
        if ( m_updateSkeletonData )
        {
            processSkeletonData( timestamp );
        }

        // Process Depth data.
        if ( m_updateDepthData )
        {
            processDepthData();
        }

        // Process RGB data
        if ( m_updateRGBData )
        {
            processRGBData();
        }
    }

    mp_openGLWindow->paintGL();
    mp_rgbViewerWindow->paintGL();
    mp_depthViewerWindow->paintGL();

    QString status = "Nothing detected.";
    ui->statusBar->showMessage( QString("Status: %4 Update Time: %1 ms Framerat: %2")
                                .arg(dt_ms)
                                .arg(fps)
                                .arg (status ) );
}

/*!
   \brief MainWindow::processRGBData
   Processes the RGB data provided by the kinect sensor.
 */
void MainWindow::processRGBData()
{
    HRESULT res;
    res = m_kinect->getRGBImage( mp_rgbData );
    if ( res == S_OK )
    {

        cv::Mat curr ( m_kinect->getDepthStreamResolution().height(),
                       m_kinect->getRGBStreamResoultion().width(),
                       CV_8UC3,
                       mp_rgbData );
        SkeletonDataPtr skeleton( m_skeletonAnalyzer.lastSkeletonData() );

        m_imageAnalyzer.analyze( curr );

        if ( !skeleton.isNull() )
        {
            const QVector<QVector3D> regionOfInterest = m_skeletonAnalyzer.regionOfInterest();
            QVector2D p1 = transformFromSkeltonToRGB( regionOfInterest.at( 0 ) ); // Top right
            QVector2D p2 = transformFromSkeltonToRGB( regionOfInterest.at( 2 ) ); // Bottom left
            Scalar color ( 0, 255, 255 );
            rectangle( curr, Point( p1.x(), p1.y() ), Point( p2.x(), p2.y() ), color, 5 );

        }
        mp_rgbViewerWindow->makeContextCurrent();
        mp_rgbViewObject->updateTexture( QOpenGLTexture::RGB8_UNorm,
                                         m_kinect->getRGBStreamResoultion().width(),
                                         m_kinect->getRGBStreamResoultion().height(),
                                         QOpenGLTexture::PixelFormat::BGR,
                                         QOpenGLTexture::PixelType::UInt8,
                                         0,
                                         curr.data,
                                         QOpenGLTexture::Linear,
                                         QOpenGLTexture::Linear );
    }
}

/*!
   \brief MainWindow::processDepthData
 */
void MainWindow::processDepthData()
{
    HRESULT res;
    res = m_kinect->getDepthImage( mp_depthData );
    if ( res == S_OK )
    {
        mp_depthViewerWindow->makeContextCurrent();
        mp_depthViewObject->updateTexture( QOpenGLTexture::RGB8_UNorm,
                                           m_kinect->getDepthStreamResolution().width(),
                                           m_kinect->getDepthStreamResolution().height(),
                                           QOpenGLTexture::PixelFormat::BGR,
                                           QOpenGLTexture::PixelType::UInt8,
                                           0,
                                           mp_depthData,
                                           QOpenGLTexture::Linear,
                                           QOpenGLTexture::Linear );
    }
}

/*!
   \fn MainWindow::processSkeletonData
   Gets skeleton data from the kinect sensor and perfoms it's analysis.
 */
void MainWindow::processSkeletonData( const unsigned int timestamp )
{
    QList<SkeletonDataPtr> skeletons;
    HRESULT res = m_kinect->getSkeleton( skeletons );

    if ( res != S_OK )
    {
        return;
    }

    if ( skeletons.count() > 0 )
    {
        // Skeleton detected.
        mp_openGLWindow->makeContextCurrent();

        mp_arrowObject->setVisible( true );

        // Update the skeleton render.
        mp_skeletonRenderObject->setVisible( true );

        SkeletonDataPtr skeleton ( skeletons.at( 0 ) );
        mp_skeletonRenderObject->updateData( skeleton );

        // Perfomr analysis
         m_skeletonAnalyzer.update( skeleton,
                                    timestamp );

         // Update BoundingBox for the lower body.
         mp_boundingBoxLowerBody->setVisible( true );
         const BoundingBox* boundingBox = m_skeletonAnalyzer.getLastBoundingBox();
         if ( boundingBox )
         {
             mp_boundingBoxLowerBody->setPosition( QVector3D( boundingBox->getX(),
                                                              boundingBox->getY(),
                                                              boundingBox->getZ() ) );
             mp_boundingBoxLowerBody->setScale( QVector3D( boundingBox->getWidth(),
                                                           boundingBox->getHeight(),
                                                           boundingBox->getDepth() ) );

             mp_arrowObject->setPosition( boundingBox->getX(),
                                          boundingBox->getY() + 2.0f,
                                          boundingBox->getZ() );
         }
         m_analysisResults.setValuesByVetcor( m_skeletonAnalyzer.getVelocity( timestamp, 10 ) );
         if ( m_analysisResults.yaw() == 0 )
         {
            // Case: Person is not moving.

            // Indicates standing person by making the arrow pointing up.
            mp_arrowObject->setYaw( 0 );
            mp_arrowObject->setRoll( 90 );
         }
         else
         {
             // Case: Person is moving.

             // Let the arrow point in the direction of the movement.
             mp_arrowObject->setYaw( m_analysisResults.yaw() );
             mp_arrowObject->setRoll( 0 );
         }

         // Update BoundingBox for the whole body.
         mp_boundingBoxWholeBody->setVisible( true );
         boundingBox = m_skeletonAnalyzer.getBoundingBoxWholeBody();
         if ( boundingBox )
         {
             mp_boundingBoxWholeBody->setPosition( QVector3D( boundingBox->getX(),
                                                              boundingBox->getY(),
                                                              boundingBox->getZ() ) );
             mp_boundingBoxWholeBody->setScale( QVector3D( boundingBox->getWidth(),
                                                           boundingBox->getHeight(),
                                                           boundingBox->getDepth() ) );
         }
    }
    else
    {
        // Case: Recived Skeletonframe, but no skeleton detected.

        // Turn all objects invisible.
        mp_skeletonRenderObject->setVisible( false );
        mp_boundingBoxLowerBody->setVisible( false );
        mp_boundingBoxWholeBody->setVisible( false );
        mp_arrowObject->setVisible( false );
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

void MainWindow::actionBackgroundSubtractionToggled()
{
    m_backGroundSubtraction = !m_backGroundSubtraction;
}

void MainWindow::takeSnapshot()
{
    m_takeSnapshot = true;
}

void MainWindow::setUpdateSkeltonData( const bool on )
{
    if ( m_updateSkeletonData != on )
    {
        m_updateSkeletonData = on;
        emit updateSkeletonDataChanged();
    }
}

void MainWindow::setUpdateRGBData( const bool on )
{
    if ( m_updateRGBData != on )
    {
        m_updateRGBData = on;
        emit updateRGBDataChanged();
    }
}

void MainWindow::setUpdateDepthData( const bool on )
{
    if ( m_updateDepthData != on )
    {
        m_updateDepthData = on;
        emit updateDepthDataChanged();
    }
}

void MainWindow::subWindowActivated( QMdiSubWindow* subWindow )
{
    if( !subWindow )
    {
        return;
    }
    mp_sceneGraph->clearTreeWidget();
    if ( subWindow->widget() == mp_openGLRenderWidget )
    {
        mp_sceneGraph->addObject( *mp_openGLWindow->getScene()->getCamera() );
        mp_sceneGraph->addObjects( mp_openGLWindow->getScene()->getRenderObjects() );
    }
    else if ( subWindow->widget() == mp_rgbViewerWidget )
    {
        mp_sceneGraph->addObjects( m_imageAnalyzer.getPiplineComponents() );
    }
    else if( subWindow->widget() == mp_depthViewerWidget )
    {
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

void MainWindow::selectObject( const QString& text )
{
    if ( !ui->mdiArea->activeSubWindow() )
    {
        return;
    }
    if ( ui->mdiArea->activeSubWindow()->widget() == mp_openGLRenderWidget )
    {
        mp_explorer->setObject( mp_openGLWindow->getScene()->getObjectByName( text ) );
    }
    else if ( ui->mdiArea->activeSubWindow()->widget() == mp_rgbViewerWidget )
    {
        mp_explorer->setObject( mp_sceneGraph->getCurrentObject() );
    }
    else if ( ui->mdiArea->activeSubWindow()->widget() == mp_depthViewerWidget )
    {

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
    // BoundingBoxLowerBody
    mp_boundingBoxLowerBody = mp_openGLWindow->getScene()->createCube();
    mp_boundingBoxLowerBody->setObjectName( "BoundingBoxLowerBody" );
    mp_boundingBoxLowerBody->setWireFrameMode( true );
    // BoundingBoxWholeBody
    mp_boundingBoxWholeBody = mp_openGLWindow->getScene()->createCube();
    mp_boundingBoxWholeBody->setObjectName( "BoundingBoxWholeBody" );
    mp_boundingBoxWholeBody->setWireFrameMode( true );
    // Arrow
    mp_arrowObject = mp_openGLWindow->getScene()->loadObjectFromFile( "../KinectTracker/res/Arrow/arrow.obj" );
    mp_arrowObject->setObjectName( "Arrow" );
    mp_arrowObject->setVisible( true );
    mp_arrowObject->setScale( QVector3D( 0.2f, 0.2f, 0.2f ) );
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


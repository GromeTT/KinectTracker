#include "../Inc/MainWindow.h"
#include "../Inc/OpenGLWindow.h"
#include "../Inc/RGBWidget.h"
#include "../Inc/RenderObject.h"
#include "../Inc/BasicUsageScene.h"
#include "../Inc/Vertex.h"
#include "../Inc/KinectInitializeDialog.h"
#include "../Inc/Skeleton.h"
#include "../Inc/BoundingBox.h"
#include "../Inc/Floor.h"
#include "../Inc/Explorer.h"
#include "../Inc/SceneGraphWidget.h"
#include "../Inc/Floor.h"
#include "../Inc/SignalBlocker.h"
#include "../Inc/DepthViewerWidget.h"
#include "../Inc/ObjectLoader.h"
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
    , mp_skeletonObject( nullptr )
    , mp_boundingBox( nullptr )
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

    if( ! faceClassifier.load( "../KinectTracker/Resources/haarcascade_frontalface_alt.xml" ) )
    {
        qDebug() << tr( "Couldn't find classifier file. " );
    }

    // Construct explorer and it's dockWidget.
    mp_explorerDockWidget = new QDockWidget( "Explorer", this );
    addDockWidget( Qt::LeftDockWidgetArea, mp_explorerDockWidget );
    mp_explorer = new Explorer( mp_explorerDockWidget );
    mp_explorerDockWidget->setWidget( mp_explorer );

    // Construct result explorer and it's dockWidget.
    mp_resultExpDockWidget = new QDockWidget( "Anlysis", this );
    addDockWidget( Qt::LeftDockWidgetArea, mp_resultExpDockWidget );
    mp_resultExp = new Explorer( mp_resultExpDockWidget );
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

    // Process RGB data
    if ( m_updateRGBData )
    {
        processRGBData();
    }
    // Process Depth data.
    if ( m_updateDepthData )
    {
        processDepthData();
    }
    // Process skeleton data
    if ( m_updateSkeletonData )
    {
        processSkeletonData( timestamp );
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
        m_imageAnalyzer.analyze( curr );
        if ( m_takeSnapshot )
        {
            m_imageAnalyzer.setSnapshot( curr );
            m_takeSnapshot = false;
        }
        imshow( "BS Window", curr );
        if ( m_backGroundSubtraction )
        {

//            cv::Mat frame_gray;
//            cvtColor( curr, frame_gray, CV_BGR2GRAY );
//            equalizeHist( frame_gray, frame_gray );
//            std::vector<Rect> faces;
//            faceClassifier.detectMultiScale( frame_gray, faces );
//            for ( int i = 0; i < faces.size(); ++i )
//            {
//                Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
//                ellipse( curr, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
//            }

//            cv::Mat foreground;
//            m_backgroundSubtractor->operator ()( curr, foreground );
//            vector<vector<Point> > contours;
//            vector<Vec4i> hierachy;
//            cv::erode( foreground, foreground, cv::Mat( 2, 2, CV_8UC1 ) );
//            cv::imshow( "Errode", foreground ) ;
//            cv::dilate( foreground, foreground, cv::Mat( 2, 2, CV_8UC1 ) );
//            cv::imshow( "Dilate", foreground ) ;
//            cv::findContours( foreground, contours, hierachy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
//            for ( int i = 0; i < contours.size(); ++i )
//            {
//                cv::drawContours( curr, contours, i, cv::Scalar( 255, 0, 0 ) );
//            }
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
        else
        {
            mp_rgbViewerWindow->makeContextCurrent();
            mp_rgbViewObject->updateTexture( QOpenGLTexture::RGB8_UNorm,
                                             m_kinect->getRGBStreamResoultion().width(),
                                             m_kinect->getRGBStreamResoultion().height(),
                                             QOpenGLTexture::PixelFormat::BGR,
                                             QOpenGLTexture::PixelType::UInt8,
                                             0,
                                             mp_rgbData,
                                             QOpenGLTexture::Linear,
                                             QOpenGLTexture::Linear );
        }
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

void MainWindow::processSkeletonData( const unsigned int timestamp )
{
    QList<Skeleton*> skeletons;
    HRESULT res = m_kinect->getSkeleton( skeletons );
    if ( res != S_OK )
    {
        return;
    }
    if ( skeletons.count() > 0 )
    {
        Indices indices;
        indices << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11
                << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19;
        mp_openGLWindow->makeContextCurrent();
        mp_skeletonObject->setVertices( skeletons.at(0)->getJoints() );
        mp_skeletonObject->setIndices( indices );
        mp_skeletonObject->setRenderMode( GL_POINTS );
        mp_skeletonObject->setVisible( true );
        mp_boundingBox->setVisible( true );

         m_skeletonAnalyzer.update( skeletons.at( 0 ),
                                    timestamp );
         const BoundingBox* boundingBox = m_skeletonAnalyzer.getLastBoundingBox();
         if ( boundingBox )
         {
             mp_boundingBox->setPosition( QVector3D( boundingBox->getX(),
                                                     boundingBox->getY(),
                                                     boundingBox->getZ() ) );
             mp_boundingBox->setScale( QVector3D( boundingBox->getWidth(),
                                                  boundingBox->getHeight(),
                                                  boundingBox->getDepth() ) );
             mp_boundingBox->setWireFrameMode( true );
             mp_arrowObject->setPosition( boundingBox->getX(),
                                          boundingBox->getY() + 1.5f,
                                          boundingBox->getZ() );
         }
         m_analysisResults.setValuesByVetcor( m_skeletonAnalyzer.getVelocity( timestamp, 10 ) );
         if ( m_analysisResults.directionY() == 0 )
         {
            mp_arrowObject->setYaw( 0 );
            mp_arrowObject->setRoll( 90 );
         }
         else
         {
             mp_arrowObject->setYaw( m_analysisResults.directionY() );
             mp_arrowObject->setRoll( 0 );
         }
    }
    else
    {
        mp_skeletonObject->setVisible( false );
        mp_boundingBox->setVisible( false );

        mp_arrowObject->setYaw( m_analysisResults.directionY() );
        mp_arrowObject->setRoll( 0 );
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
    if ( subWindow->widget() == mp_openGLRenderWidget )
    {
        mp_sceneGraph->clearTreeWidget();
        mp_sceneGraph->addObject( *mp_openGLWindow->getScene()->getCamera() );
        mp_sceneGraph->addObjects( mp_openGLWindow->getScene()->getRenderObjects() );
    }
    else if ( subWindow->widget() == mp_rgbViewerWidget )
    {
        mp_sceneGraph->clearTreeWidget();
        mp_sceneGraph->addObjects( m_imageAnalyzer.getPiplineComponents() );
    }
    else if( subWindow->widget() == mp_depthViewerWidget )
    {
        mp_sceneGraph->clearTreeWidget();
    }
}

/**
 * @brief MainWindow::initializeKinect
 */
void MainWindow::showKinectDialog()
{
    KinectInitializeDialog dial( m_kinect );
    dial.exec();
}

/**
 * @brief MainWindow::openKinectStream
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
        mp_explorer->setObject( m_imageAnalyzer.getObjectByName( text ) );
    }
    else if ( ui->mdiArea->activeSubWindow()->widget() == mp_depthViewerWidget )
    {

    }
}

void MainWindow::constructOpenGLRenderWidget()
{
    // Construct OpenGLRenderWidget.
    mp_openGLWindow = new OpenGLWindow();
    mp_openGLRenderWidget = QWidget::createWindowContainer( mp_openGLWindow, this );
    mp_openGLRenderWidget->setWindowTitle( "OpenGLRender" );
    mp_openGLWindow->getScene()->moveCamera( 0, 0, -8 );
    ui->mdiArea->addSubWindow( mp_openGLRenderWidget );
    mp_openGLWindow->setVisible( true );

    // Initialize scene.
    mp_skeletonObject  = mp_openGLWindow->getScene()->createCube();
    mp_skeletonObject->setObjectName( "Skeleton" );
    mp_boundingBox     = mp_openGLWindow->getScene()->createCube();
    mp_boundingBox->setObjectName( "BoundingBox" );
    mp_openGLWindow->getScene()->createFloor();

    mp_arrowObject     = mp_openGLWindow->getScene()->loadObjectFromFile( "../KinectTracker/Resources/Arrow/arrow.obj" );
}

void MainWindow::constructRGBViewer()
{
    mp_rgbViewerWindow  = new OpenGLWindow();
    mp_rgbViewerWidget = QWidget::createWindowContainer( mp_rgbViewerWindow, this );
    mp_rgbViewerWidget->setWindowTitle( "RGBViewer" );
    mp_rgbViewerWindow->getScene()->moveCamera( 0, 0, -4 );
    ui->mdiArea->addSubWindow( mp_rgbViewerWidget );
    mp_rgbViewerWindow->setVisible( true );

    mp_rgbViewObject   = mp_rgbViewerWindow->getScene()->createPlane();
    mp_rgbViewObject->setUseTexture( true );
    mp_rgbViewObject->setTextureActive( 0, true );
}

void MainWindow::constructDepthViewer()
{
    mp_depthViewerWindow = new OpenGLWindow();
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

/*!
 *  \fn MainWindow::updateDepthDataChanged()
 *
 */

/*!
    \fn MainWindow::updateRGBDataChanged()
    */

/*!
    \fn MainWindow::updateSkeletonDataChanged()
    */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "inc/Kinect/inc/Kinect.h"
#include "inc/PropertyBrowser/inc/PropertyBrowser.h"
#include "inc/ProcessingPipelines/inc/HighLevelProcessingPipeline.h"
#include "inc/Visualizer/inc/Visualizer.h"
#include "inc/SceneGraph/inc/SceneGraphWidget.h"
#include "inc/OpenGL/inc/Floor.h"

class OpenGLWidget;
class OpenGLWindow;
class QLabel;
class RenderObject;
class QOpenGLTexture;
class Explorer;
class QKeyPressEvent;
class DepthViewerWidget;
class QMdiSubWindow;
class SkeletonRenderObject;
class SkeletonData;
class ImageAnalyzer;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

private:
    void showKinectDialog();
    void openKinectStream();
    void selectObject( const QString& text );
    void constructOpenGLRenderWidget();
    void constructRGBViewer();
    void constructDepthViewer();
    void updateScenes();
    void actionOpenGLRenderWidgetChecked( bool checked );
    void takeScreenshot();
    void openImageAnalysisDialog();
    void toggleCapturing( bool checked );
    void enableProcessing( bool checked );
    void activateSASDMode( bool checked );
    void activateSABSSDMode( bool checked );
    void setVisualizer();
    void switchCatergoryOnSceneGraph( SceneGraphWidget::ActiveScene scene );
    void reset();
    void savePointCloud();
    void initializeFloor();
    void loadPointCloud();
    void removeRenderWindowFromRenderList();

private:
    Ui::MainWindow*         ui;
    // Explorer
    QDockWidget*            mp_explorerDockWidget;
    PropertyBrowser*        mp_explorer;
    // MovementAnalyzer
    QDockWidget*            mp_analyserDockWidget;
    PropertyBrowser*        mp_analyzerBrowser;
    // SizeAnalyzer
    QDockWidget*            mp_sizeAnalyzerDockWidget;
    PropertyBrowser*        mp_sizeAnalyzerBrowser;
    // Scenegraph
    QDockWidget*            mp_sceneDockWidget;
    SceneGraphWidget*       mp_sceneGraph;
    // Kinect
    KinectPtr               m_kinect;
    // Timer
    QTimer                  m_timer;
    QElapsedTimer           m_elpasedTimer;
    qint64                  m_lastTiming;
    // OpenGLRenderWidget
    OpenGLWindow*           mp_openGLWindow;
    QWidget*                mp_openGLRenderWidget;
    // RGBViewer
    OpenGLWindow*           mp_rgbViewerWindow;
    QWidget*                mp_rgbViewerWidget;
    // DepthViewer
    OpenGLWindow*           mp_depthViewerWindow;
    QWidget*                mp_depthViewerWidget;
    // Importent render objects
    RenderObject*           mp_rgbViewObject;
    RenderObject*           mp_depthViewObject;
    SkeletonRenderObject*   mp_skeletonRenderObject;
    QTime time;
    // Analysis
    HighLevelProcessingPipelinePtr m_highLvlProcessingPipeline;
    // Visualizer
    VisualizerPtr        m_visualizer;
    Floor*               mp_floor;
    bool                 m_floorInitialized;
    QList<OpenGLWindow*> m_renderWindows;
};

#endif // MAINWINDOW_H

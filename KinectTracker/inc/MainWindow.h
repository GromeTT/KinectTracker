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
#include "Kinect.h"
#include "BoundingGeometry.h"
#include "SkeletonAnalyzer.h"
#include "PropertyBrowser.h"
#include "HighLevelProcessingPipeline.h"
#include "Visualizer.h"
#include "SceneGraphWidget.h"

class OpenGLWidget;
class OpenGLWindow;
class QLabel;
class RGBWidget;
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
    void processSkeletonData( const unsigned int timestamp) ;
    void actionOpenGLRenderWidgetChecked( bool checked );

    void takeScreenshot();
    void setUpdateSkeltonData( const bool on );
    void setUpdateRGBData( const bool on );
    void setUpdateDepthData( const bool on );

    void activateSASDMode( bool checked );
    void activateSABSSDMode( bool checked );
    void setVisualizer();
    void switchCatergoryOnSceneGraph( SceneGraphWidget::ActiveScene scene );

signals:
    void updateSkeletonDataChanged();
    void updateRGBDataChanged();
    void updateDepthDataChanged();

private:
    Ui::MainWindow*         ui;
    // Explorer
    QDockWidget*            mp_explorerDockWidget;
    PropertyBrowser*        mp_explorer;
    // MovementAnalyzer
    QDockWidget*            mp_analyserDockWidget;
    PropertyBrowser*        mp_analyerBrowser;
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
    VisualizerPtr m_visualizer;

    bool m_updateSkeletonData;
    bool m_updateRGBData;
    bool m_updateDepthData;
};

void detect_blobs( cv::Mat& current );

#endif // MAINWINDOW_H

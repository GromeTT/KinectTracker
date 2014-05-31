#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Kinect.h"
#include "BoundingBox.h"
#include "SkeletonAnalyzer.h"
#include "AnalysisResults.h"
#include "ImageAnalyzer.h"

class OpenGLWidget;
class OpenGLWindow;
class QLabel;
class RGBWidget;
class RenderObject;
class QOpenGLTexture;
class Explorer;
class SceneGraphWidget;
class QKeyPressEvent;
class DepthViewerWidget;
class QMdiSubWindow;

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
    void processRGBData();
    void processDepthData();
    void processSkeletonData( const unsigned int timestamp) ;
    void actionOpenGLRenderWidgetChecked( bool checked );
    void actionBackgroundSubtractionToggled( );
    void takeSnapshot();
    void setUpdateSkeltonData( const bool on );
    void setUpdateRGBData( const bool on );
    void setUpdateDepthData( const bool on );
    void subWindowActivated( QMdiSubWindow* subWindow );

signals:
    void updateSkeletonDataChanged();
    void updateRGBDataChanged();
    void updateDepthDataChanged();

private:
    Ui::MainWindow*         ui;
    // Explorer
    QDockWidget*            mp_explorerDockWidget;
    Explorer*               mp_explorer;
    // ResultExplorer
    QDockWidget*            mp_resultExpDockWidget;
    Explorer*               mp_resultExp;
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
    RenderObject*           mp_skeletonObject;
    RenderObject*           mp_boundingBox;
    RenderObject*           mp_arrowObject;
    // OpenCV stuff
    cv::Ptr<cv::BackgroundSubtractor> m_backgroundSubtractor;
    cv::CascadeClassifier faceClassifier;
    // Modes
    bool m_backGroundSubtraction;
    QTime time;
    // RGB/Depth-data
    uchar* mp_rgbData;
    uchar* mp_depthData;
    // Analysis
    SkeletonAnalyzer m_skeletonAnalyzer;
    ImageAnalyzer    m_imageAnalyzer;
    AnalysisResults  m_analysisResults;
    //
    bool m_updateSkeletonData;
    bool m_updateRGBData;
    bool m_updateDepthData;
    //
    bool m_takeSnapshot;
};

void detect_blobs( cv::Mat& current );

#endif // MAINWINDOW_H

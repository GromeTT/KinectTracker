#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T23:16:27
#
#-------------------------------------------------

QT       += core gui
QT       += gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = KinectTracker\
TEMPLATE = app

SOURCES += Src\main.cpp\
           Src\MainWindow.cpp \
           Src\OpenGLWindow.cpp \
           Src\BasicUsageScene.cpp \
           Src\RenderObject.cpp \
           Src\Vertex.cpp \
           Src\RGBWidget.cpp \
           Src\Kinect.cpp \
           Src\Skeleton.cpp \
           Src\KinectInitializeDialog.cpp \
           Src/Floor.cpp \
           Src/Explorer.cpp \
           Src/SceneGraphWidget.cpp \
           Src/SignalBlocker.cpp \
           Src/DepthViewerWidget.cpp \
           Src/SkeletonAnalyzer.cpp \
           Src/BoundingBox.cpp \
           Src/Intersection.cpp \
           Src/ObjectLoader.cpp \
           Src/AnalysisResults.cpp \
           Src/Camera.cpp \
    Src/ImageAnalyzer.cpp \
    Src/Erode.cpp \
    Src/ProcessingPipeline.cpp \
    Src/Dilate.cpp \
    Src/Threshold.cpp

HEADERS  += Inc\MainWindow.h \
            Inc\OpenGLWindow.h \
            Inc\BasicUsageScene.h \
            Inc\RenderObject.h \
            Inc\Vertex.h \
            Inc\RGBWidget.h \
            Inc\Kinect.h \
            Inc\Skeleton.h \
            Inc\KinectInitializeDialog.h \
            Inc/Floor.h \
            Inc/Explorer.h \
            Inc/SceneGraphWidget.h \
            Inc/SignalBlocker.h \
            Inc/DepthViewerWidget.h \
            Inc/Macros.h \
            Inc/SkeletonAnalyzer.h \
            Inc/BoundingBox.h \
            Inc/Intersection.h \
            Inc/ObjectLoader.h \
            Inc/AnalysisResults.h \
            Inc/Camera.h \
    Inc/ImageAnalyzer.h \
    Inc/Erode.h \
    Inc/ProcessingPipeline.h \
    Inc/Dilate.h \
    Inc/Threshold.h

FORMS    += MainWindow.ui \
            KinectInitializeDialog.ui \
            Explorer.ui \
            SceneGraphWidget.ui \
            DepthViewerWidget.ui \
            RGBViewerWidget.ui


TRANSLATIONS = Translation/trans_de.ts


INCLUDEPATH += "../ThirdParty/Kinect/inc"
INCLUDEPATH += C:\\opencv\\build\\include


LIBS += "../ThirdParty/Kinect/lib/amd64/Kinect10.lib"
LIBS += -LC:\\opencv\\build\\x64\\vc11\\lib\
        -lopencv_calib3d249d \
        -lopencv_contrib249d \
        -lopencv_core249d\
        -lopencv_features2d249d \
        -lopencv_flann249d \
        -lopencv_gpu249d \
        -lopencv_imgproc249d \
        -lopencv_legacy249d \
        -lopencv_ml249d \
        -lopencv_objdetect249d \
        -lopencv_ts249d \
        -lopencv_video249d \
        -lopencv_highgui249d \

OTHER_FILES += \
    Shader/VertexShader.vert \
    Shader/FragmentShader.frag \
    Notes.txt

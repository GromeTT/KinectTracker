#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T23:16:27
#
#-------------------------------------------------

QT       += core gui
QT       += gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 5):

TARGET = KinectTracker\
TEMPLATE = app

SOURCES += src/main.cpp\
           src/MainWindow.cpp \
           src/OpenGLWindow.cpp \
           src/BasicUsageScene.cpp \
           src/RenderObject.cpp \
           src/Vertex.cpp \
           src/RGBWidget.cpp \
           src/Kinect.cpp \
           src/KinectInitializeDialog.cpp \
           src/Floor.cpp \
           src/SceneGraphWidget.cpp \
           src/SignalBlocker.cpp \
           src/DepthViewerWidget.cpp \
           src/SkeletonAnalyzer.cpp \
           src/Intersection.cpp \
           src/ObjectLoader.cpp \
           src/Camera.cpp \
           src/ImageAnalyzer.cpp \
           src/Erode.cpp \
           src/Dilate.cpp \
           src/Threshold.cpp \
           src/TransformationObject.cpp \
           src/SkeletonData.cpp \
           src/SkeletonRenderObject.cpp \
           src/RenderObjectInterface.cpp \
           src/HOGFeatureDetector.cpp \
           src/SkinColorDetector.cpp \
    src/InRange.cpp \
    src/ProcessingComponent.cpp \
    src/ArrayManipulator.cpp \
    src/FloatEditor.cpp \
    src/CustomStyledDelegate.cpp \
    src/QObjectTreeWidgetItem.cpp \
    src/FixedPropertyVector.cpp \
    src/TreeModel.cpp \
    src/PropertyBrowser.cpp \
    src/RGBAnalyzer.cpp \
    src/DepthProcessingPipeline.cpp \
    src/HighLevelProcessingPipeline.cpp \
    src/SASDProcessingPipeline.cpp \
    src/SABSSDProcessingPipeline.cpp \
    src/BoundingGeometry.cpp \
    src/MovementAnalyzer.cpp \
    src/BBMovementAnalyzer.cpp \
    src/AMath.cpp \
    src/LowLevelProcessingPipeline.cpp \
    src/Visualizer.cpp \
    src/BBMovementVisualizer.cpp \
    src/ConnectionHelper.cpp \
    src/TestObject.cpp \
    src/SizeAnalyzer.cpp \
    src/BBSizeAnalyzer.cpp \
    src/UpperBodySizeAnalyzer.cpp

HEADERS  += inc/MainWindow.h \
            inc/OpenGLWindow.h \
            inc/BasicUsageScene.h \
            inc/RenderObject.h \
            inc/Vertex.h \
            inc/RGBWidget.h \
            inc/Kinect.h \
            inc/KinectInitializeDialog.h \
            inc/Floor.h \
            inc/SceneGraphWidget.h \
            inc/SignalBlocker.h \
            inc/DepthViewerWidget.h \
            inc/Macros.h \
            inc/SkeletonAnalyzer.h \
            inc/Intersection.h \
            inc/ObjectLoader.h \
            inc/Camera.h \
            inc/ImageAnalyzer.h \
            inc/Erode.h \
            inc/Dilate.h \
            inc/Threshold.h \
            inc/TransformationObject.h \
            inc/SkeletonData.h \
            inc/SkeletonRenderObject.h \
            inc/RenderObjectInterface.h \
            inc/Defines.h \
            inc/HOGFeatureDetector.h \
            inc/SkinColorDetector.h \
    inc/InRange.h \
    inc/ProcessingComponent.h \
    inc/ArrayManipulator.h \
    inc/FloatEditor.h \
    inc/CustomStyledDelegate.h \
    inc/QObjectTreeWidgetItem.h \
    inc/FixedPropertyVector.h \
    inc/TreeModel.h \
    inc/PropertyBrowser.h \
    inc/RGBAnalyzer.h \
    inc/DepthProcessingPipeline.h \
    inc/HighLevelProcessingPipeline.h \
    inc/SASDProcessingPipeline.h \
    inc/SABSSDProcessingPipeline.h \
    inc/BoundingGeometry.h \
    inc/MovementAnalyzer.h \
    inc/BBMovementAnalyzer.h \
    inc/AMath.h \
    inc/LowLevelProcessingPipeline.h \
    inc/Visualizer.h \
    inc/BBMovementVisualizer.h \
    inc/ConnectionHelper.h \
    inc/TestObject.h \
    inc/SizeAnalyzer.h \
    inc/UpperBodySizeAnalyzer.h \
    inc/BBSizeAnalyzer.h

FORMS    += MainWindow.ui \
            KinectInitializeDialog.ui \
            Explorer.ui \
            SceneGraphWidget.ui \
            DepthViewerWidget.ui \
            RGBViewerWidget.ui \
    ArrayManipulator.ui \
    PropertyBrowser.ui


TRANSLATIONS = trans/trans_de.ts

OTHER_FILES += \
    shader/VertexShader.vert \
    shader/FragmentShader.frag \
    Notes.txt \
    config.qdocconf \
    doc/collection.qhcp \
    shader/SkeletonVertexShader.vert \
    shader/SkeletonFragmentShader.frag


INCLUDEPATH += "../ThirdParty/Kinect/inc"
INCLUDEPATH += C:\\opencv\\build\\include


LIBS += "../ThirdParty/Kinect/lib/amd64/Kinect10.lib"

CONFIG( debug, debug|release )
{
    LIBS += -LC:\\opencv\\build\\x64\\vc12\\lib\
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
            -lopencv_photo249d \
}

CONFIG( release, debug|release )
{
    LIBS += -LC:\\opencv\\build\\x64\\vc12\\lib\
            -lopencv_calib3d249 \
            -lopencv_contrib249 \
            -lopencv_core249\
            -lopencv_features2d249 \
            -lopencv_flann249 \
            -lopencv_gpu249 \
            -lopencv_imgproc249 \
            -lopencv_legacy249 \
            -lopencv_ml249 \
            -lopencv_objdetect249 \
            -lopencv_ts249 \
            -lopencv_video249 \
            -lopencv_highgui249 \
}

RESOURCES += \
    Resources.qrc



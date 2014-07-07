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

SOURCES += inc/AMath/src/AMath.cpp \
    inc/Analyzer/src/BBMovementAnalyzer.cpp \
    inc/Analyzer/src/BBSizeAnalyzer.cpp \
    inc/Analyzer/src/MovementAnalyzer.cpp \
    inc/Analyzer/src/SizeAnalyzer.cpp \
    inc/Analyzer/src/SkeletonAnalyzer.cpp \
    inc/Analyzer/src/UpperBodySizeAnalyzer.cpp \
    inc/Collision/src/Intersection.cpp \
    inc/Dialogs/src/KinectInitializeDialog.cpp \
    inc/Geometries/src/BoundingGeometry.cpp \
    inc/Kinect/src/Kinect.cpp \
    inc/Kinect/src/SkeletonData.cpp \
    inc/ProcessingPipelines/src/DepthProcessingPipeline.cpp \
    inc/ProcessingPipelines/src/Dilate.cpp \
    inc/ProcessingPipelines/src/Erode.cpp \
    inc/ProcessingPipelines/src/HighLevelProcessingPipeline.cpp \
    inc/ProcessingPipelines/src/HOGFeatureDetector.cpp \
    inc/ProcessingPipelines/src/InRange.cpp \
    inc/ProcessingPipelines/src/LowLevelProcessingPipeline.cpp \
    inc/ProcessingPipelines/src/ProcessingComponent.cpp \
    inc/ProcessingPipelines/src/SABSSDProcessingPipeline.cpp \
    inc/ProcessingPipelines/src/SASDProcessingPipeline.cpp \
    inc/ProcessingPipelines/src/Threshold.cpp \
    inc/PropertyBrowser/src/CustomStyledDelegate.cpp \
    inc/PropertyBrowser/src/FixedPropertyVector.cpp \
    inc/PropertyBrowser/src/FloatEditor.cpp \
    inc/PropertyBrowser/src/PropertyBrowser.cpp \
    inc/PropertyBrowser/src/TreeModel.cpp \
    inc/SceneGraph/src/QObjectTreeWidgetItem.cpp \
    inc/SceneGraph/src/SceneGraphWidget.cpp \
    inc/Visualizer/src/BBMovementVisualizer.cpp \
    inc/Visualizer/src/Visualizer.cpp \
    inc/QtHelper/src/ConnectionHelper.cpp \
    main.cpp \
    MainWindow.cpp \
    inc/OpenGL/src/BasicUsageScene.cpp \
    inc/OpenGL/src/Camera.cpp \
    inc/OpenGL/src/Floor.cpp \
    inc/OpenGL/src/ObjectLoader.cpp \
    inc/OpenGL/src/OpenGLWindow.cpp \
    inc/OpenGL/src/RenderObject.cpp \
    inc/OpenGL/src/RenderObjectInterface.cpp \
    inc/OpenGL/src/SkeletonRenderObject.cpp \
    inc/OpenGL/src/TransformationObject.cpp \
    inc/OpenGL/src/Vertex.cpp \
    inc/QtHelper/src/SignalBlocker.cpp \
    inc/ProcessingPipelines/src/SkinColorDetector.cpp \
    inc/Dialogs/src/ImageAnalysisDialog.cpp \
    inc/ImageWidget/src/ImageWidget.cpp \
    inc/ProcessingPipelines/src/Histogram.cpp

HEADERS  += inc/AMath/inc/AMath.h \
    inc/Analyzer/inc/BBMovementAnalyzer.h \
    inc/Analyzer/inc/BBSizeAnalyzer.h \
    inc/Analyzer/inc/MovementAnalyzer.h \
    inc/Analyzer/inc/SizeAnalyzer.h \
    inc/Analyzer/inc/SkeletonAnalyzer.h \
    inc/Analyzer/inc/UpperBodySizeAnalyzer.h \
    inc/Collision/inc/Intersection.h \
    inc/Dialogs/inc/KinectInitializeDialog.h \
    inc/Geometries/inc/BoundingGeometry.h \
    inc/Kinect/inc/Kinect.h \
    inc/Kinect/inc/SkeletonData.h \
    inc/ProcessingPipelines/inc/DepthProcessingPipeline.h \
    inc/ProcessingPipelines/inc/Dilate.h \
    inc/ProcessingPipelines/inc/Erode.h \
    inc/ProcessingPipelines/inc/HighLevelProcessingPipeline.h \
    inc/ProcessingPipelines/inc/HOGFeatureDetector.h \
    inc/ProcessingPipelines/inc/InRange.h \
    inc/ProcessingPipelines/inc/LowLevelProcessingPipeline.h \
    inc/ProcessingPipelines/inc/ProcessingComponent.h \
    inc/ProcessingPipelines/inc/SABSSDProcessingPipeline.h \
    inc/ProcessingPipelines/inc/SASDProcessingPipeline.h \
    inc/ProcessingPipelines/inc/Threshold.h \
    inc/PropertyBrowser/inc/CustomStyledDelegate.h \
    inc/PropertyBrowser/inc/FixedPropertyVector.h \
    inc/PropertyBrowser/inc/FloatEditor.h \
    inc/PropertyBrowser/inc/TreeModel.h \
    inc/SceneGraph/inc/QObjectTreeWidgetItem.h \
    inc/SceneGraph/inc/SceneGraphWidget.h \
    inc/Visualizer/inc/BBMovementVisualizer.h \
    inc/Visualizer/inc/Visualizer.h \
    inc/QtHelper/inc/ConnectionHelper.h \
    Defines.h \
    Macros.h \
    MainWindow.h \
    inc/OpenGL/inc/BasicUsageScene.h \
    inc/OpenGL/inc/Camera.h \
    inc/OpenGL/inc/Floor.h \
    inc/OpenGL/inc/ObjectLoader.h \
    inc/OpenGL/inc/OpenGLWindow.h \
    inc/OpenGL/inc/PropertyBrowser.h \
    inc/OpenGL/inc/RenderObject.h \
    inc/OpenGL/inc/RenderObjectInterface.h \
    inc/OpenGL/inc/SkeletonRenderObject.h \
    inc/OpenGL/inc/TransformationObject.h \
    inc/OpenGL/inc/Vertex.h \
    inc/QtHelper/inc/SignalBlocker.h \
    inc/ProcessingPipelines/inc/SkinColorDetector.h \
    inc/PropertyBrowser/inc/PropertyBrowser.h \
    inc/Dialogs/inc/ImageAnalysisDialog.h \\
    inc/ImageWidget/inc/ImageWidget.h \
    inc/ProcessingPipelines/inc/Histogram.h

FORMS    += MainWindow.ui \
    inc/Dialogs/ui/KinectInitializeDialog.ui \
    inc/Dialogs/ui/ImageAnalysisDialog.ui \
    inc/SceneGraph/ui/SceneGraphWidget.ui \
    inc/PropertyBrowser/ui/PropertyBrowser.ui \
    inc/ImageWidget/ui/ImageWidget.ui


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



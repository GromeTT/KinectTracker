#ifndef HIGHLEVELPROCESSINGPIPELINE_H
#define HIGHLEVELPROCESSINGPIPELINE_H

#include <QObject>
#include <vector>
#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <QList>
#include "DepthProcessingPipeline.h"
#include "LowLevelProcessingPipeline.h"
#include "../../Kinect/inc/Kinect.h"
#include "../../Analyzer/inc/MovementAnalyzer.h"
#include "../../Analyzer/inc/SizeAnalyzer.h"
#include "../../Analyzer/inc/SkeletonAnalyzer.h"
#include "../../AMath/inc/AMath.h"

class AnlysisResults;

class HighLevelProcessingPipeline : public QObject
{
public:
    HighLevelProcessingPipeline( KinectPtr& kinect,
                                 LowLevelProcessingPipeline* rbgProcessingPipeline,
                                 DepthProcessingPipeline* depthProcessingPipeline,
                                 QObject* parent = nullptr );
    virtual ~HighLevelProcessingPipeline();

    bool process( const unsigned int timestamp );
    void takeScreenShot();
    void saveHeadHistograms();
    void drawRegionOfInterest( QRect& rect,
                               cv::Mat image,
                               cv::Scalar color );
    void reset();
    QRect crop( const AMath::Rectangle3D& rect,
                cv::Mat& image );
    QRect cropRegionWithWidthAndHeightAsPixels( const QRect& rect,
                                                const cv::Mat& image );
    QRect cropRegionWithWidthAndHeightAsPixels( const QPoint& center,
                                                const float width,
                                                const float height,
                                                const cv::Mat& image );

    uchar*                                rgbImage() const;
    ushort*                               depthImage() const;
    SkeletonDataPtr                       skeletonData() const;
    QList<LowLevelProcessingPipelinePtr>& rgbProcessingPipelines();
    DepthProcessingPipelinePtr            depthProcessingPipeline() const;
    MovementAnalyzerPtr                   movementAnalyzer() const;
    SizeAnalyzerPtr                       sizeAnalyzer() const;
    SkeletonAnalyzerPtr                   skeletonAnalyzer() const;
    bool                                  skeletonDataAvailable() const;

protected:
    virtual void processV( const unsigned int timestamp ) = 0;
    virtual void resetV() = 0;
    void trackJoints(const SkeletonDataPtr skeleton , cv::Mat image);
    void drawJoint( SkeletonData::Joints joint,
                    const SkeletonDataPtr skeleton,
                    cv::Mat image,
                    const int width = 25,
                    const int height = 25 );

    KinectPtr                            m_kinect;
    SkeletonAnalyzerPtr                  m_skeletonAnalyzer;
    MovementAnalyzerPtr                  m_movementAnalyzer;
    SizeAnalyzerPtr                      m_sizeAnalyzer;
    DepthProcessingPipelinePtr           m_depthProcessingPipeline;
    QList<SkeletonDataPtr>               m_skeletons;
    QList<LowLevelProcessingPipelinePtr> m_rgbProcessingPipelines;
    ushort*                              mp_depthData;
    uchar*                               mp_rgbData;
    ushort*                              mp_depthScrennshot;
    uchar*                               mp_rgbScreenshot;
    int                                  m_depthSize;
    int                                  m_rgbSize;
    bool                                 m_skeletonDataAvailable;
};

typedef QSharedPointer<HighLevelProcessingPipeline> HighLevelProcessingPipelinePtr;

#endif // HIGHLEVELPROCESSINGPIPELINE_H

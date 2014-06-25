#ifndef HIGHLEVELPROCESSINGPIPELINE_H
#define HIGHLEVELPROCESSINGPIPELINE_H

#include <QObject>
#include <vector>
#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include "Kinect.h"
#include "LowLevelProcessingPipeline.h"
#include "DepthProcessingPipeline.h"
#include "MovementAnalyzer.h"
#include "SizeAnalyzer.h"
#include "SkeletonAnalyzer.h"

class AnlysisResults;

class HighLevelProcessingPipeline : public QObject
{
public:
    HighLevelProcessingPipeline( KinectPtr& kinect,
                                 LowLevelProcessingPipeline* rbgProcessingPipeline,
                                 DepthProcessingPipeline* depthProcessingPipeline,
                                 QObject* parent = nullptr );
    virtual ~HighLevelProcessingPipeline();

    void process( const unsigned int timestamp );
    void takeScreenShot();
    void drawRegionOfInterest();

    uchar*                          rgbImage() const;
    ushort*                         depthImage() const;
    SkeletonDataPtr                 skeletonData() const;
    LowLevelProcessingPipelinePtr   rgbProcessingPipeline() const;
    DepthProcessingPipelinePtr      depthProcessingPipeline() const;
    MovementAnalyzerPtr             movementAnalyzer() const;
    SizeAnalyzerPtr                 sizeAnalyzer() const;


protected:
    virtual void processV( const unsigned int timestamp ) = 0;

    SkeletonAnalyzerPtr           m_skeletonAnalyzer;
    MovementAnalyzerPtr           m_movementAnalyzer;
    SizeAnalyzerPtr               m_sizeAnalyzer;
    DepthProcessingPipelinePtr    m_depthProcessingPipeline;
    LowLevelProcessingPipelinePtr m_rgbProcessingPipeline;
    KinectPtr                     m_kinect;
    QList<SkeletonDataPtr>        m_skeletons;
    ushort*                       mp_depthData;
    uchar*                        mp_rgbData;
    ushort*                       mp_depthScrennshot;
    uchar*                        mp_rgbScreenshot;
    int                           m_depthSize;
    int                           m_rgbSize;
};

typedef QSharedPointer<HighLevelProcessingPipeline> HighLevelProcessingPipelinePtr;

#endif // HIGHLEVELPROCESSINGPIPELINE_H

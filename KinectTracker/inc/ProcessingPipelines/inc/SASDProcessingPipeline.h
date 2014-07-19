#ifndef SASDPROCESSINGPIPELINE_H
#define SASDPROCESSINGPIPELINE_H

#include "HighLevelProcessingPipeline.h"
#include "LowLevelProcessingPipeline.h"
#include <QVector4D>

class AnalysisResults;
class SkeletonAnalyzer;

class SASDProcessingPipeline : public HighLevelProcessingPipeline
{
public:
    SASDProcessingPipeline( KinectPtr& kinect, QObject* parent = nullptr );
    virtual ~SASDProcessingPipeline();

protected:
   void processV( const unsigned int timestamp );
   virtual void resetV();

private:
   bool processSkeletonData( const unsigned int timestamp );
   void processRGBData();
   void processDepthData();
   void deriveViewingDirectionBySkinColor( cv::Mat& head );
   void deriveViewingDirectionByHistogram( cv::Mat& headRegion );
   void deriveViewingDirectionByHistogramHSV( cv::Mat& headRegion );

   QRect                                                  m_lastRegion;
   QVector4D                                              m_planeCoefficient;
   SkinColorDetectionPipeline                             m_skinColorDetectionPipeline;
   SkinColorHistogramDetectionPipelinePtr                 m_skinColorHistogramDetectionPipeline;
   SkinColorExplicitDefinedSkinRegionDetectionPipelinePtr m_skinPipeline;
};

#endif // SASDPROCESSINGPIPELINE_H

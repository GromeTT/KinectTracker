#ifndef SASDPROCESSINGPIPELINE_H
#define SASDPROCESSINGPIPELINE_H

#include "HighLevelProcessingPipeline.h"
#include "LowLevelProcessingPipeline.h"

class AnalysisResults;
class SkeletonAnalyzer;

class SASDProcessingPipeline : public HighLevelProcessingPipeline
{
public:
    SASDProcessingPipeline( KinectPtr& kinect, QObject* parent = nullptr );
    virtual ~SASDProcessingPipeline();

protected:
   void processV( const unsigned int timestamp );

private:
   SkinColorExplicitDefinedSkinRegionDetectionPipelinePtr m_skinPipeline;

   bool processSkeletonData( const unsigned int timestamp );
   void processRGBData();
   void processDepthData();
};

#endif // SASDPROCESSINGPIPELINE_H

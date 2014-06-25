#ifndef SABSSDPROCESSINGPIPELINE_H
#define SABSSDPROCESSINGPIPELINE_H

#include "HighLevelProcessingPipeline.h"

class SABSSDProcessingPipeline : public HighLevelProcessingPipeline
{
public:
    SABSSDProcessingPipeline( KinectPtr& kinect,
                              QObject* parent = nullptr );
    virtual ~SABSSDProcessingPipeline();

private:
    virtual void processV( const unsigned int timestamp );
    bool processSkeletonData( const unsigned int timestamp );
    void processDepthData();
};

#endif // SABSSDPROCESSINGPIPELINE_H

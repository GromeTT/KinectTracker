#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "LowLevelProcessingPipeline.h"

class ProcessingComponent;

class ImageAnalyzer : public QObject
{
public:
    ImageAnalyzer( LowLevelProcessingPipeline* pipeline = nullptr,
                   QObject* parent = nullptr );
    virtual ~ImageAnalyzer();

    virtual void analyze( cv::Mat& input ) = 0;

    QObject*            getObjectByName( const QString& name );
    LowLevelProcessingPipeline* getProcessingPipeline() const;

protected:
    void setProcessingPipeline( LowLevelProcessingPipelinePtr& pipeline );

protected:
    LowLevelProcessingPipelinePtr mp_processingPipeline;
};

#endif // IMAGEANALYZER_H

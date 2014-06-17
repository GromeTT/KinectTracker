#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "ProcessingPipeline.h"

class ProcessingComponent;

class ImageAnalyzer : public QObject
{
public:
    ImageAnalyzer();
    virtual ~ImageAnalyzer();

    void analyze( cv::Mat& input );
    void setSnapshot( cv::Mat& snapshot );

    const QVector<ProcessingComponent*>& getPiplineComponents() const;
    QObject*                             getObjectByName( const QString& name );
    ProcessingPipeline*                  getProcessingPipeline() const;

private:
    ProcessingPipelinePtr mp_processingPipeline;
    cv::Mat               m_snapshot;
};

#endif // IMAGEANALYZER_H

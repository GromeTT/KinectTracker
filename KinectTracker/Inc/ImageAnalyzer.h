#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "ProcessingPipeline.h"


class ImageAnalyzer : public QObject
{
public:
    ImageAnalyzer();
    virtual ~ImageAnalyzer();

    void analyze( cv::Mat& input );
    void setSnapshot( cv::Mat& snapshot );

    const QVector<QObject*>& getPiplineComponents() const;
    QObject*                 getObjectByName( const QString& name );

private:
    ProcessingPipelinePtr mp_processingPipeline;
    cv::Mat               m_snapshot;
};

#endif // IMAGEANALYZER_H

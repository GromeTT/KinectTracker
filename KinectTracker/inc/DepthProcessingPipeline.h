#ifndef DEPTHPROCESSINGPIPELINE_H
#define DEPTHPROCESSINGPIPELINE_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <opencv2/opencv.hpp>
#include <opencv2/photo/photo.hpp>
#include <vector>

class ProcessingComponent;

class DepthProcessingPipeline : public QObject
{
    Q_OBJECT

public:
    DepthProcessingPipeline( QObject* parent = nullptr );
    ~DepthProcessingPipeline();

    void process( ushort* depthImage,
                  ushort* screenshot,
                  const float size );
    void setThreshold( const int threshold );

    QVector<ProcessingComponent*>& getComponents();
    int threshold() const;

private:
    QVector<ProcessingComponent*> m_processingComponents;
    int                           m_threshold;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

signals:
    void thresholdChanged();

private:
    Q_PROPERTY( int threshold
                READ threshold
                WRITE setThreshold
                NOTIFY thresholdChanged )
};

typedef QSharedPointer<DepthProcessingPipeline> DepthProcessingPipelinePtr;

#endif // DEPTHPROCESSINGPIPELINE_H

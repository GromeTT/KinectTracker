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
    void setMinContourSize( const int size );

    QVector<ProcessingComponent*>& getComponents();
    int threshold() const;
    int minContourSize() const;

private:
    QVector<ProcessingComponent*> m_processingComponents;
    int                           m_threshold;
    int                           m_minContourSize;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

signals:
    void thresholdChanged();
    void minContourSizeChanged();

private:
    Q_PROPERTY( int threshold
                READ threshold
                WRITE setThreshold
                NOTIFY thresholdChanged )

    Q_PROPERTY( int minContourSize MEMBER m_minContourSize
                READ minContourSize
                WRITE setMinContourSize
                NOTIFY minContourSizeChanged )
};

typedef QSharedPointer<DepthProcessingPipeline> DepthProcessingPipelinePtr;

#endif // DEPTHPROCESSINGPIPELINE_H

#ifndef PROCESSINGPIPELINE_H
#define PROCESSINGPIPELINE_H

#include <opencv2/opencv.hpp>
#include <QVector>
#include "Erode.h"
#include "Dilate.h"
#include "Threshold.h"

class ImageAnalyzer;

class QObject;

class ProcessingPipeline
{
public:
    ProcessingPipeline( ImageAnalyzer* parent );
    virtual ~ProcessingPipeline();

    virtual void process( cv::Mat& input ) = 0;
    void setSnapshot( cv::Mat* snapshot );

    const QVector<QObject*>& getComponents() const;
    QObject*                 getObjectByName( const QString& name );

protected:
    QVector<QObject*> m_processingComponents;
    cv::Mat*          mp_snapshot;
    ImageAnalyzer*    m_parent;
};


/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


class BackgroudSubtractionPipeline : public ProcessingPipeline
{
public:
    BackgroudSubtractionPipeline( ImageAnalyzer* parent );
    virtual ~BackgroudSubtractionPipeline();

    virtual void process( cv::Mat& input );
private:
    cv::BackgroundSubtractorMOG m_backgroundSubtractor;
    ErodePtr                    mp_erode;
};

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class BSPipeline : public ProcessingPipeline
{
public:
    BSPipeline( ImageAnalyzer* parent );
    virtual ~BSPipeline();

    virtual void process( cv::Mat& input );

private:
    ErodePtr     mp_erode;
    DilatePtr    mp_dilate;
    ThresholdPtr mp_threshold;

};

typedef QSharedPointer<ProcessingPipeline> ProcessingPipelinePtr;

#endif // PROCESSINGPIPELINE_H

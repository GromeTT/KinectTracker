#ifndef PROCESSINGPIPELINE_H
#define PROCESSINGPIPELINE_H

#include <opencv2/opencv.hpp>
#include <QVector>
#include <QMap>
#include <QObject>
#include "Erode.h"
#include "Dilate.h"
#include "Threshold.h"
#include "HOGFeatureDetector.h"
#include "SkinColorDetector.h"
#include "InRange.h"


class ImageAnalyzer;
class QObject;

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class LowLevelProcessingPipeline : public QObject
{
    Q_OBJECT

public:
    LowLevelProcessingPipeline( QObject* parent = nullptr );
    virtual ~LowLevelProcessingPipeline();

    virtual void process( cv::Mat& input ) = 0;
    void setScreenshot( cv::Mat* screenshot );

    const QVector<ProcessingComponent*>& getComponents() const;
    QObject*                             getObjectByName( const QString& name );

protected:
    void registerComponent( ProcessingComponent* component,
                            const bool recursive );

    cv::Mat*                        mp_screenshot;
    QVector<ProcessingComponent*>   m_processingComponents;
    QMap<int, ProcessingComponent*> m_allComponents;
    int                             m_instanceCounter;
};


/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


class BackgroudSubtractionPipeline : public LowLevelProcessingPipeline
{
public:
    BackgroudSubtractionPipeline( QObject* parent );
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

class BSPipeline : public LowLevelProcessingPipeline
{
public:
    BSPipeline( QObject* parent );
    virtual ~BSPipeline();

    virtual void process( cv::Mat& input );

private:
    ErodePtr     mp_erode;
    DilatePtr    mp_dilate;
    ThresholdPtr mp_threshold;

};

/**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************/


class HOGDetectionPipeline : public LowLevelProcessingPipeline
{
public:
    HOGDetectionPipeline( QObject* parent );
    virtual ~HOGDetectionPipeline();

    virtual void process( cv::Mat& input );

private:
    HogFeatureDetectorPtr   mp_HOGFeatureDetector;
    std::vector<cv::Point>  m_foundLocations;
    std::vector<cv::Rect>   m_rectangles;

};

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


class SkinColorDetectionPipeline : public LowLevelProcessingPipeline
{
public:
    SkinColorDetectionPipeline( QObject* parent = nullptr );
    virtual ~SkinColorDetectionPipeline();

    virtual void process( cv::Mat& input );

private:
    SkinColorDetectorPtr mp_skinColorDetector;
    InRangePtr           mp_inRange;
};

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class SkinColorExplicitDefinedSkinRegionDetectionPipeline : public LowLevelProcessingPipeline
{
public:
    SkinColorExplicitDefinedSkinRegionDetectionPipeline( QObject* parent = nullptr);
    virtual ~SkinColorExplicitDefinedSkinRegionDetectionPipeline();

    virtual void process( cv::Mat& input );
    int    absoluteFrequency();
private:
    int   m_absoluteFrequency;
};

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

typedef QSharedPointer<LowLevelProcessingPipeline> LowLevelProcessingPipelinePtr;
typedef QSharedPointer<SkinColorExplicitDefinedSkinRegionDetectionPipeline> SkinColorExplicitDefinedSkinRegionDetectionPipelinePtr;

#endif // PROCESSINGPIPELINE_H

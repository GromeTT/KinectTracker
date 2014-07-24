#ifndef SASDPROCESSINGPIPELINE_H
#define SASDPROCESSINGPIPELINE_H

#include "HighLevelProcessingPipeline.h"
#include "LowLevelProcessingPipeline.h"
#include <QVector4D>
#include <QColor>

class AnalysisResults;
class SkeletonAnalyzer;
class SASDProcessingPipeline;

typedef bool (SASDProcessingPipeline::*Func)( cv::Mat& region );

struct JointSummary
{
    JointSummary() {}
    JointSummary( cv::Mat& subMatrix,
                  const QRect& cropedRegion,
                  const SkeletonData::Joints joint,
                  const QColor& color )
        : m_subMatrix( subMatrix )
        , m_cropedRegion( cropedRegion )
        , m_joint( joint )
        , m_color( color )
    {
    }

    cv::Mat              m_subMatrix;
    QRect                m_cropedRegion;
    SkeletonData::Joints m_joint;
    QColor               m_color;
};

/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class SASDProcessingPipeline : public HighLevelProcessingPipeline
{
    Q_OBJECT

public:
    SASDProcessingPipeline( KinectPtr& kinect, QObject* parent = nullptr );
    virtual ~SASDProcessingPipeline();

    void setUseHaarClassifier( const bool arg );
    void setSkinColorFixedRegionThreshold( const int threshold );
    void setHistogramThreshold( const int threshold );
    void setHistogramHSVThreshold( const int threshold );

    bool useHaarClassifier() const;
    int  skinColorFixedRegionThreshold() const;
    int  histogramThreshold() const;
    int  histogramHSVThreshold() const;

protected:
   void processV( const unsigned int timestamp );
   virtual void resetV();

signals:
   void useHaarClassifierChanged();
   void skinColorFixedRegionThresholdChanged();
   void histogramThresholdChanged();
   void histogramHSVThresholdChanged();

private:
   bool processSkeletonData( const unsigned int timestamp );
   void processRGBData();
   void processDepthData();
   void extractAllRegions( cv::Mat& image );
   void extractRegion( cv::Mat& image, SkeletonData::Joints joint );
   bool deriveViewingDirection();
   bool deriveViewingDirectionBySkinColorFixedRegion( cv::Mat& region );
   bool deriveViewingDirectionByHistogram( cv::Mat& region );
   bool deriveViewingDirectionByHistogramHSV( cv::Mat& region );
   void drawRegionsOfInterest( cv::Mat& image );
   bool useHaarClassifier( cv::Mat& currentImage );
   bool analyseLastRegion(cv::Mat& image, QVector3D& head );

   QRect                                                  m_lastRegion;
   QVector4D                                              m_planeCoefficient;
   SkinColorHistogramDetectionPipelinePtr                 m_skinColorHistogramDetectionPipeline;
   SkinColorExplicitDefinedSkinRegionDetectionPipelinePtr m_skinPipeline;
   QVector<JointSummary>                                  m_regions;
   Func                                                   mp_deriveViewingDirectionFunc;
   cv::CascadeClassifier                                  m_hairFaceClassifier;
   std::vector<cv::Rect>                                  faces;
   SkeletonDataPtr                                        m_lastSkeleton;
   bool                                                   m_useHaarClassifier;
   int                                                    m_currentThreshold;
   int                                                    m_skinColorFixedRegionThreshold;
   int                                                    m_histogramThreshold;
   int                                                    m_histogramHSVThreshold;

private:
   Q_PROPERTY( bool useHaarClassifier MEMBER m_useHaarClassifier
               READ useHaarClassifier
               WRITE setUseHaarClassifier
               NOTIFY useHaarClassifierChanged )

   Q_PROPERTY( int skinColorFixedRegionThreshold MEMBER m_skinColorFixedRegionThreshold
               READ skinColorFixedRegionThreshold
               WRITE setSkinColorFixedRegionThreshold
               NOTIFY skinColorFixedRegionThresholdChanged )
};

#endif // SASDPROCESSINGPIPELINE_H

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

class SASDProcessingPipeline : public HighLevelProcessingPipeline
{
public:
    SASDProcessingPipeline( KinectPtr& kinect, QObject* parent = nullptr );
    virtual ~SASDProcessingPipeline();

protected:
   void processV( const unsigned int timestamp );
   virtual void resetV();

private:
   bool processSkeletonData( const unsigned int timestamp );
   void processRGBData();
   void processDepthData();
   void extractAllRegions( cv::Mat& image );
   void extractRegion( cv::Mat& image, SkeletonData::Joints joint );
   void deriveViewingDirection();
   bool deriveViewingDirectionBySkinColor( cv::Mat& head );
   bool deriveViewingDirectionByHistogram( cv::Mat& headRegion );
   bool deriveViewingDirectionByHistogramHSV( cv::Mat& headRegion );
   void drawRegionsOfInterest( cv::Mat& image );
   void useHairClassifier( cv::Mat& currentImage );

   QRect                                                  m_lastRegion;
   QVector4D                                              m_planeCoefficient;
   SkinColorDetectionPipeline                             m_skinColorDetectionPipeline;
   SkinColorHistogramDetectionPipelinePtr                 m_skinColorHistogramDetectionPipeline;
   SkinColorExplicitDefinedSkinRegionDetectionPipelinePtr m_skinPipeline;
   QVector<JointSummary>                                  m_regions;
   Func                                                   mp_deriveViewingDirectionFunc;
   cv::CascadeClassifier                                  m_hairFaceClassifier;
   std::vector<cv::Rect>                                  faces;
};

#endif // SASDPROCESSINGPIPELINE_H

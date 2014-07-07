#ifndef BBSIZEANALYZER_H
#define BBSIZEANALYZER_H

#include "SizeAnalyzer.h"
#include "../../Geometries/inc/BoundingGeometry.h"

class BBSizeAnalyzer : public SizeAnalyzer
{
public:
    BBSizeAnalyzer( QObject* parent = nullptr );
    virtual ~BBSizeAnalyzer();

    BoundingBoxPtr boundigBox() const;

private:
    virtual void analyzeV( const SkeletonDataPtr& skeletonData );
    virtual void resetV();

    void estimatedBodySize( const SkeletonDataPtr& skeletonDat );


    BoundingBoxPtr m_boundingBox;
};

#endif // BBSIZEANALYZER_H

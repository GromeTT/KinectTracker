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
    void analyzeV( const SkeletonDataPtr& skeletonData );
    void estimatedBodySize( const SkeletonDataPtr& skeletonDat );

    BoundingBoxPtr m_boundingBox;
};

#endif // BBSIZEANALYZER_H

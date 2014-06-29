#ifndef UPPERBODYSIZEANALYZER_H
#define UPPERBODYSIZEANALYZER_H

#include "SizeAnalyzer.h"

class UpperBodySizeAnalyzer : public SizeAnalyzer
{
    Q_OBJECT

public:
    UpperBodySizeAnalyzer();
    virtual ~UpperBodySizeAnalyzer();

    void setBodyPropotionFactor( const float factor );
    float bodyPropotionFactor() const;

private:
    void analyzeV( const SkeletonDataPtr& skeletonData );
    void estimateBodySize( const SkeletonDataPtr& skeletonData );

    float m_bodyPropotionFactor;

signals:
    void bodyPropotionFactorChanged();

private:
    Q_PROPERTY( float bodyPropotionFactor MEMBER m_bodyPropotionFactor
                READ bodyPropotionFactor
                WRITE setBodyPropotionFactor
                NOTIFY bodyPropotionFactorChanged )
};

#endif // UPPERBODYSIZEANALYZER_H


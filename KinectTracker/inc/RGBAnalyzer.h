#ifndef RGBANALYZER_H
#define RGBANALYZER_H

#include "ImageAnalyzer.h"

class RGBAnalyzer : public ImageAnalyzer
{
public:
    RGBAnalyzer( QObject* parent );
    virtual ~RGBAnalyzer();

    void analyze( cv::Mat& input );
};

#endif // RGBANALYZER_H

#ifndef VIEWINGDIRECTIONANALYZER_H
#define VIEWINGDIRECTIONANALYZER_H

#include <opencv2/opencv.hpp>

class ViewingDirectionHistogramAnalyzer
{
public:
    ViewingDirectionHistogramAnalyzer();
    ~ViewingDirectionHistogramAnalyzer();

    void update( cv::Mat image );
    void saveCurrentHistogram();
    float compare();

private:
    cv::Mat m_rHistogram;
    cv::Mat m_gHistogram;
    cv::Mat m_bHistogram;
    cv::Mat m_currentRHistogram;
    cv::Mat m_currentGHistogram;
    cv::Mat m_currentBHistograms;
};

#endif // VIEWINGDIRECTIONANALYZER_H

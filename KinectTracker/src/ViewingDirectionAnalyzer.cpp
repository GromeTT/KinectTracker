#include "../inc/ViewingDirectionAnalyzer.h"

using namespace std;
using namespace cv;


/*!
   \brief ViewingDirectionHistogramAnalyzer::ViewingDirectionHistogramAnalyzer
   Constructs the analyzer.
 */
ViewingDirectionHistogramAnalyzer::ViewingDirectionHistogramAnalyzer()
{

}

/*!
   \brief ViewingDirectionHistogramAnalyzer::~ViewingDirectionHistogramAnalyzer
   Destroyes the object.
 */
ViewingDirectionHistogramAnalyzer::~ViewingDirectionHistogramAnalyzer()
{

}


void ViewingDirectionHistogramAnalyzer::update( cv::Mat image )
{
    std::vector<Mat> bgr_planes;
    split( image, bgr_planes );

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, true, false );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, true, false );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, true, false );

    /// Normalize the result to [ 0, histImage.rows ]
    normalize( b_hist, b_hist, 0, head.rows, NORM_MINMAX, -1, Mat() );
    normalize( g_hist, g_hist, 0, head.rows, NORM_MINMAX, -1, Mat() );
    normalize( r_hist, r_hist, 0, head.rows, NORM_MINMAX, -1, Mat() );
}

/*!
   \brief ViewingDirectionHistogramAnalyzer::compare
   Compares the currentHistograms with the saved one and returns a scalar wich
   discribes their likeness.
   \see docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_comparison/histogram_comparison.html
 */
float ViewingDirectionHistogramAnalyzer::compare()
{

}

/*!
   \brief ViewingDirectionHistogramAnalyzer::saveCurrentHistogram
   Saves the current histograms.
 */
void ViewingDirectionHistogramAnalyzer::saveCurrentHistograms()
{
    m_rHistogram = m_currentRHistogram;
    m_gHistogram = m_currentGHistogram;
    m_bHistogram = m_currentBHistogram;
}

#include "../inc/SkinColorDetector.h"


SkinColorDetector::SkinColorDetector()
//    : mp_inRange( new InRange() )
{
    setObjectName( "SkinColorDetector" );
    setBins( 25 );

    cv::Mat src = cv::imread( "../KinectTracker/res/SkinColor/color.jpg", 1 );

}

SkinColorDetector::~SkinColorDetector()
{

}

void SkinColorDetector::detect( cv::Mat& img )
{
    // http://docs.opencv.org/doc/tutorials/imgproc/histograms/back_projection/back_projection.html?highlight=skin
    cv::Mat hsv;
    cv::cvtColor( img, hsv, CV_BGR2HSV );

    // Just use the hue value.
    m_hue.create( hsv.size(), hsv.depth() );
    int ch [] = { 0, 0 };
    cv::mixChannels( &hsv, 1, &m_hue, 1, ch, 1 );

    cv::MatND hist;
    int histSize = MAX( m_bins, 2 );
    float hueRange [] = { 0, 180 };
    const float* ranges = { hueRange };

    cv::calcHist( &m_hue, 1, 0, cv::Mat(), hist, 1, &histSize, &ranges, true, false );
    cv::normalize( hist, hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat() );

    cv::MatND backProjection;
    cv::calcBackProject( &m_hue, 1, 0, hist, backProjection, &ranges, 1, true );
    cv::imshow( "BackProj", backProjection );

    /// Draw the histogram
    int w = 400; int h = 400;
    int bin_w = cvRound( (double) w / histSize );
    cv::Mat histImg = cv::Mat::zeros( w, h, CV_8UC3 );

    for( int i = 0; i < m_bins; i ++ )
       { rectangle( histImg, cv::Point( i*bin_w, h ), cv::Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), cv::Scalar( 0, 0, 255 ), -1 ); }

    imshow( "Histogram", histImg );
}


void SkinColorDetector::setBins( const int bins )
{
    if ( m_bins != bins )
    {
        m_bins = bins;
        emit binsChanged();
    }
}


int SkinColorDetector::bins() const
{
    return m_bins;
}

#include "../inc/HOGFeatureDetector.h"
#include "../inc/Dilate.h"
#include <vector>


HOGFeatureDetector::HOGFeatureDetector( QObject* parent )
    : ProcessingComponent( parent )
{
    setObjectName( "HOGFeatureDetector" );
    Dilate* dilate = new Dilate( this );
    addComponent( dilate );
}

HOGFeatureDetector::~HOGFeatureDetector()
{

}

cv::Size HOGFeatureDetector::winSize() const
{
    return m_descriptor.winSize;
}

cv::Size HOGFeatureDetector::blockSize() const
{
    return m_descriptor.blockSize;
}

cv::Size HOGFeatureDetector::blockStride() const
{
    return m_descriptor.blockStride;
}

cv::Size HOGFeatureDetector::cellSize() const
{
    return m_descriptor.cellSize;
}

int HOGFeatureDetector::numberOfBins() const
{
    return m_descriptor.nbins;
}

double HOGFeatureDetector::winSigma() const
{
    return m_descriptor.winSigma;
}

double HOGFeatureDetector::thresholdL2Hys() const
{
    return m_descriptor.L2HysThreshold;
}

bool HOGFeatureDetector::gammaCorrection() const
{
    return m_descriptor.gammaCorrection;
}

int HOGFeatureDetector::numberOfLevels() const
{
    return m_descriptor.nlevels;
}

void HOGFeatureDetector::detect( const cv::Mat& img,
                                 std::vector<cv::Point>& foundLocations,
                                 double hitThreshold,
                                 cv::Size winStride,
                                 cv::Size padding ,
                                 const std::vector<cv::Point>& searchLocations ) const
{
    m_descriptor.detect( img,
                         foundLocations,
                         hitThreshold,
                         winStride,
                         padding,
                         searchLocations );
}

void HOGFeatureDetector::detect( const cv::Mat& img,
                                 std::vector<cv::Point>& foundLocations,
                                 std::vector<double>& weights,
                                 double hitThreshold,
                                 cv::Size winStride,
                                 cv::Size padding,
                                 const std::vector<cv::Point>& searchLocations) const
{
    m_descriptor.detect( img,
                         foundLocations,
                         weights,
                         hitThreshold,
                         winStride,
                         padding,
                         searchLocations );
}

void HOGFeatureDetector::detectMultiScale( const cv::Mat& img,
                                           std::vector<cv::Rect>& foundLocations,
                                           double hitThreshold,
                                           cv::Size winStride,
                                           cv::Size padding,
                                           double scale )
{
    m_descriptor.detectMultiScale( img,
                                   foundLocations,
                                   hitThreshold,
                                   winStride,
                                   padding,
                                   scale );
}

void HOGFeatureDetector::useDefaultPeopleDetector()
{
    m_descriptor.setSVMDetector( m_descriptor.getDefaultPeopleDetector() );
}

void HOGFeatureDetector::setSVMDetector( const std::vector<float>& detector )
{
    m_descriptor.setSVMDetector( detector );
}

void HOGFeatureDetector::setWinSize( const cv::Size& winSize )
{
    if ( m_descriptor.winSize != winSize )
    {
        m_descriptor.winSize = winSize;
        emit winSizeChanged();
    }
}

void HOGFeatureDetector::setBlockSize( const cv::Size& blockSize )
{
    if ( m_descriptor.blockSize != blockSize )
    {
        m_descriptor.blockSize = blockSize;
        emit blockSizeChanged();
    }
}

void HOGFeatureDetector::setBlockStride( const cv::Size& blockStride )
{
    if ( m_descriptor.blockStride != blockStride )
    {
        m_descriptor.blockStride = blockStride;
        emit blockStrideChanged();
    }
}

void HOGFeatureDetector::setCellSize( const cv::Size& cellSize )
{
    if ( m_descriptor.cellSize != cellSize )
    {
        m_descriptor.cellSize = cellSize;
        emit cellSizeChanged();
    }
}

void HOGFeatureDetector::setNumberOfBins( const int numberOfBins )
{
    if ( m_descriptor.nbins != numberOfBins )
    {
        m_descriptor.nbins = numberOfBins;
        emit numberOfBinsChanged();
    }
}

void HOGFeatureDetector::setWinSigma( const double winSigma )
{
    if ( m_descriptor.winSigma!= winSigma )
    {
        m_descriptor.winSigma = winSigma;
        emit winSigmaChanged();
    }
}

void HOGFeatureDetector::setThresholdL2Hys( const double threshold )
{
    if ( m_descriptor.L2HysThreshold != threshold )
    {
        m_descriptor.L2HysThreshold = threshold;
        emit thresholdL2HysChanged();
    }
}

void HOGFeatureDetector::setGammaCorrection( const bool gammaCorrection )
{
    if ( m_descriptor.gammaCorrection != gammaCorrection )
    {
        m_descriptor.gammaCorrection = gammaCorrection;
        emit gammaCorrectionChanged();
    }
}

void HOGFeatureDetector::setNumberOfLevels( const int numberOfLevels )
{
    if ( m_descriptor.nlevels != numberOfLevels )
    {
        m_descriptor.nlevels = numberOfLevels;
        emit numberOfLevelsChanged();
    }
}




#ifndef HOGFEATUREDETECTOR_H
#define HOGFEATUREDETECTOR_H

#include <opencv2/opencv.hpp>
#include "ProcessingComponent.h"
#include <QSharedPointer>

Q_DECLARE_METATYPE( cv::Size )

class vector;

class HOGFeatureDetector : public ProcessingComponent
{
    Q_OBJECT

public:
    HOGFeatureDetector( QObject* parent = nullptr );
    ~HOGFeatureDetector();

    cv::Size    winSize() const;
    cv::Size    blockSize() const;
    cv::Size    blockStride() const;
    cv::Size    cellSize() const;
    int         numberOfBins() const;
    double      winSigma() const;
    double      thresholdL2Hys() const;
    bool        gammaCorrection() const;
    int         numberOfLevels() const;

    void detect( const cv::Mat& img,
                 CV_OUT std::vector<cv::Point>& foundLocations,
                 double hitThreshold = 0,
                 cv::Size winStride = cv::Size(),
                 cv::Size padding = cv::Size(),
                 const std::vector<cv::Point>& searchLocations = std::vector<cv::Point>() ) const;
    void detect( const cv::Mat& img,
                 std::vector<cv::Point>& foundLocations,
                 std::vector<double>& weights,
                 double hitThreshold = 0,
                 cv::Size winStride = cv::Size(),
                 cv::Size padding = cv::Size(),
                 const std::vector<cv::Point>& searchLocations = std::vector<cv::Point>() ) const;
    void detectMultiScale( const cv::Mat& img,
                           std::vector<cv::Rect>& foundLocations,
                           double hitThreshold = 0,
                           cv::Size winStride = cv::Size(),
                           cv::Size padding = cv::Size(),
                           double scale = 1.05 );
    void useDefaultPeopleDetector();
    void setSVMDetector( const std::vector<float>& detector );
    void setWinSize( const cv::Size& winSize );
    void setBlockSize( const cv::Size& blockSize );
    void setBlockStride( const cv::Size& blockStride );
    void setCellSize( const cv::Size& cellSize );
    void setNumberOfBins( const int numberOfBins );
    void setWinSigma( const double winSigma );
    void setThresholdL2Hys( const double threshold );
    void setGammaCorrection( const bool gammaCorrection );
    void setNumberOfLevels( const int numberOfLevels );

private:
    cv::HOGDescriptor m_descriptor;

signals:
    void winSizeChanged();
    void blockSizeChanged();
    void blockStrideChanged();
    void cellSizeChanged();
    void numberOfBinsChanged();
    void winSigmaChanged();
    void thresholdL2HysChanged();
    void gammaCorrectionChanged();
    void numberOfLevelsChanged();

private:
    Q_PROPERTY( cv::Size winSize
                READ winSize )

    Q_PROPERTY( cv::Size blockSize
                READ blockSize
                WRITE setBlockSize
                NOTIFY blockSizeChanged )

    Q_PROPERTY( cv::Size blockStride
                READ blockStride
                WRITE setBlockStride
                NOTIFY blockStrideChanged )

    Q_PROPERTY( cv::Size cellSize
                READ cellSize
                WRITE setCellSize
                NOTIFY cellSizeChanged )

    Q_PROPERTY( int numberOfBins
                READ numberOfBins
                WRITE setNumberOfBins
                NOTIFY numberOfBinsChanged )

    Q_PROPERTY( double winSigma
                READ winSigma
                WRITE setWinSigma
                NOTIFY winSigmaChanged )

    Q_PROPERTY( double thresholdL2Hys
                READ thresholdL2Hys
                WRITE setThresholdL2Hys
                NOTIFY thresholdL2HysChanged )

    Q_PROPERTY( bool gammaCorrection
                READ gammaCorrection
                WRITE setGammaCorrection
                NOTIFY gammaCorrectionChanged )

    Q_PROPERTY( int numberOfLevels
                READ numberOfLevels
                WRITE setNumberOfLevels
                NOTIFY numberOfLevelsChanged )
};

typedef QSharedPointer<HOGFeatureDetector> HogFeatureDetectorPtr;

#endif // HOGFEATUREDETECTOR_H

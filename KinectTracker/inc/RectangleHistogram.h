#ifndef RECTANGLEHISTOGRAM_H
#define RECTANGLEHISTOGRAM_H

#include "opencv2/opencv.hpp"

class RectangleHistogram
{
public:
    RectangleHistogram();
    RectangleHistogram( const int x,
                        const int y,
                        const int width,
                        const int height );
    ~RectangleHistogram();

    int x() const;
    int y() const;
    int width() const;
    int height() const;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_histSize;
    cv::Mat m_rChannel;
    cv::Mat m_gChannel;
    cv::Mat m_bChannel;

};

#endif // RECTANGLEHISTOGRAM_H

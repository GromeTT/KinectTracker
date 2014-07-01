#ifndef IMAGEANALYSISDIALOG_H
#define IMAGEANALYSISDIALOG_H

#include <QDialog>
#include <QDir>
#include <opencv2/opencv.hpp>

namespace Ui
{
    class ImageAnalysisDialog;
}

class ImageAnalysisDialog : public QDialog
{
public:
    ImageAnalysisDialog( QWidget* parent = nullptr );
    ~ImageAnalysisDialog();

private:
    void loadImage();
    void loadROI();
    void computeHistogram();

    Ui::ImageAnalysisDialog* ui;
    QDir                     m_lastDirectory;
    cv::Mat                  m_image;
    cv::Mat                  m_imageBGR;
    cv::Mat                  m_roi;

};

#endif // IMAGEANALYSISDIALOG_H

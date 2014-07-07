#ifndef IMAGEANALYSISDIALOG_H
#define IMAGEANALYSISDIALOG_H

#include "../../ProcessingPipelines/inc/LowLevelProcessingPipeline.h"
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
    void saveROI();
    void computeBackprojection();
    void showSkinColor();
    QString loadImageFromLastDirectory();

    Ui::ImageAnalysisDialog*                            ui;
    QDir                                                m_lastDirectory;
    cv::Mat                                             m_imageBGR;
    cv::Mat                                             m_imageRGB;
    cv::Mat                                             m_skinColorImage;
    SkinColorHistogramDetectionPipeline                 m_skinColorDetectionPipeline;
    SkinColorExplicitDefinedSkinRegionDetectionPipeline m_skiColorDefinedRegions;

};

#endif // IMAGEANALYSISDIALOG_H

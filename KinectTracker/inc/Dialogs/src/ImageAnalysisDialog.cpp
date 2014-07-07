#include "../inc/ImageAnalysisDialog.h"
#include "../../ImageWidget/inc/ImageWidget.h"
#include "ui_ImageAnalysisDialog.h"
#include <QFileDialog>
#include <QObject>
#include <QImage>
#include <QDebug>
#include <QDebug>

/*!
   \brief ImageAnalysisDialog::ImageAnalysisDialog
   Standardconstructor.
 */
ImageAnalysisDialog::ImageAnalysisDialog( QWidget* parent )
    : QDialog( parent )
    , ui( new Ui::ImageAnalysisDialog )
    , m_lastDirectory( QDir::current() )
{
    ui->setupUi( this );

    connect( ui->loadButton, &QPushButton::pressed, this, &ImageAnalysisDialog::loadImage );
    connect( ui->computeHistogramButton, &QPushButton::pressed, this, &ImageAnalysisDialog::computeBackprojection );
    connect( ui->calculateSkinRegionButton, &QPushButton::pressed, this, &ImageAnalysisDialog::showSkinColor );
    connect( ui->saveRoiButton, &QPushButton::pressed, this, &ImageAnalysisDialog::saveROI );
}

/*!
   \brief ImageAnalysisDialog::~ImageAnalysisDialog
   Destroyes the object.
 */
ImageAnalysisDialog::~ImageAnalysisDialog()
{
}

/*!
   \brief ImageAnalysisDialog::loadImage
   Opens an image.
 */
void ImageAnalysisDialog::loadImage()
{
    QString filename = loadImageFromLastDirectory();
    if ( filename.isEmpty() )
    {
        qWarning( "Empty filename." );
        return;
    }
    // Convert the image in a bgr color image.
    // http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html
    m_imageBGR = cv::imread( filename.toStdString(), CV_LOAD_IMAGE_COLOR );
    cv::cvtColor( m_imageBGR, m_imageRGB, CV_BGR2RGB ); // convert into RGB
    QImage image( m_imageRGB.data, m_imageRGB.cols, m_imageRGB.rows, QImage::Format_RGB888 );
    ui->imageWidget->setImage( image );
}

/*!
   \brief ImageAnalysisDialog::saveROI
   Saves the rectangular region made by the user.
 */
void ImageAnalysisDialog::saveROI()
{
    QRect rect = ui->imageWidget->rect();
    if ( rect.width() ==  0 )
    {
        // case: Rectangle has as width of zero.
        //       This value is not valid, leave function.
        return;
    }
    cv::Mat roi = m_imageBGR( cv::Rect( rect.topLeft().x(),
                                        rect.topLeft().y(),
                                        rect.width(),
                                        rect.height() ) );
    m_skinColorDetectionPipeline.computeAndSaveROIHistogram( roi );
}

/*!
   \brief ImageAnalysisDialog::computeHistogram
   Computes the histogram of the rectangle drawn by the user if this area is valid.
 */
void ImageAnalysisDialog::computeBackprojection()
{
    if ( m_skinColorDetectionPipeline.roi().rows == 0 ||
         m_skinColorDetectionPipeline.roi().cols == 0 )
    {
        qWarning( "With or height of the roi image equals zero" );
        return;
    }
    cv::imshow( "roi", m_skinColorDetectionPipeline.roi() );
    cv::MatND backprojection;
    const float* range = { m_skinColorDetectionPipeline.ranges() };
    cv::calcBackProject( &m_imageBGR, 1, m_skinColorDetectionPipeline.channels(), m_skinColorDetectionPipeline.histogram(), backprojection, &range, 1, true );
    cv::imshow( "Backprojection", backprojection );
    cv::threshold( backprojection, backprojection, ui->thresholdSpinBox->value(), 255, cv::THRESH_BINARY );
    cv::imshow( "Threshold", backprojection );
}

/*!
   \brief ImageAnalysisDialog::showSkinColor
   Takes a copy of the bgr image and shows the pixels which have skin color.
 */
void ImageAnalysisDialog::showSkinColor()
{
    m_imageBGR.copyTo( m_skinColorImage );
    m_skiColorDefinedRegions.process( m_skinColorImage );
}

/*!
   \brief ImageAnalysisDialog::loadImageFromLastDirectory
   Loads an image and saves the path to it, if the user doesn't quit.
*/
QString ImageAnalysisDialog::loadImageFromLastDirectory()
{
    QString filename = QFileDialog::getOpenFileName( this,
                                                     QObject::tr( "Open"),
                                                     m_lastDirectory.absolutePath(),
                                                     QObject::tr( "Image files (*.png *.jpg *.bmp)") );
    if ( !filename.isEmpty() )
    {
        m_lastDirectory = QDir( filename );
    }
    return filename;
}


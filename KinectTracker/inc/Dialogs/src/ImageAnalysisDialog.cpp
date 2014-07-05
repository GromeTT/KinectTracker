#include "../inc/ImageAnalysisDialog.h"
#include "../../ImageWidget/inc/ImageWidget.h"
#include "../../ProcessingPipelines/inc/LowLevelProcessingPipeline.h"
#include "ui_ImageAnalysisDialog.h"
#include <QFileDialog>
#include <QObject>
#include <QImage>
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
    connect( ui->loadROIButton, &QPushButton::pressed, this, &ImageAnalysisDialog::loadROI );
    connect( ui->computeHistogramButton, &QPushButton::pressed, this, &ImageAnalysisDialog::computeHistogram );
    connect( ui->calculateSkinRegionButton, &QPushButton::pressed, this, &ImageAnalysisDialog::showSkinColor );
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
    QString filename = QFileDialog::getOpenFileName( this,
                                                     QObject::tr( "Open"),
                                                     m_lastDirectory.absolutePath(),
                                                     QObject::tr( "Image files (*.png *.jpg *.bmp)") );
    if ( filename.isEmpty() )
    {
        return;
    }
    m_lastDirectory = QDir( filename );
    // Convert the image in a bgr color image.
    // http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html
    m_imageBGR = cv::imread( filename.toStdString(), CV_LOAD_IMAGE_COLOR );
    cv::cvtColor( m_imageBGR, m_image, CV_BGR2RGB ); // convert into RGB
    QImage image( m_image.data, m_image.cols, m_image.rows, QImage::Format_RGB888 );
    ui->imageWidget->setImage( image );
}

void ImageAnalysisDialog::loadROI()
{
    QString filename = QFileDialog::getOpenFileName( this,
                                                     QObject::tr( "Open"),
                                                     m_lastDirectory.absolutePath(),
                                                     QObject::tr( "Image files (*.png *.jpg *.bmp)") );
    if ( filename.isEmpty() )
    {
        return;
    }
    m_roi = cv::imread( filename.toStdString(), CV_LOAD_IMAGE_COLOR );
    cv::imshow( "ROI", m_roi );
}

/*!
   \brief ImageAnalysisDialog::computeHistogram
   Computes the histogram of the rectangle drawn by the user if this area is valid.
 */
void ImageAnalysisDialog::computeHistogram()
{
    QRect rect = ui->imageWidget->rect();
    if ( rect.width() ==  0 )
    {
        // case: Rectangle has as width of zero.
        //       This value is not valid, leave function.
        return;
    }
    cv::imshow( "Original", m_imageBGR );
    cv::Mat roi = m_imageBGR( cv::Rect( rect.topLeft().x(),
                                        rect.topLeft().y(),
                                        rect.width(),
                                        rect.height() ) );

    cv::imshow( "roi", roi);
    int channels [] = { 0, 1, 2 };
    int bins[] = { 256, 256, 256 };
    float ranges [] = { 0, 256 };
    const float* rangesPerChannel = { ranges };
    cv::MatND roiHistogram;
    cv::calcHist( &roi, 1, &channels[0], cv::Mat(), roiHistogram, 1, &bins[0], &rangesPerChannel, true, false );
    cv::MatND backprojection;
    cv::calcBackProject( &m_image, 1, &channels[0], roiHistogram, backprojection, &rangesPerChannel, 1, true );
    cv::imshow( "Backprojection", backprojection );
    cv::threshold( backprojection, backprojection, ui->thresholdSpinBox->value(), 255, cv::THRESH_BINARY );
    cv::imshow( "Threshold", backprojection );
}

void ImageAnalysisDialog::showSkinColor()
{

}


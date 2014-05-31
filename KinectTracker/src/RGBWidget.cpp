#include "../Inc/RGBWidget.h"
#include "ui_RGBViewerWidget.h"

RGBWidget::RGBWidget( QWidget *parent )
    : QWidget(parent)
    , ui ( new Ui::RGBViewerWidget )
{
    ui->setupUi( this );
}

RGBWidget::~RGBWidget()
{

}

void RGBWidget::update(QImage* image)
{
    if ( image )
    {
        ui->label->setPixmap( QPixmap::fromImage( *image ) );
    }
}

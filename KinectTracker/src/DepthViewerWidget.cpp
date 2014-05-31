#include "../Inc/DepthViewerWidget.h"
#include "ui_DepthViewerWidget.h"


DepthViewerWidget::DepthViewerWidget( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::DepthViewerWidget )
{
    ui->setupUi( this );
}

DepthViewerWidget::~DepthViewerWidget()
{
    delete ui;
}

void DepthViewerWidget::update(QImage* image)
{
    if ( image )
    {
        ui->label->setPixmap( QPixmap::fromImage( *image ) );
    }
}

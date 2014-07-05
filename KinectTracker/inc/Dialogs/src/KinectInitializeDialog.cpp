#include "../Inc/KinectInitializeDialog.h"
#include "../../Kinect/inc/Kinect.h"
#include "ui_KinectInitializeDialog.h"
#include <QPushButton>

KinectInitializeDialog::KinectInitializeDialog( QSharedPointer<Kinect> kinect,
                                                QWidget* parent )
    :QDialog(parent)
    ,ui(new Ui::KinectInitializeDialog)
    ,m_kinect( kinect )
{
    ui->setupUi(this);

    ui->editKinectCount->setText( QString::number( kinect->getSensorCount() ) );

    connect( ui->buttonBox->button( QDialogButtonBox::Ok ), &QPushButton::clicked, this, &KinectInitializeDialog::accept );
    connect( ui->buttonBox->button( QDialogButtonBox::Cancel ), &QPushButton::clicked, this, &KinectInitializeDialog::reject );
}

KinectInitializeDialog::~KinectInitializeDialog()
{
}

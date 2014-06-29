#ifndef KINECTINITIALIZEDIALOG_H
#define KINECTINITIALIZEDIALOG_H

#include <QDialog>

class Kinect;

namespace Ui {
class KinectInitializeDialog;
}

class KinectInitializeDialog : public QDialog
{

public:
    explicit KinectInitializeDialog( QSharedPointer<Kinect> kinect,
                                     QWidget *parent = 0 );
    ~KinectInitializeDialog();

private:
    Ui::KinectInitializeDialog*     ui;
    QSharedPointer<Kinect>          m_kinect;
};

#endif // KINECTINITIALIZEDIALOG_H

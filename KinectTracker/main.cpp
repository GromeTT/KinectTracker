#include "MainWindow.h"
#include "inc/OpenGL/inc/OpenGLWindow.h"
#include <QTranslator>
#include <QApplication>
#include "inc/AMath/inc/AMath.h"
#include <QDebug>
#include <QtCore/QtMath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load( "../KinectTracker/trans/trans_de" );
    a.installTranslator( &translator );

    float phi, theta;
    QVector3D vec ( 1, 1, 0 );
    AMath::anglesFromSphericalCoordinates( phi, theta, vec );
    qDebug() << theta;
    qDebug() << qRadiansToDegrees( qAcos( vec.y() / vec.length() ) );

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

#include "MainWindow.h"
#include "inc/OpenGL/inc/OpenGLWindow.h"
#include <QTranslator>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load( "../KinectTracker/trans/trans_de" );
    a.installTranslator( &translator );

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

#ifndef DEPTHVIEWERWIDGETO_H
#define DEPTHVIEWERWIDGETO_H

#include <QWidget>

namespace Ui{
    class DepthViewerWidget;
}

class DepthViewerWidget : public QWidget
{

public:
    DepthViewerWidget( QWidget* parent = 0 );
    ~DepthViewerWidget();

    void update( QImage* image );

private:
    Ui::DepthViewerWidget* ui;

};

#endif // DEPTHVIEWERWIDGETO_H

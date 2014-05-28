#ifndef RGBWIDGET_H
#define RGBWIDGET_H

#include <QWidget>

namespace Ui
{
    class RGBViewerWidget;
}

class RGBWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RGBWidget(QWidget *parent = 0);
    ~RGBWidget();

    void update( QImage* image );

private:
    Ui::RGBViewerWidget* ui;
};

#endif // RGBWIDGET_H

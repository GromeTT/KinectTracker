#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

namespace Ui
{
    class ImageWidget;
}

class QImage;

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget( QWidget* parent = nullptr );
    virtual ~ImageWidget();

    void setImage( const QImage& image );
    bool eventFilter(QObject* object, QEvent* event );
    QRect rect() const;

private:
    void updateStatusbar();

    Ui::ImageWidget* ui;
    QImage           m_image;
    QPoint           m_startPoint;
    QPoint           m_endPoint;
    bool             m_leftMousePressed;


signals:
    void leftMousePressed( QPoint point );
    void leftMouseReleased( QPoint point );
    void mouseMoved( QPoint point );

};

#endif // IMAGEWIDGET_H

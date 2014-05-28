#ifndef SCENEGRAPHWIDGET_H
#define SCENEGRAPHWIDGET_H

#include <QWidget>

class RenderObject;
class QTreeWidgetItem;

typedef QVector<RenderObject*> RenderObjects;

namespace Ui {
class SceneGraphWidget;
}

class SceneGraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SceneGraphWidget( QWidget *parent = 0 );
    ~SceneGraphWidget();

    void addObject( const QObject& object );
    void addObject( const RenderObject& object );
    void addObjects( const QList<QObject*>& objects );
    void addObjects( const RenderObjects& objects );
    void addObjects( const QVector<QObject*>& objects );


    void clearTreeWidget();

private:
    void selectionHasChanged( QTreeWidgetItem* curr,
                              QTreeWidgetItem* prev );

signals:
    void selectionChanged( const QString& text );

private:
    Ui::SceneGraphWidget *ui;
};

#endif // SCENEGRAPHWIDGET_H

#ifndef SCENEGRAPHWIDGET_H
#define SCENEGRAPHWIDGET_H

#include <QWidget>

class RenderObject;
class QTreeWidgetItem;
class RenderObjectInterface;
class ProcessingComponent;

typedef QVector<RenderObjectInterface*> RenderObjects;

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
    void addObjects( const QList<QObject*>& objects );
    void addObjects( const RenderObjects& objects );
    void addObjects( const QVector<QObject*>& objects );
    void addObjects( const QVector<ProcessingComponent*>& objects );
    QObject* getCurrentObject() const;

    void clearTreeWidget();

private:
    void selectionHasChanged( QTreeWidgetItem* curr,
                              QTreeWidgetItem* prev );
    QTreeWidgetItem* createItemFromObject( const QObject& object );
    QTreeWidgetItem* createItemFromObject( const QObject& object,
                                           QTreeWidgetItem* parent );
    QTreeWidgetItem* createItemFromObject( QObject& object );
    QTreeWidgetItem* createItemFromObject( QObject& object,
                                           QTreeWidgetItem* parent );
    void addObjects( const QVector<ProcessingComponent*>& objects,
                     QTreeWidgetItem* parent );
signals:
    void selectionChanged( const QString& text );

private:
    Ui::SceneGraphWidget *ui;
};

#endif // SCENEGRAPHWIDGET_H

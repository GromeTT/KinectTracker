#ifndef SCENEGRAPHWIDGET_H
#define SCENEGRAPHWIDGET_H

#include <QWidget>

class RenderObject;
class QTreeWidgetItem;
class RenderObjectInterface;
class ProcessingComponent;
class LowLevelProcessingPipeline;

typedef QVector<RenderObjectInterface*> RenderObjects;
typedef QSharedPointer<LowLevelProcessingPipeline> LowLevelProcessingPipelinePtr;

namespace Ui {
class SceneGraphWidget;
}

class SceneGraphWidget : public QWidget
{
    Q_OBJECT

public:
    enum class ActiveScene
    {
        RGBProcessingPipeline = 0,
        DepthProcessingPipeline = 1,
        RenderScene = 2
    };

public:
    explicit SceneGraphWidget( QWidget *parent = 0 );
    ~SceneGraphWidget();

    QObject*     getCurrentObject() const;
    ActiveScene  activeScene() const;
//    void addObject( QObject* object );
    void addObject( const QObject* object );
    void addObject( QObject* object );
    void addObjects( const QList<QObject*>& objects );
    void addObjects( const RenderObjects& objects );
    void addObjects( const QVector<QObject*>& objects );
    void addObjects( const QVector<ProcessingComponent*>& objects );
    void clearTreeWidget();

private:
    void selectionHasChanged( QTreeWidgetItem* curr,
                              QTreeWidgetItem* prev );
    QTreeWidgetItem* createItemFromObject( const QObject* object );
    QTreeWidgetItem* createItemFromObject( const QObject* object,
                                           QTreeWidgetItem* parent );
    QTreeWidgetItem* createItemFromObject( QObject* object );
    QTreeWidgetItem* createItemFromObject( QObject* object,
                                           QTreeWidgetItem* parent );
    void addObjects( const QVector<ProcessingComponent*>& objects,
                     QTreeWidgetItem* parent );

    ActiveScene m_activeScene;
private slots:
    void comboBoxChanged( int index );

signals:
    void selectionChanged( const QString& text );
    void sceneChanged( ActiveScene index );

private:
    Ui::SceneGraphWidget *ui;
};

#endif // SCENEGRAPHWIDGET_H

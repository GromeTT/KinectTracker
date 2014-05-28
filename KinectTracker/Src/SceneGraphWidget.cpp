#include "../Inc/SceneGraphWidget.h"
#include "../Inc/RenderObject.h"
#include "ui_SceneGraphWidget.h"

SceneGraphWidget::SceneGraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneGraphWidget)
{
    ui->setupUi(this);

    ui->treeWidget->setHeaderLabel( "Objects" );
    connect( ui->treeWidget, &QTreeWidget::currentItemChanged, this, &SceneGraphWidget::selectionHasChanged );
}

SceneGraphWidget::~SceneGraphWidget()
{
    delete ui;
}

void SceneGraphWidget::addObject( const QObject& object )
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText( 0, object.objectName() );
    ui->treeWidget->invisibleRootItem()->addChild( item );
}

void SceneGraphWidget::addObject( const RenderObject& object )
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText( 0, object.objectName() );
    ui->treeWidget->invisibleRootItem()->addChild( item );
}

void SceneGraphWidget::addObjects( const QList<QObject*>& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        addObject( *objects.at( i ) );
    }
}

void SceneGraphWidget::addObjects( const RenderObjects& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        addObject( *objects.at( i ) );
    }
}

void SceneGraphWidget::addObjects( const QVector<QObject*>& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        addObject( *objects.at( i ) );
    }
}

void SceneGraphWidget::clearTreeWidget()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->invisibleRootItem()->takeChildren();
    while( !items.isEmpty() )
    {
        QTreeWidgetItem* item = items.takeFirst();
        items.append( item->takeChildren() );
        delete item;
        item = nullptr;
    }
}

void SceneGraphWidget::selectionHasChanged( QTreeWidgetItem* curr,
                                            QTreeWidgetItem* prev )
{
    Q_UNUSED( prev );
    if ( !curr )
    {
        return;
    }
    emit selectionChanged( curr->text(0) );
}



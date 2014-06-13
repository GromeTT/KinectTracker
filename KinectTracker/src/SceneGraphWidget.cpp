#include "../inc/SceneGraphWidget.h"
#include "../inc/RenderObject.h"
#include "../inc/ProcessingComponent.h"
#include "../inc/QObjectTreeWidgetItem.h"
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
    QTreeWidgetItem* item = createItemFromObject( object );
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

void SceneGraphWidget::addObjects( const QVector<ProcessingComponent*>& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        QTreeWidgetItem* parent = createItemFromObject( *objects.at( i ) );
        addObjects( objects.at( i )->getComponents(), parent );
        ui->treeWidget->invisibleRootItem()->addChild( parent );
    }
}

QObject* SceneGraphWidget::getCurrentObject() const
{
    QObjectTreeWidgetItem* item = dynamic_cast<QObjectTreeWidgetItem*>( ui->treeWidget->currentItem() );
    if ( !item )
    {
        return nullptr;
    }
    else
    {
        return item->getObject();
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

QTreeWidgetItem* SceneGraphWidget::createItemFromObject( const QObject& object )
{
    QObjectTreeWidgetItem* item = new QObjectTreeWidgetItem();
    item->setText( 0, object.objectName() );
    return item;
}

QTreeWidgetItem* SceneGraphWidget::createItemFromObject( const QObject& object,
                                                         QTreeWidgetItem* parent )
{
    QTreeWidgetItem* item = createItemFromObject( object );
    parent->addChild( item );
    return item;
}

QTreeWidgetItem*SceneGraphWidget::createItemFromObject( QObject& object )
{
    QObjectTreeWidgetItem* item = new QObjectTreeWidgetItem();
    item->setText( 0, object.objectName() );
    item->setObject( &object );
    return item;
}

QTreeWidgetItem*SceneGraphWidget::createItemFromObject( QObject& object,
                                                        QTreeWidgetItem* parent )
{
    QTreeWidgetItem* item = createItemFromObject( object );
    parent->addChild( item );
    return item;
}

void SceneGraphWidget::addObjects( const QVector<ProcessingComponent*>& objects,
                                   QTreeWidgetItem* parent )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        QTreeWidgetItem* item = createItemFromObject( *objects.at( i ), parent );
        addObjects( objects.at( i )->getComponents(), item );
    }
}



#include "../inc/SceneGraphWidget.h"
#include "../inc/QObjectTreeWidgetItem.h"
#include "../../OpenGL/inc/RenderObject.h"
#include "../../ProcessingPipelines/inc/ProcessingComponent.h"
#include "../../ProcessingPipelines/inc/LowLevelProcessingPipeline.h"
#include "ui_SceneGraphWidget.h"

SceneGraphWidget::SceneGraphWidget(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::SceneGraphWidget )
    , m_activeScene( ActiveScene::RGBProcessingPipeline )
{
    ui->setupUi( this );

    ui->treeWidget->setHeaderLabel( "Objects" );
    ui->comboBox->addItem( "RGBProcessingPipeline" );
    ui->comboBox->addItem( "DepthProcessingPipeline" );
    ui->comboBox->addItem( tr( "Render Scene" ) );

    connect( ui->treeWidget, &QTreeWidget::currentItemChanged, this, &SceneGraphWidget::selectionHasChanged );
    connect( ui->comboBox,   SIGNAL( currentIndexChanged( int ) ) , this, SLOT( comboBoxChanged( int ) ) );
}

SceneGraphWidget::~SceneGraphWidget()
{
    delete ui;
}

//void SceneGraphWidget::addObject( QObject* object )
//{
//    if ( !object )
//    {
//        return;
//    }
//    QTreeWidgetItem* item = createItemFromObject( object );
//    ui->treeWidget->invisibleRootItem()->addChild( item );
//}

void SceneGraphWidget::addObject( const QObject* object )
{
    if ( !object )
    {
        return;
    }
    QTreeWidgetItem* item = createItemFromObject( object );
    ui->treeWidget->invisibleRootItem()->addChild( item );
}

void SceneGraphWidget::addObject(QObject* object)
{
    if ( !object )
    {
        return;
    }
    QTreeWidgetItem* item = createItemFromObject( object );
    ui->treeWidget->invisibleRootItem()->addChild( item );
}

void SceneGraphWidget::addObjects( const QList<QObject*>& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        addObject( objects.at( i ) );
    }
}

void SceneGraphWidget::addObjects( const RenderObjects& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        addObject( objects.at( i ) );
    }
}

void SceneGraphWidget::addObjects( const QVector<QObject*>& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        addObject( objects.at( i ) );
    }
}

void SceneGraphWidget::addObjects( const QVector<ProcessingComponent*>& objects )
{
    for ( int i = 0; i < objects.count(); ++i )
    {
        QTreeWidgetItem* parent = createItemFromObject( objects.at( i ) );
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

/*!
   \brief SceneGraphWidget::activeScene
   Returns the active scene.
 */
SceneGraphWidget::ActiveScene SceneGraphWidget::activeScene() const
{
    return m_activeScene;
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

QTreeWidgetItem* SceneGraphWidget::createItemFromObject( const QObject* object )
{
    QObjectTreeWidgetItem* item = new QObjectTreeWidgetItem();
    item->setText( 0, object->objectName() );
    return item;
}

QTreeWidgetItem* SceneGraphWidget::createItemFromObject( const QObject* object,
                                                         QTreeWidgetItem* parent )
{
    QTreeWidgetItem* item = createItemFromObject( object );
    parent->addChild( item );
    return item;
}

QTreeWidgetItem*SceneGraphWidget::createItemFromObject( QObject* object )
{
    QObjectTreeWidgetItem* item = new QObjectTreeWidgetItem();
    item->setText( 0, object->objectName() );
    item->setObject( object );
    return item;
}

QTreeWidgetItem*SceneGraphWidget::createItemFromObject( QObject* object,
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
        QTreeWidgetItem* item = createItemFromObject( objects.at( i ), parent );
        addObjects( objects.at( i )->getComponents(), item );
    }
}

/*!
   \brief SceneGraphWidget::comboBoxChanged
   Is called, whenever the value in the QComboBox changes.
 */
void SceneGraphWidget::comboBoxChanged( int index )
{
    switch ( index )
    {
        case 0:
        {
            m_activeScene = ActiveScene::RGBProcessingPipeline;
            break;
        }
        case 1:
        {
            m_activeScene = ActiveScene::DepthProcessingPipeline;
            break;
        }
        case 2:
        {
            m_activeScene = ActiveScene::RenderScene;
            break;
        }
    }
    emit sceneChanged( m_activeScene );
}



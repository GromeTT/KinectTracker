#include "../inc/TreeModel.h"
#include "../inc/FixedPropertyVector.h"
#include <QTreeWidgetItem>
#include <QVector3D>
#include <QMetaProperty>
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDebug>


Q_DECLARE_METATYPE( cv::Size )
Q_DECLARE_METATYPE( FixedPropertyVector )

TreeModel::TreeModel( QObject* parent )
    : QStandardItemModel( parent )
    , mp_object( nullptr )
{
    m_updateSlot = metaObject()->method( metaObject()->indexOfSlot( "propertyChanged()" ) );

    // Set up the horizontal headers.
    setColumnCount( 3 );
    QStringList horizontalHeaders;
    horizontalHeaders << tr( "property" ) << tr( "value" ) << tr( "type" );
    setHorizontalHeaderLabels( horizontalHeaders );

    // Changes on item -> data
    connect( this, SIGNAL( itemChanged( QStandardItem* ) ), this, SLOT( slotItemChanged(QStandardItem*) ) );
}

TreeModel::~TreeModel()
{

}

/*!
   \brief TreeModel::setObject

 */
void TreeModel::setObject( QObject* object )
{
    // Clean up workspace if necessary.
    if ( mp_object &&
         mp_object != object )
    {
        // Remove connections.
        for ( int i = 0 ; i < object->metaObject()->propertyCount(); ++i )
        {
            if ( metaObject()->property( i ).hasNotifySignal() )
            {
                QMetaMethod signal = metaObject()->property( i ).notifySignal();
                bool res = disconnect( mp_object, signal, this, m_updateSlot  );
                Q_ASSERT( res );
            }
        }
        // Delete items.
        deleteAllItems();
        // Clear the mapping.
        m_propertyIndexToItemMap.clear();
    }

    mp_object = object;

    if ( !object )
    {
        // No object is passed, nothing needs to be done.
        return;
    }

    // A valdid object is passed, fill the QTreeView with it's properties.
    int propertyCount = object->metaObject()->propertyCount();
    for ( int i = 0; i < propertyCount; ++i )
    {
        QMetaProperty metaProperty = object->metaObject()->property( i );
        QString typeName = metaProperty.name();
        QVariant value   = object->property( metaProperty.name() );

        QList<QStandardItem*> itemRow;

        QStandardItem* first = createItem( metaProperty, typeName, false );
        itemRow.append( first );

        // Unwrap special QVariant types.
        if ( value.canConvert<QVector3D>() )
        {
            // Case: QVector3D

            QVector3D vec = qvariant_cast<QVector3D>( value );
            QList<QStandardItem*> nextRow;

            // Extract values from QVector3D
            QStandardItem* tmp = nullptr;

            // x-coordinate
            tmp= createItem( metaProperty, "x", false );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, vec.x(), true );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, "float", false );
            nextRow.append( tmp );
            first->appendRow( nextRow );
            nextRow.clear();

            // y-coordinate
            tmp= createItem( metaProperty, "y", false );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, vec.y(), true );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, "float", false );
            nextRow.append( tmp );
            first->appendRow( nextRow );
            nextRow.clear();

            // z-coordinte
            tmp= createItem( metaProperty, "z", false );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, vec.z(), true );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, "float", false );
            nextRow.append( tmp );
            first->appendRow( nextRow );

            // Append second and third item on the top level.
            tmp = createItem( metaProperty, value, false );
            itemRow.append( tmp );
            tmp = createItem( metaProperty, "QVector3D", false );
            itemRow.append( tmp );
        }
        else if ( value.canConvert<cv::Size>() )
        {
            // Case: cv::Size

            cv::Size size = qvariant_cast<cv::Size>( value );
            QList<QStandardItem*> nextRow;

            // Extract values from cv::Size
            QStandardItem* tmp = nullptr;

            // Width
            tmp= createItem( metaProperty, tr( "width" ), false );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, size.width, true );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, "uchar", false );
            nextRow.append( tmp );
            first->appendRow( nextRow );
            nextRow.clear();

            // Height
            tmp= createItem( metaProperty, tr( "height" ), false );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, size.height, true );
            nextRow.append( tmp );
            tmp = createItem( metaProperty, "uchar", false );
            nextRow.append( tmp );
            first->appendRow( nextRow );
            nextRow.clear();

            // Append editable data.
            tmp = createItem( metaProperty, value, false );
            connectProperty( mp_object, metaProperty, tmp );
            itemRow.append( tmp );
        }
        else if ( value.canConvert<FixedPropertyVector>() )
        {
            // Case: FixedPropertyVector

            FixedPropertyVector vec = qvariant_cast<FixedPropertyVector>( value );
            QList<QStandardItem*> nextRow;

            QStandardItem* tmp;
            for ( int i = 0; i < vec.size(); ++i )
            {
                nextRow.clear();
                // Append name.
                tmp = createItem( metaProperty, QString::number( i ), false );
                nextRow.append( tmp );
                // Append data.
                tmp = createItem( metaProperty, vec.at( i ), true );
                nextRow.append( tmp );
                // Append type informations.
                tmp = createItem( metaProperty, "float", false );
                nextRow.append( tmp );

                first->appendRow( nextRow );
            }
            // Append editable data.
            tmp = createItem( metaProperty, value, false );
            connectProperty( mp_object, metaProperty, tmp );
            itemRow.append( tmp );
        }
        else
        {
            // Append editable data.
            QStandardItem*  tmp = createItem( metaProperty, value, true );
            connectProperty( mp_object, metaProperty, tmp );
            itemRow.append( tmp );
        }

        // Append type informations.
        QStandardItem* tmp = createItem( metaProperty, value.typeName(), false );
        itemRow.append( tmp );

        // Append the row to the invisible root item.
        appendRow( itemRow );
    }
}


/*!
   \brief TreeModel::createItem
   Creates an QStandardItem displaying the data from \a value.
   The flags Qt::ItemIsSelectable and Qt::ItemIsEnabled are always set.
   If \a metaProperty is \b writable and \a editable is set to true
   the flag Qt::ItemIsEditable will be set and the data is stored in
   Qt::EditRole.
   Otherwise the data will be put in the Qt::DisplayRole slot.
 */
QStandardItem* TreeModel::createItem( const QMetaProperty& metaProperty,
                                      const QVariant& value,
                                      const bool editable )
{
    QStandardItem* item = new QStandardItem();
    if ( !editable || !metaProperty.isWritable() )
    {
        item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        item->setData( value, Qt::DisplayRole );
    }
    else
    {
        item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
        item->setData( value, Qt::EditRole );
    }
    return item;
}

/*!
   \brief TreeModel::connectProperty
    If \a property has got a notify signal, it will be connected to
    TreeModel::itemChanged( QStandardItem *item ).
 */
void TreeModel::connectProperty( QObject* object,
                                 const QMetaProperty& metaProperty,
                                 QStandardItem* item )
{
    Q_ASSERT( object );

    if ( metaProperty.hasNotifySignal() )
    {
        int index = object->metaObject()->indexOfProperty( metaProperty.name() );
        m_propertyIndexToItemMap.insert( index, item );
        QMetaMethod signal = metaProperty.notifySignal();
        connect( object, signal, this, m_updateSlot );
    }
}

/*!
   \brief TreeModel::updateItem
   Updates \a item with the data provided by \a object and \a metaProperty.
   If \a metaProperty is writable, the data will be stored in Qt::EditRole,
   otherwise in Qt::DisplayRole.
 */
void TreeModel::updateItem( QStandardItem* item,
                            QObject* object,
                            const QMetaProperty& metaProperty )
{
    Q_ASSERT( item );
    Q_ASSERT( mp_object );
    if ( metaProperty.isWritable() )
    {
        item->setData( object->property( metaProperty.name() ), Qt::EditRole );
    }
    {
        item->setData( object->property( metaProperty.name() ), Qt::DisplayRole );
    }

}

/*!
   \brief TreeModel::deleteAllItems
   Deletes all items in the QTreeView.
 */
void TreeModel::deleteAllItems()
{
    while ( invisibleRootItem()->rowCount() > 0 )
    {
        QList<QStandardItem*> childs = invisibleRootItem()->takeRow( 0 );
        qDeleteAll( childs );
    }
}

/*!
   \brief TreeModel::propertyChanged
   This function is responsible to propagade the changes in the data to
   the GUI.
 */
void TreeModel::propertyChanged()
{
    int propCount   = QObject::sender()->metaObject()->propertyCount();
    int signalIndex = QObject::senderSignalIndex();
    for ( int i = 0; i < propCount; ++i )
    {
        QMetaProperty metaProperty = mp_object->metaObject()->property( i );
        if ( metaProperty.notifySignalIndex() == signalIndex )
        {
            QStandardItem* item = m_propertyIndexToItemMap.value( i );
            updateItem( item, mp_object, metaProperty );
            return;
        }
    }
}


/*!
   \brief TreeModel::slotItemChanged
 */
void TreeModel::slotItemChanged( QStandardItem* item )
{
    // Item should always be there.
    Q_ASSERT( item );

    // Get property name.
    QStandardItem* propNameItem = QStandardItemModel::item( item->row(), 0 );
    Q_ASSERT( propNameItem );
    QString propertyName;
    if ( item->parent() &&
         item->parent() != invisibleRootItem() )
    {
        propertyName = item->parent()->text();
    }
    else
    {
        propertyName = propNameItem->text();
    }

    int propertyIndex = mp_object->metaObject()->indexOfProperty( propertyName.toStdString().c_str() );
    QMetaProperty metaProperty  = mp_object->metaObject()->property( propertyIndex );
    QVariant value = mp_object->property( metaProperty.name() );
    if ( metaProperty.isWritable() )
    {
        if ( value.canConvert<QVector3D>() )
        {
            QVector3D vec;
            vec.setX( propNameItem->child( 0, 0 )->data( Qt::EditRole ).toFloat() );
            vec.setY( propNameItem->child( 0, 1 )->data( Qt::EditRole ).toFloat() );
            vec.setZ( propNameItem->child( 0, 2 )->data( Qt::EditRole ).toFloat() );

            mp_object->setProperty( metaProperty.name(), QVariant::fromValue( vec ) );
        }
        else if ( value.canConvert<cv::Size>() )
        {
            cv::Size size;
            size.width = propNameItem->child( 0, 0 )->data( Qt::EditRole ).toInt();
            size.height= propNameItem->child( 0, 1 )->data( Qt::EditRole ).toInt();

            mp_object->setProperty( metaProperty.name(), QVariant::fromValue( size ) );
        }
        else if ( value.canConvert<FixedPropertyVector>() )
        {
            int count = propNameItem->rowCount();

            FixedPropertyVector vec ( count );
            for ( int i = 0; i < vec.size(); ++i )
            {
                vec.setData( i, propNameItem->child( i, 1 )->data( Qt::EditRole).toFloat() );
            }
            mp_object->setProperty( metaProperty.name(), QVariant::fromValue( vec ) );
        }
        else
        {
            // case : Standardprocedure
            mp_object->setProperty( metaProperty.name(), item->data( Qt::EditRole ) );
        }
    }
}


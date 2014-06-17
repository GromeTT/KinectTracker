#include "../Inc/Explorer.h"
#include "ui_Explorer.h"
#include "../inc/FloatEditor.h"
#include "../inc/FixedPropertyVector.h"
#include <QItemEditorFactory>

#include <QDebug>

Q_DECLARE_METATYPE( FixedPropertyVector )

Explorer::Explorer(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::Explorer )
{
    ui->setupUi( this );
    mp_styledDelegate = new CustomStyledDelegate( ui->tableWidget );

    // If the column count is less than 3, the labels are not
    // displayed correctly.
    ui->tableWidget->setColumnCount( 3 );
    QStringList labelNames;
    labelNames << "Name" << "Type" << "Value";
    ui->tableWidget->setHorizontalHeaderLabels( labelNames );
    QItemEditorFactory* factory = new QItemEditorFactory();

    QItemEditorCreatorBase* floatEditor = new QStandardItemEditorCreator<FloatEditor>();
    factory->registerEditor( QMetaType::Float, floatEditor );
    mp_styledDelegate->setItemEditorFactory( factory );

    ui->tableWidget->setItemDelegate( mp_styledDelegate );

    connect( ui->tableWidget, &QTableWidget::itemChanged, this, &Explorer::itemChanged );
}

Explorer::~Explorer()
{
    delete ui;
}

/**
 * @brief Explorer::setObject
 * All properties of \a object will be extracted and displayed in
 * a QTableWidget.
 * @param object
 */
bool Explorer::setObject( QObject* object )
{
    if ( !object )
    {
        return false;
    }

    // Store object for updating purpose.
    mp_object = object;

    // Adjust table dimensions
    int propertyCount = object->metaObject()->propertyCount();
    ui->tableWidget->setRowCount( propertyCount );
    ui->tableWidget->setColumnCount( 3 );


    for ( int i = 0; i < propertyCount; ++ i )
    {
        // Extract all properties and store them into QTableWidgetItems.
        QMetaProperty metaProperty = object->metaObject()->property( i );
        QString name     = metaProperty.name();
        QString typeName = metaProperty.typeName();
        QVariant value   = object->property( metaProperty.name() );

        QTableWidgetItem* nameItem = new QTableWidgetItem( name );
        nameItem->setFlags( Qt::NoItemFlags );
        QTableWidgetItem* typeItem = new QTableWidgetItem( typeName );
        typeItem->setFlags( Qt::NoItemFlags );
        QTableWidgetItem* propItem = new QTableWidgetItem();
        propItem->setData( Qt::EditRole, value );

        ui->tableWidget->setItem( i, 0, nameItem );
        ui->tableWidget->setItem( i, 1, typeItem );
        ui->tableWidget->setItem( i, 2, propItem );

        if ( metaProperty.hasNotifySignal() )
        {
            QMetaMethod signal = metaProperty.notifySignal();
            QMetaMethod slot   = metaObject()->method( metaObject()->indexOfSlot( "propertyChanged()" ) );
            connect( mp_object, signal, this, slot );
        }
    }
    return true;
}

void Explorer::itemChanged( QTableWidgetItem* item )
{
    // Item should always be there.
    Q_ASSERT( item );
    if ( item->column() == 2 )
    {
        // Get item in the first column which contains the property name.
        QTableWidgetItem* propNameItem = ui->tableWidget->item( item->row(), item->column() - 2 );
        Q_ASSERT( propNameItem );

        // Check if property is writable.
        bool writable = mp_object->metaObject()->property( item->row() ).isWritable();
        if ( writable )
        {
            // Alter property.
            if ( propNameItem->text() == "lowerBounds" )
            {
                QVariant v( item->data( Qt::EditRole ) );
                FixedPropertyVector f = qvariant_cast<FixedPropertyVector>( v );
            }
            mp_object->setProperty( propNameItem->text().toStdString().c_str(), QVariant( item->data( Qt::EditRole ) ) );
        }
    }
}

void Explorer::propertyChanged()
{

    int propCount   = QObject::sender()->metaObject()->propertyCount();
    int signalIndex = QObject::senderSignalIndex();
    for ( int i = 0; i < propCount; ++i )
    {
        QMetaProperty metaProp = mp_object->metaObject()->property( i );
        if ( metaProp.notifySignalIndex() == signalIndex )
        {
            ui->tableWidget->item( i, 2 )->setData( Qt::EditRole,
                                                    mp_object->property( metaProp.name() ) );
        }
    }
}

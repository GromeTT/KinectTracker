#include "../Inc/Explorer.h"
#include "ui_Explorer.h"

#include <QDebug>
#include <QMetaProperty>

Explorer::Explorer(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::Explorer )
{
    ui->setupUi( this );

    // If the column count is less than 3, the labels are not
    // displayed correctly.
    ui->tableWidget->setColumnCount( 3 );
    QStringList labelNames;
    labelNames << "Name" << "Type" << "Value";
    ui->tableWidget->setHorizontalHeaderLabels( labelNames );

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
bool Explorer::setObject(QObject* object )
{
//    if ( mp_object )
//    {
//        disconnect( mp_object, 0, this, 0 );
//    }
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
        QTableWidgetItem* propItem = new QTableWidgetItem( value.toString() );

        ui->tableWidget->setItem( i, 0, nameItem );
        ui->tableWidget->setItem( i, 1, typeItem );
        ui->tableWidget->setItem( i, 2, propItem );

        if ( metaProperty.hasNotifySignal() )
        {
            QMetaMethod signal = metaProperty.notifySignal();
            QMetaMethod slot   = metaObject()->method( metaObject()->indexOfSlot( "propertyChanged()") );
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
            mp_object->setProperty( propNameItem->text().toStdString().c_str(), item->text() );
        }
    }
}

void Explorer::propertyChanged()
{
    int signalIndex = QObject::senderSignalIndex();
    int propCount = QObject::sender()->metaObject()->propertyCount();
    for ( int i = 0; i < propCount; ++i )
    {
        QMetaProperty metaProp = mp_object->metaObject()->property( i );
        if ( metaProp.notifySignalIndex() == signalIndex )
        {
            QString name = metaProp.name();
            QString value = mp_object->property( metaProp.name() ).toString();
            ui->tableWidget->item( i, 2 )->setText( value );
        }
    }
}

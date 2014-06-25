#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>
#include <QMap>
#include <QMetaMethod>

class QTreeWidgetItem;

class TreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    TreeModel( QObject* parent = nullptr );
    ~TreeModel();

    void setObject( QObject* object );
    void clearModel();

private:
    QStandardItem* createItem( const QMetaProperty& metaProperty,
                               const QVariant& value,
                               const bool editable );
    void connectProperty( QObject* object,
                          const QMetaProperty& metaProperty ,
                          QStandardItem* item );
    void updateItem( QStandardItem* item,
                     QObject* object,
                     const QMetaProperty& metaProperty );
    void deleteAllItems();

private slots:
    void propertyChanged();
    void slotItemChanged( QStandardItem* item );

private:
    QObject*                  mp_object;
    QMetaMethod               m_updateSlot;
    QMap<int, QStandardItem*> m_propertyIndexToItemMap;

};


#endif // TREEMODEL_H

#include "../inc/QObjectTreeWidgetItem.h"


QObjectTreeWidgetItem::QObjectTreeWidgetItem()
    : QTreeWidgetItem()
    , m_object( nullptr )
{

}

QObjectTreeWidgetItem::~QObjectTreeWidgetItem()
{

}

void QObjectTreeWidgetItem::setObject( QObject* object )
{
    m_object = object;
}

QObject* QObjectTreeWidgetItem::getObject()
{
    return m_object;
}

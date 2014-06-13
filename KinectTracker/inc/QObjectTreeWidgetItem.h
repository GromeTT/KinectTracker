#ifndef QOBJECTTREEWIDGETITEMS_H
#define QOBJECTTREEWIDGETITEMS_H

#include <QTreeWidgetItem>

class QObjectTreeWidgetItem : public QTreeWidgetItem
{
public:
    QObjectTreeWidgetItem();
    virtual ~QObjectTreeWidgetItem();

    void setObject( QObject* object );
    QObject* getObject();

private:
    QObject* m_object;

};

#endif // QOBJECTTREEWIDGETITEMS_H

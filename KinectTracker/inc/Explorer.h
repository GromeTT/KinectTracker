#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QSignalMapper>
#include <QMetaMethod>
#include "CustomStyledDelegate.h"

namespace Ui {
    class Explorer;
}

class Explorer : public QWidget
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = 0);
    ~Explorer();

    bool setObject( QObject* object );
    void clearView();

private:
    void itemChanged( QTableWidgetItem* item );
private slots:
    void propertyChanged();

private:
    Ui::Explorer*           ui;
    CustomStyledDelegate*   mp_styledDelegate;
    QObject*                mp_object;
    bool                    mp_updateHorizontalHeaderLabels;
};

#endif // EXPLORER_H

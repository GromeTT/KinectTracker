#ifndef TREEWIDGETEXPLORER_H
#define TREEWIDGETEXPLORER_H

#include <QWidget>

namespace Ui
{
    class PropertyBrowser;
}

class TreeModel;
class CustomStyledDelegate;

class PropertyBrowser : public QWidget
{
public:
    PropertyBrowser( QWidget* parent );
    ~PropertyBrowser();

    void setObject( QObject* object );

private:
    TreeModel*              mp_treeModel;
    CustomStyledDelegate*   mp_styledDelegate;
    Ui::PropertyBrowser*    ui;
};

#endif // TREEWIDGETEXPLORER_H

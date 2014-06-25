#include "../inc/PropertyBrowser.h"
#include "../inc/TreeModel.h"
#include "../inc/CustomStyledDelegate.h"
#include "../inc/FloatEditor.h"
#include "ui_PropertyBrowser.h"
#include <QMetaProperty>
#include <QItemEditorCreatorBase>

/*!
   \brief PropertyBrowser::PropertyBrowser
 */
PropertyBrowser::PropertyBrowser( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::PropertyBrowser )
    , mp_treeModel( new TreeModel( this ) )
    , mp_styledDelegate( new CustomStyledDelegate( this ) )
{
    ui->setupUi( this );
    ui->treeView->setModel( mp_treeModel );

    QItemEditorFactory* factory = new QItemEditorFactory();
    QItemEditorCreatorBase* floatEditor = new QStandardItemEditorCreator<FloatEditor>();
    factory->registerEditor( QMetaType::Float, floatEditor );
    mp_styledDelegate->setItemEditorFactory( factory );

    ui->treeView->setItemDelegate( mp_styledDelegate );
}

/*!
   \brief PropertyBrowser::~PropertyBrowser
   Destroys the widget.
 */
PropertyBrowser::~PropertyBrowser()
{
}

/*!
   \brief PropertyBrowser::setObject
   Displays all properties of \a object in the QTreeView.
 */
void PropertyBrowser::setObject( QObject* object )
{
    // Display the object's name and it's class name.
    if ( object )
    {
        ui->objectInfoLabel->setText( QString( "%1 : %2" ).arg( object->objectName() )
                                                          .arg( object->metaObject()->className() ) );
    }
    else
    {
        ui->objectInfoLabel->setText( tr( "No selection") );
    }
    // Pass object to the TreeModel.
    mp_treeModel->setObject( object );
}

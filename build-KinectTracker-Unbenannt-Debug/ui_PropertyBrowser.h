/********************************************************************************
** Form generated from reading UI file 'PropertyBrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYBROWSER_H
#define UI_PROPERTYBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropertyBrowser
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *objectInfoLabel;
    QTreeView *treeView;

    void setupUi(QWidget *PropertyBrowser)
    {
        if (PropertyBrowser->objectName().isEmpty())
            PropertyBrowser->setObjectName(QStringLiteral("PropertyBrowser"));
        PropertyBrowser->resize(400, 300);
        verticalLayout = new QVBoxLayout(PropertyBrowser);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        objectInfoLabel = new QLabel(PropertyBrowser);
        objectInfoLabel->setObjectName(QStringLiteral("objectInfoLabel"));
        objectInfoLabel->setFrameShape(QFrame::Panel);
        objectInfoLabel->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(objectInfoLabel);

        treeView = new QTreeView(PropertyBrowser);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setFrameShape(QFrame::Panel);
        treeView->setMidLineWidth(10);
        treeView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        treeView->setProperty("showDropIndicator", QVariant(false));
        treeView->setAlternatingRowColors(true);
        treeView->setTextElideMode(Qt::ElideNone);
        treeView->setRootIsDecorated(true);
        treeView->setAllColumnsShowFocus(true);
        treeView->setWordWrap(true);
        treeView->setHeaderHidden(false);
        treeView->header()->setVisible(true);
        treeView->header()->setHighlightSections(true);

        verticalLayout->addWidget(treeView);


        retranslateUi(PropertyBrowser);

        QMetaObject::connectSlotsByName(PropertyBrowser);
    } // setupUi

    void retranslateUi(QWidget *PropertyBrowser)
    {
        PropertyBrowser->setWindowTitle(QApplication::translate("PropertyBrowser", "Form", 0));
        objectInfoLabel->setText(QApplication::translate("PropertyBrowser", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertyBrowser: public Ui_PropertyBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYBROWSER_H

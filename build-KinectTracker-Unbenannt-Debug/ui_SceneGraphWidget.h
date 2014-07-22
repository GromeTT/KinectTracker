/********************************************************************************
** Form generated from reading UI file 'SceneGraphWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEGRAPHWIDGET_H
#define UI_SCENEGRAPHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneGraphWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *SceneGraphWidget)
    {
        if (SceneGraphWidget->objectName().isEmpty())
            SceneGraphWidget->setObjectName(QStringLiteral("SceneGraphWidget"));
        SceneGraphWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(SceneGraphWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SceneGraphWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(SceneGraphWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(SceneGraphWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);


        retranslateUi(SceneGraphWidget);

        QMetaObject::connectSlotsByName(SceneGraphWidget);
    } // setupUi

    void retranslateUi(QWidget *SceneGraphWidget)
    {
        SceneGraphWidget->setWindowTitle(QApplication::translate("SceneGraphWidget", "Form", 0));
        label->setText(QApplication::translate("SceneGraphWidget", "Scene:", 0));
    } // retranslateUi

};

namespace Ui {
    class SceneGraphWidget: public Ui_SceneGraphWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEGRAPHWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'KinectInitializeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KINECTINITIALIZEDIALOG_H
#define UI_KINECTINITIALIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_KinectInitializeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *labelKinectCount;
    QLineEdit *editKinectCount;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;

    void setupUi(QDialog *KinectInitializeDialog)
    {
        if (KinectInitializeDialog->objectName().isEmpty())
            KinectInitializeDialog->setObjectName(QStringLiteral("KinectInitializeDialog"));
        KinectInitializeDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(KinectInitializeDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelKinectCount = new QLabel(KinectInitializeDialog);
        labelKinectCount->setObjectName(QStringLiteral("labelKinectCount"));

        gridLayout->addWidget(labelKinectCount, 0, 0, 1, 1);

        editKinectCount = new QLineEdit(KinectInitializeDialog);
        editKinectCount->setObjectName(QStringLiteral("editKinectCount"));
        editKinectCount->setReadOnly(true);

        gridLayout->addWidget(editKinectCount, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(KinectInitializeDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(KinectInitializeDialog);

        QMetaObject::connectSlotsByName(KinectInitializeDialog);
    } // setupUi

    void retranslateUi(QDialog *KinectInitializeDialog)
    {
        KinectInitializeDialog->setWindowTitle(QApplication::translate("KinectInitializeDialog", "Dialog", 0));
        labelKinectCount->setText(QApplication::translate("KinectInitializeDialog", "Number of connected Kinects :", 0));
    } // retranslateUi

};

namespace Ui {
    class KinectInitializeDialog: public Ui_KinectInitializeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KINECTINITIALIZEDIALOG_H

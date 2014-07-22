/********************************************************************************
** Form generated from reading UI file 'ImageWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEWIDGET_H
#define UI_IMAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *image;
    QHBoxLayout *horizontalLayout;
    QLabel *statusbar;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *ImageWidget)
    {
        if (ImageWidget->objectName().isEmpty())
            ImageWidget->setObjectName(QStringLiteral("ImageWidget"));
        ImageWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(ImageWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        image = new QLabel(ImageWidget);
        image->setObjectName(QStringLiteral("image"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image->sizePolicy().hasHeightForWidth());
        image->setSizePolicy(sizePolicy);
        image->setScaledContents(true);
        image->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(image);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        statusbar = new QLabel(ImageWidget);
        statusbar->setObjectName(QStringLiteral("statusbar"));

        horizontalLayout->addWidget(statusbar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ImageWidget);

        QMetaObject::connectSlotsByName(ImageWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageWidget)
    {
        ImageWidget->setWindowTitle(QApplication::translate("ImageWidget", "Form", 0));
        image->setText(QString());
        statusbar->setText(QApplication::translate("ImageWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageWidget: public Ui_ImageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEWIDGET_H

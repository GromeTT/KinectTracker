/********************************************************************************
** Form generated from reading UI file 'ImageAnalysisDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEANALYSISDIALOG_H
#define UI_IMAGEANALYSISDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "C:\Projekte\C++\Kinect_Tracker\KinectTracker\inc\ImageWidget\inc\ImageWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ImageAnalysisDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    ImageWidget *imageWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *loadButton;
    QPushButton *saveRoiButton;
    QPushButton *computeHistogramButton;
    QPushButton *saveHistogramButton;
    QPushButton *calculateSkinRegionButton;
    QPushButton *showCurrentHistogramButton;
    QPushButton *showSaveHistogramButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *thresholdLabel;
    QDoubleSpinBox *thresholdSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *ImageAnalysisDialog)
    {
        if (ImageAnalysisDialog->objectName().isEmpty())
            ImageAnalysisDialog->setObjectName(QStringLiteral("ImageAnalysisDialog"));
        ImageAnalysisDialog->resize(606, 554);
        verticalLayout_2 = new QVBoxLayout(ImageAnalysisDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        imageWidget = new ImageWidget(ImageAnalysisDialog);
        imageWidget->setObjectName(QStringLiteral("imageWidget"));
        imageWidget->setMinimumSize(QSize(250, 250));

        horizontalLayout->addWidget(imageWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        loadButton = new QPushButton(ImageAnalysisDialog);
        loadButton->setObjectName(QStringLiteral("loadButton"));

        verticalLayout->addWidget(loadButton);

        saveRoiButton = new QPushButton(ImageAnalysisDialog);
        saveRoiButton->setObjectName(QStringLiteral("saveRoiButton"));

        verticalLayout->addWidget(saveRoiButton);

        computeHistogramButton = new QPushButton(ImageAnalysisDialog);
        computeHistogramButton->setObjectName(QStringLiteral("computeHistogramButton"));

        verticalLayout->addWidget(computeHistogramButton);

        saveHistogramButton = new QPushButton(ImageAnalysisDialog);
        saveHistogramButton->setObjectName(QStringLiteral("saveHistogramButton"));

        verticalLayout->addWidget(saveHistogramButton);

        calculateSkinRegionButton = new QPushButton(ImageAnalysisDialog);
        calculateSkinRegionButton->setObjectName(QStringLiteral("calculateSkinRegionButton"));

        verticalLayout->addWidget(calculateSkinRegionButton);

        showCurrentHistogramButton = new QPushButton(ImageAnalysisDialog);
        showCurrentHistogramButton->setObjectName(QStringLiteral("showCurrentHistogramButton"));

        verticalLayout->addWidget(showCurrentHistogramButton);

        showSaveHistogramButton = new QPushButton(ImageAnalysisDialog);
        showSaveHistogramButton->setObjectName(QStringLiteral("showSaveHistogramButton"));

        verticalLayout->addWidget(showSaveHistogramButton);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        thresholdLabel = new QLabel(ImageAnalysisDialog);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));

        horizontalLayout_4->addWidget(thresholdLabel);

        thresholdSpinBox = new QDoubleSpinBox(ImageAnalysisDialog);
        thresholdSpinBox->setObjectName(QStringLiteral("thresholdSpinBox"));
        thresholdSpinBox->setMaximum(255);

        horizontalLayout_4->addWidget(thresholdSpinBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(ImageAnalysisDialog);

        QMetaObject::connectSlotsByName(ImageAnalysisDialog);
    } // setupUi

    void retranslateUi(QWidget *ImageAnalysisDialog)
    {
        ImageAnalysisDialog->setWindowTitle(QApplication::translate("ImageAnalysisDialog", "Form", 0));
        loadButton->setText(QApplication::translate("ImageAnalysisDialog", "Load image", 0));
        saveRoiButton->setText(QApplication::translate("ImageAnalysisDialog", "Save ROI", 0));
        computeHistogramButton->setText(QApplication::translate("ImageAnalysisDialog", "Compute backprojection", 0));
        saveHistogramButton->setText(QApplication::translate("ImageAnalysisDialog", "Save histogram", 0));
        calculateSkinRegionButton->setText(QApplication::translate("ImageAnalysisDialog", "Show skin color pixels", 0));
        showCurrentHistogramButton->setText(QApplication::translate("ImageAnalysisDialog", "Show current histogram", 0));
        showSaveHistogramButton->setText(QApplication::translate("ImageAnalysisDialog", "Show saved histogram", 0));
        thresholdLabel->setText(QApplication::translate("ImageAnalysisDialog", "Threshold", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageAnalysisDialog: public Ui_ImageAnalysisDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEANALYSISDIALOG_H

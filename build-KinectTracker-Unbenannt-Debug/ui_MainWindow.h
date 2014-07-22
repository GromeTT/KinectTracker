/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionOpenKinectStream;
    QAction *actionRGBViewer;
    QAction *actionOpenGLRender;
    QAction *actionTakeScreenshot;
    QAction *actionSASDMode;
    QAction *actionSABSSDMode;
    QAction *actionStartCapturing;
    QAction *actionImageAnalysisTool;
    QAction *actionReset;
    QAction *actionSaveAsPointCloud;
    QAction *actionInitializeFloor;
    QAction *actionLoadPointCloud;
    QAction *actionProcessingEnabled;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *windowMenu;
    QMenu *editMenu;
    QMenu *menuAnalysis;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(616, 496);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionOpenKinectStream = new QAction(MainWindow);
        actionOpenKinectStream->setObjectName(QStringLiteral("actionOpenKinectStream"));
        actionRGBViewer = new QAction(MainWindow);
        actionRGBViewer->setObjectName(QStringLiteral("actionRGBViewer"));
        actionRGBViewer->setCheckable(true);
        actionOpenGLRender = new QAction(MainWindow);
        actionOpenGLRender->setObjectName(QStringLiteral("actionOpenGLRender"));
        actionOpenGLRender->setCheckable(true);
        actionTakeScreenshot = new QAction(MainWindow);
        actionTakeScreenshot->setObjectName(QStringLiteral("actionTakeScreenshot"));
        actionSASDMode = new QAction(MainWindow);
        actionSASDMode->setObjectName(QStringLiteral("actionSASDMode"));
        actionSASDMode->setCheckable(true);
        actionSABSSDMode = new QAction(MainWindow);
        actionSABSSDMode->setObjectName(QStringLiteral("actionSABSSDMode"));
        actionSABSSDMode->setCheckable(true);
        actionStartCapturing = new QAction(MainWindow);
        actionStartCapturing->setObjectName(QStringLiteral("actionStartCapturing"));
        actionStartCapturing->setCheckable(true);
        actionImageAnalysisTool = new QAction(MainWindow);
        actionImageAnalysisTool->setObjectName(QStringLiteral("actionImageAnalysisTool"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionSaveAsPointCloud = new QAction(MainWindow);
        actionSaveAsPointCloud->setObjectName(QStringLiteral("actionSaveAsPointCloud"));
        actionInitializeFloor = new QAction(MainWindow);
        actionInitializeFloor->setObjectName(QStringLiteral("actionInitializeFloor"));
        actionLoadPointCloud = new QAction(MainWindow);
        actionLoadPointCloud->setObjectName(QStringLiteral("actionLoadPointCloud"));
        actionProcessingEnabled = new QAction(MainWindow);
        actionProcessingEnabled->setObjectName(QStringLiteral("actionProcessingEnabled"));
        actionProcessingEnabled->setCheckable(true);
        actionProcessingEnabled->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 616, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        windowMenu = new QMenu(menuBar);
        windowMenu->setObjectName(QStringLiteral("windowMenu"));
        editMenu = new QMenu(menuBar);
        editMenu->setObjectName(QStringLiteral("editMenu"));
        menuAnalysis = new QMenu(menuBar);
        menuAnalysis->setObjectName(QStringLiteral("menuAnalysis"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(editMenu->menuAction());
        menuBar->addAction(menuAnalysis->menuAction());
        menuBar->addAction(windowMenu->menuAction());
        menuDatei->addAction(actionOpenKinectStream);
        menuDatei->addSeparator();
        menuDatei->addAction(actionQuit);
        windowMenu->addAction(actionRGBViewer);
        windowMenu->addAction(actionOpenGLRender);
        editMenu->addAction(actionStartCapturing);
        editMenu->addAction(actionProcessingEnabled);
        editMenu->addSeparator();
        editMenu->addAction(actionTakeScreenshot);
        editMenu->addSeparator();
        editMenu->addAction(actionSaveAsPointCloud);
        editMenu->addAction(actionLoadPointCloud);
        editMenu->addAction(actionInitializeFloor);
        editMenu->addSeparator();
        editMenu->addAction(actionReset);
        menuAnalysis->addAction(actionSASDMode);
        menuAnalysis->addAction(actionSABSSDMode);
        menuAnalysis->addSeparator();
        menuAnalysis->addAction(actionImageAnalysisTool);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionOpenKinectStream->setText(QApplication::translate("MainWindow", "Establish connection to kinect...", 0));
        actionRGBViewer->setText(QApplication::translate("MainWindow", "RGBViewer", 0));
        actionOpenGLRender->setText(QApplication::translate("MainWindow", "OpenGLRender", 0));
        actionTakeScreenshot->setText(QApplication::translate("MainWindow", "Take screenshot", 0));
        actionSASDMode->setText(QApplication::translate("MainWindow", "SASDMode", 0));
        actionSABSSDMode->setText(QApplication::translate("MainWindow", "SABSSDMode", 0));
        actionStartCapturing->setText(QApplication::translate("MainWindow", "Start Capturing", 0));
#ifndef QT_NO_TOOLTIP
        actionStartCapturing->setToolTip(QApplication::translate("MainWindow", "Start/Stop Capturing", 0));
#endif // QT_NO_TOOLTIP
        actionImageAnalysisTool->setText(QApplication::translate("MainWindow", "Image Analysis Tool", 0));
        actionReset->setText(QApplication::translate("MainWindow", "Reset ", 0));
        actionSaveAsPointCloud->setText(QApplication::translate("MainWindow", "Save as PointCloud", 0));
        actionInitializeFloor->setText(QApplication::translate("MainWindow", "Initialize Floor", 0));
        actionLoadPointCloud->setText(QApplication::translate("MainWindow", "Load Point Cloud", 0));
        actionProcessingEnabled->setText(QApplication::translate("MainWindow", "Processing enabled", 0));
#ifndef QT_NO_TOOLTIP
        actionProcessingEnabled->setToolTip(QApplication::translate("MainWindow", "Processing enabled", 0));
#endif // QT_NO_TOOLTIP
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", 0));
        windowMenu->setTitle(QApplication::translate("MainWindow", "Window", 0));
        editMenu->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuAnalysis->setTitle(QApplication::translate("MainWindow", "Analysis", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'usbcamera.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USBCAMERA_H
#define UI_USBCAMERA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_USBCameraClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *USBCameraClass)
    {
        if (USBCameraClass->objectName().isEmpty())
            USBCameraClass->setObjectName(QString::fromUtf8("USBCameraClass"));
        USBCameraClass->resize(600, 400);
        menuBar = new QMenuBar(USBCameraClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        USBCameraClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(USBCameraClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        USBCameraClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(USBCameraClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        USBCameraClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(USBCameraClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        USBCameraClass->setStatusBar(statusBar);

        retranslateUi(USBCameraClass);

        QMetaObject::connectSlotsByName(USBCameraClass);
    } // setupUi

    void retranslateUi(QMainWindow *USBCameraClass)
    {
        USBCameraClass->setWindowTitle(QApplication::translate("USBCameraClass", "USBCamera", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class USBCameraClass: public Ui_USBCameraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBCAMERA_H

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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_USBCameraClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *open;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *close;
    QHBoxLayout *layout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *openstorage;
    QPushButton *closestorage;
    QHBoxLayout *layout1;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *USBCameraClass)
    {
        if (USBCameraClass->objectName().isEmpty())
            USBCameraClass->setObjectName(QString::fromUtf8("USBCameraClass"));
        USBCameraClass->resize(600, 400);
        centralWidget = new QWidget(USBCameraClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        open = new QPushButton(centralWidget);
        open->setObjectName(QString::fromUtf8("open"));

        horizontalLayout->addWidget(open);

        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));

        horizontalLayout->addWidget(start);

        stop = new QPushButton(centralWidget);
        stop->setObjectName(QString::fromUtf8("stop"));

        horizontalLayout->addWidget(stop);

        close = new QPushButton(centralWidget);
        close->setObjectName(QString::fromUtf8("close"));

        horizontalLayout->addWidget(close);


        verticalLayout_2->addLayout(horizontalLayout);

        layout = new QHBoxLayout();
        layout->setSpacing(6);
        layout->setObjectName(QString::fromUtf8("layout"));

        verticalLayout_2->addLayout(layout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        openstorage = new QPushButton(centralWidget);
        openstorage->setObjectName(QString::fromUtf8("openstorage"));

        horizontalLayout_2->addWidget(openstorage);

        closestorage = new QPushButton(centralWidget);
        closestorage->setObjectName(QString::fromUtf8("closestorage"));

        horizontalLayout_2->addWidget(closestorage);


        verticalLayout_2->addLayout(horizontalLayout_2);

        layout1 = new QHBoxLayout();
        layout1->setSpacing(6);
        layout1->setObjectName(QString::fromUtf8("layout1"));

        verticalLayout_2->addLayout(layout1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        USBCameraClass->setCentralWidget(centralWidget);

        retranslateUi(USBCameraClass);

        QMetaObject::connectSlotsByName(USBCameraClass);
    } // setupUi

    void retranslateUi(QMainWindow *USBCameraClass)
    {
        USBCameraClass->setWindowTitle(QApplication::translate("USBCameraClass", "USBCamera", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("USBCameraClass", "Open Sensor", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("USBCameraClass", "Start", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("USBCameraClass", "Stop", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("USBCameraClass", "Close Sensor", 0, QApplication::UnicodeUTF8));
        openstorage->setText(QApplication::translate("USBCameraClass", "Open Storage", 0, QApplication::UnicodeUTF8));
        closestorage->setText(QApplication::translate("USBCameraClass", "Close Storage", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class USBCameraClass: public Ui_USBCameraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBCAMERA_H

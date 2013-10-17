/********************************************************************************
** Form generated from reading UI file 'tsukuba.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TSUKUBA_H
#define UI_TSUKUBA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TsukubaClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *open;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *close;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *layout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TsukubaClass)
    {
        if (TsukubaClass->objectName().isEmpty())
            TsukubaClass->setObjectName(QString::fromUtf8("TsukubaClass"));
        TsukubaClass->resize(641, 478);
        centralWidget = new QWidget(TsukubaClass);
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

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 621, 370));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        layout = new QVBoxLayout();
        layout->setSpacing(6);
        layout->setObjectName(QString::fromUtf8("layout"));

        verticalLayout_3->addLayout(layout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        TsukubaClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TsukubaClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 641, 23));
        TsukubaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TsukubaClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TsukubaClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TsukubaClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TsukubaClass->setStatusBar(statusBar);

        retranslateUi(TsukubaClass);

        QMetaObject::connectSlotsByName(TsukubaClass);
    } // setupUi

    void retranslateUi(QMainWindow *TsukubaClass)
    {
        TsukubaClass->setWindowTitle(QApplication::translate("TsukubaClass", "Tsukuba", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("TsukubaClass", "Open", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("TsukubaClass", "Start", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("TsukubaClass", "Stop", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("TsukubaClass", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TsukubaClass: public Ui_TsukubaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TSUKUBA_H

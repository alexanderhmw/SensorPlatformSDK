/********************************************************************************
** Form generated from reading UI file 'poss_goblin_collector.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSS_GOBLIN_COLLECTOR_H
#define UI_POSS_GOBLIN_COLLECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_POSS_Goblin_CollectorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *POSS_Goblin_CollectorClass)
    {
        if (POSS_Goblin_CollectorClass->objectName().isEmpty())
            POSS_Goblin_CollectorClass->setObjectName(QString::fromUtf8("POSS_Goblin_CollectorClass"));
        POSS_Goblin_CollectorClass->resize(600, 400);
        centralWidget = new QWidget(POSS_Goblin_CollectorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hlayout = new QHBoxLayout();
        hlayout->setSpacing(6);
        hlayout->setObjectName(QString::fromUtf8("hlayout"));
        vlayout = new QVBoxLayout();
        vlayout->setSpacing(6);
        vlayout->setObjectName(QString::fromUtf8("vlayout"));

        hlayout->addLayout(vlayout);


        verticalLayout->addLayout(hlayout);

        POSS_Goblin_CollectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(POSS_Goblin_CollectorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        POSS_Goblin_CollectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(POSS_Goblin_CollectorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        POSS_Goblin_CollectorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(POSS_Goblin_CollectorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        POSS_Goblin_CollectorClass->setStatusBar(statusBar);

        retranslateUi(POSS_Goblin_CollectorClass);

        QMetaObject::connectSlotsByName(POSS_Goblin_CollectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *POSS_Goblin_CollectorClass)
    {
        POSS_Goblin_CollectorClass->setWindowTitle(QApplication::translate("POSS_Goblin_CollectorClass", "POSS_Goblin_Collector", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class POSS_Goblin_CollectorClass: public Ui_POSS_Goblin_CollectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSS_GOBLIN_COLLECTOR_H

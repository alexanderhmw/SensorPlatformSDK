/********************************************************************************
** Form generated from reading UI file 'poss_goblin.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSS_GOBLIN_H
#define UI_POSS_GOBLIN_H

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

class Ui_POSS_GOBLINClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *POSS_GOBLINClass)
    {
        if (POSS_GOBLINClass->objectName().isEmpty())
            POSS_GOBLINClass->setObjectName(QString::fromUtf8("POSS_GOBLINClass"));
        POSS_GOBLINClass->resize(600, 400);
        menuBar = new QMenuBar(POSS_GOBLINClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        POSS_GOBLINClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(POSS_GOBLINClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        POSS_GOBLINClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(POSS_GOBLINClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        POSS_GOBLINClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(POSS_GOBLINClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        POSS_GOBLINClass->setStatusBar(statusBar);

        retranslateUi(POSS_GOBLINClass);

        QMetaObject::connectSlotsByName(POSS_GOBLINClass);
    } // setupUi

    void retranslateUi(QMainWindow *POSS_GOBLINClass)
    {
        POSS_GOBLINClass->setWindowTitle(QApplication::translate("POSS_GOBLINClass", "POSS_GOBLIN", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class POSS_GOBLINClass: public Ui_POSS_GOBLINClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSS_GOBLIN_H

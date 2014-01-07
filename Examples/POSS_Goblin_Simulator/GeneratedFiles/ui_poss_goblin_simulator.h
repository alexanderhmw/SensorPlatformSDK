/********************************************************************************
** Form generated from reading UI file 'poss_goblin_simulator.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSS_GOBLIN_SIMULATOR_H
#define UI_POSS_GOBLIN_SIMULATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_POSS_Goblin_SimulatorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *hlayout;
    QLineEdit *starttime;
    QPushButton *initial;
    QPushButton *start;
    QPushButton *stop;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *vlayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *POSS_Goblin_SimulatorClass)
    {
        if (POSS_Goblin_SimulatorClass->objectName().isEmpty())
            POSS_Goblin_SimulatorClass->setObjectName(QString::fromUtf8("POSS_Goblin_SimulatorClass"));
        POSS_Goblin_SimulatorClass->resize(600, 400);
        centralWidget = new QWidget(POSS_Goblin_SimulatorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        hlayout = new QHBoxLayout();
        hlayout->setSpacing(6);
        hlayout->setObjectName(QString::fromUtf8("hlayout"));
        starttime = new QLineEdit(centralWidget);
        starttime->setObjectName(QString::fromUtf8("starttime"));

        hlayout->addWidget(starttime);

        initial = new QPushButton(centralWidget);
        initial->setObjectName(QString::fromUtf8("initial"));

        hlayout->addWidget(initial);

        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));

        hlayout->addWidget(start);

        stop = new QPushButton(centralWidget);
        stop->setObjectName(QString::fromUtf8("stop"));

        hlayout->addWidget(stop);


        verticalLayout_2->addLayout(hlayout);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        vlayout = new QVBoxLayout();
        vlayout->setSpacing(6);
        vlayout->setObjectName(QString::fromUtf8("vlayout"));

        verticalLayout_3->addLayout(vlayout);


        verticalLayout_2->addWidget(frame);

        POSS_Goblin_SimulatorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(POSS_Goblin_SimulatorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        POSS_Goblin_SimulatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(POSS_Goblin_SimulatorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        POSS_Goblin_SimulatorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(POSS_Goblin_SimulatorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        POSS_Goblin_SimulatorClass->setStatusBar(statusBar);

        retranslateUi(POSS_Goblin_SimulatorClass);

        QMetaObject::connectSlotsByName(POSS_Goblin_SimulatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *POSS_Goblin_SimulatorClass)
    {
        POSS_Goblin_SimulatorClass->setWindowTitle(QApplication::translate("POSS_Goblin_SimulatorClass", "POSS_Goblin_Simulator", 0, QApplication::UnicodeUTF8));
        initial->setText(QApplication::translate("POSS_Goblin_SimulatorClass", "Initial", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("POSS_Goblin_SimulatorClass", "Start", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("POSS_Goblin_SimulatorClass", "Stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class POSS_Goblin_SimulatorClass: public Ui_POSS_Goblin_SimulatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSS_GOBLIN_SIMULATOR_H

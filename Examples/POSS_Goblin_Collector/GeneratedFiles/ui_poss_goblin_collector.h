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
#include <QtGui/QCheckBox>
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

class Ui_POSS_Goblin_CollectorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *order;
    QPushButton *startsend;
    QPushButton *stopsend;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *storecamera;
    QCheckBox *storelaser;
    QCheckBox *storeencoder;
    QCheckBox *storeodometry;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *openstorage;
    QPushButton *closestorage;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *POSS_Goblin_CollectorClass)
    {
        if (POSS_Goblin_CollectorClass->objectName().isEmpty())
            POSS_Goblin_CollectorClass->setObjectName(QString::fromUtf8("POSS_Goblin_CollectorClass"));
        POSS_Goblin_CollectorClass->resize(617, 460);
        centralWidget = new QWidget(POSS_Goblin_CollectorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        order = new QLineEdit(centralWidget);
        order->setObjectName(QString::fromUtf8("order"));

        horizontalLayout->addWidget(order);

        startsend = new QPushButton(centralWidget);
        startsend->setObjectName(QString::fromUtf8("startsend"));

        horizontalLayout->addWidget(startsend);

        stopsend = new QPushButton(centralWidget);
        stopsend->setObjectName(QString::fromUtf8("stopsend"));

        horizontalLayout->addWidget(stopsend);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        storecamera = new QCheckBox(centralWidget);
        storecamera->setObjectName(QString::fromUtf8("storecamera"));

        horizontalLayout_3->addWidget(storecamera);

        storelaser = new QCheckBox(centralWidget);
        storelaser->setObjectName(QString::fromUtf8("storelaser"));

        horizontalLayout_3->addWidget(storelaser);

        storeencoder = new QCheckBox(centralWidget);
        storeencoder->setObjectName(QString::fromUtf8("storeencoder"));

        horizontalLayout_3->addWidget(storeencoder);

        storeodometry = new QCheckBox(centralWidget);
        storeodometry->setObjectName(QString::fromUtf8("storeodometry"));

        horizontalLayout_3->addWidget(storeodometry);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        openstorage = new QPushButton(centralWidget);
        openstorage->setObjectName(QString::fromUtf8("openstorage"));

        horizontalLayout_2->addWidget(openstorage);

        closestorage = new QPushButton(centralWidget);
        closestorage->setObjectName(QString::fromUtf8("closestorage"));

        horizontalLayout_2->addWidget(closestorage);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        vlayout = new QVBoxLayout();
        vlayout->setSpacing(6);
        vlayout->setObjectName(QString::fromUtf8("vlayout"));
        hlayout = new QHBoxLayout();
        hlayout->setSpacing(6);
        hlayout->setObjectName(QString::fromUtf8("hlayout"));

        vlayout->addLayout(hlayout);


        verticalLayout_2->addLayout(vlayout);


        verticalLayout->addWidget(frame);

        POSS_Goblin_CollectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(POSS_Goblin_CollectorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 617, 23));
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
        startsend->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Start Send", 0, QApplication::UnicodeUTF8));
        stopsend->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Stop Send", 0, QApplication::UnicodeUTF8));
        storecamera->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Camera", 0, QApplication::UnicodeUTF8));
        storelaser->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Laser", 0, QApplication::UnicodeUTF8));
        storeencoder->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Encoder", 0, QApplication::UnicodeUTF8));
        storeodometry->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Odometry", 0, QApplication::UnicodeUTF8));
        openstorage->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Open Storage", 0, QApplication::UnicodeUTF8));
        closestorage->setText(QApplication::translate("POSS_Goblin_CollectorClass", "Close Storage", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class POSS_Goblin_CollectorClass: public Ui_POSS_Goblin_CollectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSS_GOBLIN_COLLECTOR_H

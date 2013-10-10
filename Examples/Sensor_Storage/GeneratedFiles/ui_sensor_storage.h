/********************************************************************************
** Form generated from reading UI file 'sensor_storage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSOR_STORAGE_H
#define UI_SENSOR_STORAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sensor_StorageClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *sensorclass;
    QLineEdit *sensorname;
    QLineEdit *buffersize;
    QPushButton *setsensor;
    QLineEdit *paramsfilename;
    QPushButton *browse;
    QPushButton *loadparams;
    QHBoxLayout *horizontalLayout;
    QPushButton *open;
    QLineEdit *interval;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *close;
    QHBoxLayout *sensorlayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *openstorage;
    QPushButton *closestorage;
    QHBoxLayout *storagelayout;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *Sensor_StorageClass)
    {
        if (Sensor_StorageClass->objectName().isEmpty())
            Sensor_StorageClass->setObjectName(QString::fromUtf8("Sensor_StorageClass"));
        Sensor_StorageClass->resize(719, 375);
        centralWidget = new QWidget(Sensor_StorageClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sensorclass = new QLineEdit(centralWidget);
        sensorclass->setObjectName(QString::fromUtf8("sensorclass"));

        horizontalLayout_3->addWidget(sensorclass);

        sensorname = new QLineEdit(centralWidget);
        sensorname->setObjectName(QString::fromUtf8("sensorname"));

        horizontalLayout_3->addWidget(sensorname);

        buffersize = new QLineEdit(centralWidget);
        buffersize->setObjectName(QString::fromUtf8("buffersize"));

        horizontalLayout_3->addWidget(buffersize);

        setsensor = new QPushButton(centralWidget);
        setsensor->setObjectName(QString::fromUtf8("setsensor"));

        horizontalLayout_3->addWidget(setsensor);

        paramsfilename = new QLineEdit(centralWidget);
        paramsfilename->setObjectName(QString::fromUtf8("paramsfilename"));

        horizontalLayout_3->addWidget(paramsfilename);

        browse = new QPushButton(centralWidget);
        browse->setObjectName(QString::fromUtf8("browse"));

        horizontalLayout_3->addWidget(browse);

        loadparams = new QPushButton(centralWidget);
        loadparams->setObjectName(QString::fromUtf8("loadparams"));

        horizontalLayout_3->addWidget(loadparams);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        open = new QPushButton(centralWidget);
        open->setObjectName(QString::fromUtf8("open"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(open->sizePolicy().hasHeightForWidth());
        open->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(open);

        interval = new QLineEdit(centralWidget);
        interval->setObjectName(QString::fromUtf8("interval"));

        horizontalLayout->addWidget(interval);

        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));
        sizePolicy.setHeightForWidth(start->sizePolicy().hasHeightForWidth());
        start->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(start);

        stop = new QPushButton(centralWidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        sizePolicy.setHeightForWidth(stop->sizePolicy().hasHeightForWidth());
        stop->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(stop);

        close = new QPushButton(centralWidget);
        close->setObjectName(QString::fromUtf8("close"));
        sizePolicy.setHeightForWidth(close->sizePolicy().hasHeightForWidth());
        close->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(close);


        verticalLayout->addLayout(horizontalLayout);

        sensorlayout = new QHBoxLayout();
        sensorlayout->setSpacing(6);
        sensorlayout->setObjectName(QString::fromUtf8("sensorlayout"));

        verticalLayout->addLayout(sensorlayout);

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

        storagelayout = new QHBoxLayout();
        storagelayout->setSpacing(6);
        storagelayout->setObjectName(QString::fromUtf8("storagelayout"));

        verticalLayout->addLayout(storagelayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        Sensor_StorageClass->setCentralWidget(centralWidget);

        retranslateUi(Sensor_StorageClass);

        QMetaObject::connectSlotsByName(Sensor_StorageClass);
    } // setupUi

    void retranslateUi(QMainWindow *Sensor_StorageClass)
    {
        Sensor_StorageClass->setWindowTitle(QApplication::translate("Sensor_StorageClass", "Sensor_Storage", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sensorclass->setToolTip(QApplication::translate("Sensor_StorageClass", "Sensor Class", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sensorname->setToolTip(QApplication::translate("Sensor_StorageClass", "Sensor Name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        buffersize->setToolTip(QApplication::translate("Sensor_StorageClass", "Data Buffer Size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buffersize->setText(QApplication::translate("Sensor_StorageClass", "10", 0, QApplication::UnicodeUTF8));
        setsensor->setText(QApplication::translate("Sensor_StorageClass", "Set Sensor", 0, QApplication::UnicodeUTF8));
        paramsfilename->setText(QApplication::translate("Sensor_StorageClass", "config.xml", 0, QApplication::UnicodeUTF8));
        browse->setText(QApplication::translate("Sensor_StorageClass", "Browse...", 0, QApplication::UnicodeUTF8));
        loadparams->setText(QApplication::translate("Sensor_StorageClass", "Load", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("Sensor_StorageClass", "Open Sensor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        interval->setToolTip(QApplication::translate("Sensor_StorageClass", "Timer Interval (msec)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        interval->setText(QApplication::translate("Sensor_StorageClass", "50", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("Sensor_StorageClass", "Start", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("Sensor_StorageClass", "Stop", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("Sensor_StorageClass", "Close Sensor", 0, QApplication::UnicodeUTF8));
        openstorage->setText(QApplication::translate("Sensor_StorageClass", "Open Storage", 0, QApplication::UnicodeUTF8));
        closestorage->setText(QApplication::translate("Sensor_StorageClass", "Close Storage", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Sensor_StorageClass: public Ui_Sensor_StorageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSOR_STORAGE_H

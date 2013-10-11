/********************************************************************************
** Form generated from reading UI file 'funcmoudlecreator.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCMOUDLECREATOR_H
#define UI_FUNCMOUDLECREATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FuncMoudleCreatorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *projectdir;
    QPushButton *browseprojectdir;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *funcmodulename;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *funclibrarydir;
    QPushButton *browsefunclibrarydirectory;
    QGridLayout *gridLayout;
    QCheckBox *sensor;
    QCheckBox *sensorwidget;
    QCheckBox *storage;
    QCheckBox *storagewidget;
    QCheckBox *processor;
    QCheckBox *processorwidget;
    QCheckBox *fusion;
    QCheckBox *fusionwidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *create;

    void setupUi(QMainWindow *FuncMoudleCreatorClass)
    {
        if (FuncMoudleCreatorClass->objectName().isEmpty())
            FuncMoudleCreatorClass->setObjectName(QString::fromUtf8("FuncMoudleCreatorClass"));
        FuncMoudleCreatorClass->resize(494, 227);
        centralWidget = new QWidget(FuncMoudleCreatorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        projectdir = new QLineEdit(centralWidget);
        projectdir->setObjectName(QString::fromUtf8("projectdir"));

        horizontalLayout->addWidget(projectdir);

        browseprojectdir = new QPushButton(centralWidget);
        browseprojectdir->setObjectName(QString::fromUtf8("browseprojectdir"));

        horizontalLayout->addWidget(browseprojectdir);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        funcmodulename = new QLineEdit(centralWidget);
        funcmodulename->setObjectName(QString::fromUtf8("funcmodulename"));

        horizontalLayout_3->addWidget(funcmodulename);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        funclibrarydir = new QLineEdit(centralWidget);
        funclibrarydir->setObjectName(QString::fromUtf8("funclibrarydir"));

        horizontalLayout_4->addWidget(funclibrarydir);

        browsefunclibrarydirectory = new QPushButton(centralWidget);
        browsefunclibrarydirectory->setObjectName(QString::fromUtf8("browsefunclibrarydirectory"));

        horizontalLayout_4->addWidget(browsefunclibrarydirectory);


        verticalLayout->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sensor = new QCheckBox(centralWidget);
        sensor->setObjectName(QString::fromUtf8("sensor"));

        gridLayout->addWidget(sensor, 0, 0, 1, 1);

        sensorwidget = new QCheckBox(centralWidget);
        sensorwidget->setObjectName(QString::fromUtf8("sensorwidget"));

        gridLayout->addWidget(sensorwidget, 0, 1, 1, 1);

        storage = new QCheckBox(centralWidget);
        storage->setObjectName(QString::fromUtf8("storage"));

        gridLayout->addWidget(storage, 1, 0, 1, 1);

        storagewidget = new QCheckBox(centralWidget);
        storagewidget->setObjectName(QString::fromUtf8("storagewidget"));

        gridLayout->addWidget(storagewidget, 1, 1, 1, 1);

        processor = new QCheckBox(centralWidget);
        processor->setObjectName(QString::fromUtf8("processor"));

        gridLayout->addWidget(processor, 2, 0, 1, 1);

        processorwidget = new QCheckBox(centralWidget);
        processorwidget->setObjectName(QString::fromUtf8("processorwidget"));

        gridLayout->addWidget(processorwidget, 2, 1, 1, 1);

        fusion = new QCheckBox(centralWidget);
        fusion->setObjectName(QString::fromUtf8("fusion"));

        gridLayout->addWidget(fusion, 3, 0, 1, 1);

        fusionwidget = new QCheckBox(centralWidget);
        fusionwidget->setObjectName(QString::fromUtf8("fusionwidget"));

        gridLayout->addWidget(fusionwidget, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        create = new QPushButton(centralWidget);
        create->setObjectName(QString::fromUtf8("create"));

        horizontalLayout_2->addWidget(create);


        verticalLayout->addLayout(horizontalLayout_2);

        FuncMoudleCreatorClass->setCentralWidget(centralWidget);

        retranslateUi(FuncMoudleCreatorClass);

        QMetaObject::connectSlotsByName(FuncMoudleCreatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *FuncMoudleCreatorClass)
    {
        FuncMoudleCreatorClass->setWindowTitle(QApplication::translate("FuncMoudleCreatorClass", "FuncMoudleCreator", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FuncMoudleCreatorClass", "Project Directory:", 0, QApplication::UnicodeUTF8));
        browseprojectdir->setText(QApplication::translate("FuncMoudleCreatorClass", "Browse...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FuncMoudleCreatorClass", "FuncModule Name:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FuncMoudleCreatorClass", "FuncLibrary Directory:", 0, QApplication::UnicodeUTF8));
        browsefunclibrarydirectory->setText(QApplication::translate("FuncMoudleCreatorClass", "Browse...", 0, QApplication::UnicodeUTF8));
        sensor->setText(QApplication::translate("FuncMoudleCreatorClass", "sensor", 0, QApplication::UnicodeUTF8));
        sensorwidget->setText(QApplication::translate("FuncMoudleCreatorClass", "sensorwidget", 0, QApplication::UnicodeUTF8));
        storage->setText(QApplication::translate("FuncMoudleCreatorClass", "storage", 0, QApplication::UnicodeUTF8));
        storagewidget->setText(QApplication::translate("FuncMoudleCreatorClass", "storagewidget", 0, QApplication::UnicodeUTF8));
        processor->setText(QApplication::translate("FuncMoudleCreatorClass", "processor", 0, QApplication::UnicodeUTF8));
        processorwidget->setText(QApplication::translate("FuncMoudleCreatorClass", "processorwidget", 0, QApplication::UnicodeUTF8));
        fusion->setText(QApplication::translate("FuncMoudleCreatorClass", "fusion", 0, QApplication::UnicodeUTF8));
        fusionwidget->setText(QApplication::translate("FuncMoudleCreatorClass", "fusionwidget", 0, QApplication::UnicodeUTF8));
        create->setText(QApplication::translate("FuncMoudleCreatorClass", "Create Files", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FuncMoudleCreatorClass: public Ui_FuncMoudleCreatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCMOUDLECREATOR_H

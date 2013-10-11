/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *projectdir;
    QPushButton *browseprojectdir;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *funclibrarydir;
    QPushButton *browsefunclibrarydir;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *funcmodulename;
    QPushButton *load;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *nodelist;
    QListWidget *nodewidgetlist;
    QPushButton *create;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(470, 272);
        centralWidget = new QWidget(MainWindow);
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

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        funclibrarydir = new QLineEdit(centralWidget);
        funclibrarydir->setObjectName(QString::fromUtf8("funclibrarydir"));

        horizontalLayout_2->addWidget(funclibrarydir);

        browsefunclibrarydir = new QPushButton(centralWidget);
        browsefunclibrarydir->setObjectName(QString::fromUtf8("browsefunclibrarydir"));

        horizontalLayout_2->addWidget(browsefunclibrarydir);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        funcmodulename = new QLineEdit(centralWidget);
        funcmodulename->setObjectName(QString::fromUtf8("funcmodulename"));

        horizontalLayout_3->addWidget(funcmodulename);

        load = new QPushButton(centralWidget);
        load->setObjectName(QString::fromUtf8("load"));

        horizontalLayout_3->addWidget(load);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        nodelist = new QListWidget(centralWidget);
        nodelist->setObjectName(QString::fromUtf8("nodelist"));
        nodelist->setViewMode(QListView::ListMode);
        nodelist->setSelectionRectVisible(true);

        horizontalLayout_4->addWidget(nodelist);

        nodewidgetlist = new QListWidget(centralWidget);
        nodewidgetlist->setObjectName(QString::fromUtf8("nodewidgetlist"));

        horizontalLayout_4->addWidget(nodewidgetlist);


        verticalLayout->addLayout(horizontalLayout_4);

        create = new QPushButton(centralWidget);
        create->setObjectName(QString::fromUtf8("create"));

        verticalLayout->addWidget(create);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Project Dir:", 0, QApplication::UnicodeUTF8));
        browseprojectdir->setText(QApplication::translate("MainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "FuncLibrary Dir:", 0, QApplication::UnicodeUTF8));
        browsefunclibrarydir->setText(QApplication::translate("MainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "FuncModule Name:", 0, QApplication::UnicodeUTF8));
        load->setText(QApplication::translate("MainWindow", "Load Config", 0, QApplication::UnicodeUTF8));
        create->setText(QApplication::translate("MainWindow", "Create files", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

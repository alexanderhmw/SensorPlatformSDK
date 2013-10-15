#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <qxmlstream.h>
#include <QCheckBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QList>
#include <QVector>
#include <fstream>
#include <string>
#include <iostream>
#include <ios>
#include <qfileinfo.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_browseprojectdir_clicked();

    void on_browsefunclibrarydir_clicked();

    void on_load_clicked();

    void on_create_clicked();

private:
    Ui::MainWindow *ui;
    QFile configfile;
};

#endif // MAINWINDOW_H

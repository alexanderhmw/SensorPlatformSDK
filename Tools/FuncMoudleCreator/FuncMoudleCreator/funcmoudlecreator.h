#ifndef FUNCMOUDLECREATOR_H
#define FUNCMOUDLECREATOR_H

#include <QtGui/QMainWindow>
#include "ui_funcmoudlecreator.h"

#include<qfiledialog.h>
#include<qdir.h>
#include<qvector.h>
#include<qstring.h>
#include<qfile.h>

class FuncMoudleCreator : public QMainWindow
{
	Q_OBJECT

public:
	FuncMoudleCreator(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FuncMoudleCreator();

private slots:
    void on_browseprojectdir_clicked();

    void on_browsefunclibrarydirectory_clicked();

    void on_create_clicked();

    void on_sensor_clicked(bool checked);

    void on_sensorwidget_clicked(bool checked);

    void on_storage_clicked(bool checked);

    void on_storagewidget_clicked(bool checked);

    void on_processor_clicked(bool checked);

    void on_processorwidget_clicked(bool checked);

    void on_fusion_clicked(bool checked);

    void on_fusionwidget_clicked(bool checked);

private:
	Ui::FuncMoudleCreatorClass ui;
    QVector<QString> nodelist;
	QVector<QString> outputfiles;
};

#endif // FUNCMOUDLECREATOR_H

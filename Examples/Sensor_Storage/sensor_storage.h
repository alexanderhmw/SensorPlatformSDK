#ifndef SENSOR_STORAGE_H
#define SENSOR_STORAGE_H

#include<qmainwindow.h>
#include "ui_sensor_storage.h"
#include<Sensor\sensor.h>
#include<Sensor\sensorwidget.h>
#include<Storage\storage.h>
#include<Storage\storagewidget.h>
#include<Communicator\communicator.h>
#include<Communicator\communicatorwidget.h>
#include<qtimer.h>
#include <qthread.h>
#include<qfiledialog.h>

#define COMMUNICATOR

class Sensor_Storage : public QMainWindow
{
	Q_OBJECT

public:
	Sensor_Storage(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Sensor_Storage();

private:
	Ui::Sensor_StorageClass ui;

public:
	bool flag;

	QTimer timer;
	QThread sensorthread;
	QThread storagethread;

#ifndef COMMUNICATOR
	Sensor * sensor;
	SensorWidget * sensorwidget;
#else
	Communicator * sensor;
	CommunicatorWidget * sensorwidget;
#endif
	Storage * storage;
	StorageWidget * storagewidget;
public slots:
	void setSensor();
	void browseParamsFile();
	void loadParamsFile();
	void startSensor();
	void stopSensor();
};

#endif // SENSOR_STORAGE_H

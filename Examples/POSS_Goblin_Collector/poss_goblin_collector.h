#ifndef POSS_GOBLIN_COLLECTOR_H
#define POSS_GOBLIN_COLLECTOR_H

#include <QtGui/QMainWindow>
#include "ui_poss_goblin_collector.h"

#include<Sensor\sensor.h>
#include<Sensor\sensorwidget.h>
#include<Communicator\communicator.h>
#include<Communicator\communicatorwidget.h>
#include<Processor\processor.h>
#include<Storage\storage.h>
#include<Storage\storagewidget.h>
#include <qthread.h>
#include<qtimer.h>
#include <qbytearray.h>
#include<qfile.h>
#include<qstring.h>

struct CONTROLORDER
{
	QByteArray order;
};

struct URGSTORAGEPARAMS	//storage parameters
{
	QFile file;
	QString storagepath;
	QString extension;
};

class POSS_Goblin_Collector : public QMainWindow
{
	Q_OBJECT

public:
	POSS_Goblin_Collector(QWidget *parent = 0, Qt::WFlags flags = 0);
	~POSS_Goblin_Collector();

private:
	Ui::POSS_Goblin_CollectorClass ui;
public:
	Sensor * camera;
	SensorWidget * camerawidget;
	Storage * camerastorage;
	QThread camerathread;
	QTimer cameratimer;

	Sensor * laser;
	SensorWidget * laserwidget;
	Storage * laserstorage;
	QThread laserthread;
	QTimer lasertimer;

	Communicator * encoder;
	CommunicatorWidget * encoderwidget;
	Storage * encoderstorage;
	QThread encoderthread;
	QTimer controltimer;

	Processor * odometry;
	Storage * odometrystorage;
	StorageWidget * odometrystoragewidget;
	QThread odometrythread;
	
signals:
	void sendControlOrderSignal(void * order);
public slots:
	void sendControlOrderSlot();
	//send order via comport
	void startSendSlot();
	void stopSendSlot();
	//
	void openStorageSlot();
	void closeStorageSlot();
};

#endif // POSS_GOBLIN_COLLECTOR_H

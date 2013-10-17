#ifndef TSUKUBA_H
#define TSUKUBA_H

#include <QtGui/QMainWindow>
#include "ui_tsukuba.h"
#include<Sensor\sensor.h>
#include<Sensor\sensorwidget.h>
#include<Communicator\communicator.h>
#include<Communicator\communicatorwidget.h>
#include<Storage\storage.h>
#include<Storage\storagewidget.h>
#include<qtimer.h>
#include <qthread.h>

class Tsukuba : public QMainWindow
{
	Q_OBJECT

public:
	Tsukuba(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Tsukuba();

private:
	Ui::TsukubaClass ui;

	QTimer URGtimer;
	QTimer Xtiontimer;

	QThread URGthread;
	QThread Xtionthread;
	QThread UDPReceiverthread;
	QThread Encoderthread;

	Sensor * URG;
	Sensor * Xtion;
	Sensor * UDPReceiver;
	Communicator * Encoder;

	Storage * URGstorage;
	Storage * Xtionstorage;
	Storage * UDPReceiverstorage;
	Storage * Encoderstorage;

	SensorWidget * URGwidget;
	SensorWidget * Xtionwidget;
	SensorWidget * UDPReceiverwidget;
	CommunicatorWidget * Encoderwidget;

	StorageWidget * URGstoragewidget;
	StorageWidget * Xtionstoragewidget;
	StorageWidget * UDPReceiverstoragewidget;
	StorageWidget * Encoderstoragewidget;
signals:
	void startSignal();
	void stopSignal();
};

#endif // TSUKUBA_H

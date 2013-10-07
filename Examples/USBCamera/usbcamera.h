#ifndef USBCAMERA_H
#define USBCAMERA_H

#include <QtGui/QMainWindow>
#include "ui_usbcamera.h"
#include<Sensor\sensor.h>
#include<Sensor\sensorwidget.h>
#include<Storage\storage.h>
#include<qtimer.h>
#include<qdatetime.h>
#include <opencv2\opencv.hpp>
#include <qthread.h>
#include <qboxlayout.h>

class USBCamera : public QMainWindow
{
	Q_OBJECT

public:
	USBCamera(QWidget *parent = 0, Qt::WFlags flags = 0);
	~USBCamera();

private:
	Ui::USBCameraClass ui;
public:
	Sensor * sensor1;
	Sensor * sensor2;
	QTimer timer1;
	QTimer timer2;
	Storage * storage1;
	Storage * storage2;
	SensorWidget * sensorwidget1;
	SensorWidget * sensorwidget2;
	QThread thread1;
	QThread thread2;
};

#endif // USBCAMERA_H

#ifndef USBCAMERA_H
#define USBCAMERA_H

#include <QtGui/QMainWindow>
#include "ui_usbcamera.h"
#include<sensor.h>
#include<qtimer.h>
#include<qdatetime.h>
#include <opencv2\opencv.hpp>

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
	Sensor * sensor3;
	QTimer timer1;
	QTimer timer2;
	QTimer timer3;
public slots:
	void showImage1(void * data);
	void showImage2(void * data);
	void showImage3(void * data);
};

#endif // USBCAMERA_H

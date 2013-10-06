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
	Sensor * sensor;
	QTimer timer;
public slots:
	void showImage(void * data);
};

#endif // USBCAMERA_H

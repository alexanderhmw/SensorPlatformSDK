#include "usbcamera.h"

#pragma comment(lib,"Sensor.lib")
#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")

USBCamera::USBCamera(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QString configfilename=QString("C:/PossDemo/GitHub/HMW-Alexander/SensorPlatformSDK/Examples/USBCamera/usbcamera.xml");

	sensor1=new Sensor("USBCamera","camera1");
	sensor1->loadParamsSlot(configfilename);
	sensor1->openSensorSlot();
	sensor1->connectCaptureDataSignal(&timer1,SIGNAL(timeout()));
	sensor1->connectDataCaptureSlot(this,SLOT(showImage1(void *)));

	sensor2=new Sensor("USBCamera","camera2");
	sensor2->loadParamsSlot(configfilename);
	sensor2->openSensorSlot();
	sensor2->connectCaptureDataSignal(&timer2,SIGNAL(timeout()));
	sensor2->connectDataCaptureSlot(this,SLOT(showImage2(void *)));

	sensor3=new Sensor("URG","urg");
	sensor3->loadParamsSlot(configfilename);
	sensor3->openSensorSlot();
	sensor3->connectCaptureDataSignal(&timer3,SIGNAL(timeout()));
	sensor3->connectDataCaptureSlot(this,SLOT(showImage3(void *)));

	timer1.start(100);
	timer2.start(100);
	timer3.start(100);
}

USBCamera::~USBCamera()
{
	timer1.stop();
	timer2.stop();
	timer3.stop();
	delete sensor1;
	delete sensor2;
	delete sensor3;
}

struct USBCameraData
{
	QTime timestamp;
	cv::Mat image;
};

void USBCamera::showImage1(void * data)
{
	USBCameraData * tempdata=(USBCameraData *)data;
	cv::imshow("USBCamera1",tempdata->image);
}

void USBCamera::showImage2(void * data)
{
	USBCameraData * tempdata=(USBCameraData *)data;
	cv::imshow("USBCamera2",tempdata->image);
}

void USBCamera::showImage3(void * data)
{
//	USBCameraData * tempdata=(USBCameraData *)data;
//	cv::imshow("USBCamera3",tempdata->image);
}
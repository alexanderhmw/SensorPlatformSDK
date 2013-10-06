#include "usbcamera.h"

#pragma comment(lib,"Sensor.lib")
#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")

USBCamera::USBCamera(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	sensor=new Sensor("USBCamera","camera");
	sensor->loadParamsSlot("C:/PossDemo/GitHub/HMW-Alexander/SensorPlatformSDK/Examples/USBCamera/usbcamera.xml");
	
	sensor->openSensorSlot();
	sensor->connectCaptureDataSignal(&timer,SIGNAL(timeout()));
	sensor->connectDataCaptureSlot(this,SLOT(showImage(void *)));
	timer.start(100);
}

USBCamera::~USBCamera()
{
	timer.stop();
	sensor->closeSensorSlot();
	delete sensor;
}

struct USBCameraData
{
	QTime timestamp;
	cv::Mat image;
};

void USBCamera::showImage(void * data)
{
	USBCameraData * tempdata=(USBCameraData *)data;
	cv::imshow("USBCamera",tempdata->image);
}
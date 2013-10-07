#include "usbcamera.h"

#pragma comment(lib,"Sensor.lib")
#pragma comment(lib,"Storage.lib")
#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")

USBCamera::USBCamera(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QString configfilename=QString("usbcamera.xml");
	bool flag=1;

	sensor1=new Sensor("URG","urg",10);
	sensor1->loadParamsSlot(configfilename);
	sensor1->openSensorSlot();
	sensor1->moveToThread(&thread1);

	storage=new Storage(sensor1);
	storage->loadParamsSlot(configfilename);
	storage->openStorageSlot();	

	sensor2=new Sensor("USBCamera","camera",10);
	sensor2->loadParamsSlot(configfilename);
	sensor2->openSensorSlot();
	sensor2->moveToThread(&thread2);

	flag&=sensor1->connectCaptureDataSignal(&timer1,SIGNAL(timeout()));
	flag&=sensor1->connectDataCaptureSlot(storage,SLOT(storeDataSlot(void *)));
	flag&=sensor2->connectCaptureDataSignal(&timer2,SIGNAL(timeout()));
	flag&=sensor2->connectDataCaptureSlot(this,SLOT(showImage(void *)));

	thread1.start();
	thread2.start();

	timer1.start(25);
	timer2.start(25);
}

USBCamera::~USBCamera()
{
	timer1.stop();
	timer2.stop();
	thread1.exit();
	thread1.wait();
	thread2.exit();
	thread2.wait();
	delete storage;
	delete sensor1;
	delete sensor2;	
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
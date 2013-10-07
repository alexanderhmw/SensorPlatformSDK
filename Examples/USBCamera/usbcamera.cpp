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

//==========================================

	sensor1=new Sensor("USBCamera","camera0",10);
	//sensor1=new Sensor("URG","urg",10);
	sensor1->moveToThread(&thread1);
	sensor1->loadParamsSlot(configfilename);

	sensorwidget1=new SensorWidget(sensor1);
	ui.layout->addWidget(sensorwidget1);
	sensorwidget1->connectSignals();
	
	storage1=new Storage(sensor1);
	storage1->loadParamsSlot(configfilename);
	storage1->openStorageSlot();
	
	flag&=sensor1->connectDataCaptureSlot(storage1,SLOT(storeDataSlot(void *)));

//==========================================

	sensor2=new Sensor("USBCamera","camera1",10);
	sensor2->moveToThread(&thread2);
	sensor2->loadParamsSlot(configfilename);

	sensorwidget2=new SensorWidget(sensor2);
	ui.layout->addWidget(sensorwidget2);
	sensorwidget2->connectSignals();

	storage2=new Storage(sensor2);
	storage2->loadParamsSlot(configfilename);
	storage2->openStorageSlot();

	flag&=sensor2->connectDataCaptureSlot(storage2,SLOT(storeDataSlot(void *)));

//==========================================

	flag&=sensor1->connectCaptureDataSignal(&timer1,SIGNAL(timeout()));	
	flag&=sensor2->connectCaptureDataSignal(&timer2,SIGNAL(timeout()));	
	flag&=connect(ui.start,SIGNAL(clicked()),&timer1,SLOT(start()));
	flag&=connect(ui.start,SIGNAL(clicked()),&timer2,SLOT(start()));
	flag&=connect(ui.stop,SIGNAL(clicked()),&timer1,SLOT(stop()));
	flag&=connect(ui.stop,SIGNAL(clicked()),&timer2,SLOT(stop()));	
	flag&=connect(ui.close,SIGNAL(clicked()),&timer1,SLOT(stop()));
	flag&=connect(ui.close,SIGNAL(clicked()),&timer2,SLOT(stop()));	

	flag&=sensor1->connectOpenSensorSignal(ui.open,SIGNAL(clicked()));
	flag&=sensor1->connectCloseSensorSignal(ui.close,SIGNAL(clicked()));
	flag&=sensor2->connectOpenSensorSignal(ui.open,SIGNAL(clicked()));
	flag&=sensor2->connectCloseSensorSignal(ui.close,SIGNAL(clicked()));

//==========================================
	thread1.start();
	thread2.start();

	timer1.setInterval(100);
	timer2.setInterval(100);
}

USBCamera::~USBCamera()
{	
	timer1.stop();
	timer2.stop();
	sensorwidget1->disconnectSignals();
	sensorwidget2->disconnectSignals();
	
	thread1.exit();
	thread1.wait();
	thread2.exit();
	thread2.wait();

	delete storage1;
	delete storage2;
	delete sensor1;
	delete sensor2;	
}

struct USBCameraData
{
	QTime timestamp;
	cv::Mat image;
};
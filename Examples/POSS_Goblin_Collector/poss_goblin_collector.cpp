#include "poss_goblin_collector.h"

#pragma comment(lib,"Sensor.lib")
#pragma comment(lib,"Communicator.lib")
#pragma comment(lib,"Storage.lib")

POSS_Goblin_Collector::POSS_Goblin_Collector(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	bool flag=1;

//==================================
//Camera
	camera=new Sensor("PointGreyFlea2","PointGreyFlea2",20);
	camera->moveToThread(&camerathread);
	camerawidget=new SensorWidget(camera);
	camerawidget->connectSignals();
	camerastorage=new Storage(camera);
	cameratimer.setInterval(50);

	ui.hlayout->addWidget(camerawidget,1);

	flag&=camera->connectCaptureDataSignal(&cameratimer,SIGNAL(timeout()));
	flag&=camera->connectDataCaptureSlot(camerastorage,SLOT(storeDataSlot(void *)));
//==================================
//Laser
	laser=new Sensor("URG","URG",20);
	laser->moveToThread(&laserthread);
	laserwidget=new SensorWidget(laser);
	laserwidget->connectSignals();
	laserstorage=new Storage(laser);
	lasertimer.setInterval(25);

	ui.vlayout->addWidget(laserwidget,0);

	flag&=laser->connectCaptureDataSignal(&lasertimer,SIGNAL(timeout()));
	flag&=laser->connectDataCaptureSlot(laserstorage,SLOT(storeDataSlot(void *)));
//==================================
//Encoder
	encoder=new Communicator("Encoder","Encoder",20);
	encoder->moveToThread(&encoderthread);
	encoderwidget=new CommunicatorWidget(encoder);
	encoderwidget->connectSignals();
	encoderstorage=new Storage(encoder);

	ui.vlayout->addWidget(encoderwidget,0);

	flag&=encoder->connectDataReceivedSlot(encoderstorage,SLOT(storeDataSlot(void *)));
//==================================
//Load Parameters
	QString configfile=QString("config.xml");
	camera->loadParamsSlot(configfile);
	camerastorage->loadParamsSlot(configfile);
	laser->loadParamsSlot(configfile);
	laserstorage->loadParamsSlot(configfile);
	encoder->loadParamsSlot(configfile);
	encoderstorage->loadParamsSlot(configfile);
//===================================
//Open Sensor & Storage
	camera->openSensorSlot();
	camerastorage->openStorageSlot();
	laser->openSensorSlot();
	laserstorage->openStorageSlot();
	encoder->openCommunicatorSlot();
	encoderstorage->openStorageSlot();
//==================================
//Start timer
	camerathread.start();
	laserthread.start();
	encoderthread.start();
	cameratimer.start(50);
	lasertimer.start(25);
}

POSS_Goblin_Collector::~POSS_Goblin_Collector()
{


	cameratimer.stop();
	lasertimer.stop();

	camerawidget->disconnectSignals();
	camerathread.exit();
	camerathread.wait();

	laserwidget->disconnectSignals();
	laserthread.exit();
	laserthread.wait();

	encoderwidget->disconnectSignals();
	encoderthread.exit();
	encoderthread.wait();

	delete camera;
	delete camerastorage;
	delete laser;
	delete laserstorage;
	delete encoder;
	delete encoderstorage;
}

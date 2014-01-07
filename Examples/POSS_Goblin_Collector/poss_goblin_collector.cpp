#include "poss_goblin_collector.h"
#pragma comment(lib,"Sensor.lib")
#pragma comment(lib,"Communicator.lib")
#pragma comment(lib,"Storage.lib")
#pragma comment(lib,"Processor.lib")

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
	//
	controltimer.setInterval(100);
	flag&=connect(&controltimer,SIGNAL(timeout()),this,SLOT(sendControlOrderSlot()));
	flag&=connect(this, SIGNAL(sendControlOrderSignal(void*)), encoder, SLOT(sendDataSlot(void*)));
//==================================
//Odometry
	odometry=new Processor("Odometry","Odometry",10,10);
	odometry->moveToThread(&odometrythread);

	odometrystorage=new Storage(odometry);
	odometrystoragewidget=new StorageWidget(odometrystorage);
	odometrystoragewidget->connectSignals();

	ui.vlayout->addWidget(odometrystoragewidget);

	flag&=odometry->connectDataProcessedSlot(odometrystorage,SLOT(storeDataSlot(void *)));
	flag&=odometry->inputDataDriven(encoder,SIGNAL(dataReceivedSignal(void *)));
//==================================
//Load Parameters
	QString configfile=QString("config.xml");
	camera->loadParamsSlot(configfile);
	camerastorage->loadParamsSlot(configfile);
	laser->loadParamsSlot(configfile);
	laserstorage->loadParamsSlot(configfile);
	encoder->loadParamsSlot(configfile);
	encoderstorage->loadParamsSlot(configfile);
	odometry->loadParamsSlot(configfile);
	odometrystorage->loadParamsSlot(configfile);
//===================================
//Open Sensor 
	camera->openSensorSlot();
	laser->openSensorSlot();
	encoder->openCommunicatorSlot();
	odometry->openProcessorSlot();
//==================================
//Start timer and thread
	camerathread.start();
	laserthread.start();
	encoderthread.start();
	cameratimer.start(50);
	lasertimer.start(25);
	odometrythread.start();
//===================
// init for UI
	connect(ui.startsend, SIGNAL(clicked()), this, SLOT(startSendSlot()));
	connect(ui.stopsend, SIGNAL(clicked()), this, SLOT(stopSendSlot()));
	connect(ui.openstorage, SIGNAL(clicked()), this, SLOT(openStorageSlot()));
	connect(ui.closestorage, SIGNAL(clicked()), this, SLOT(closeStorageSlot()));

	ui.startsend->setEnabled(true);
	ui.stopsend->setEnabled(false);
	ui.openstorage->setEnabled(true);
	ui.closestorage->setEnabled(false);
	ui.storecamera->setChecked(true);
	ui.storelaser->setChecked(true);
	ui.storeencoder->setChecked(true);
	ui.storeodometry->setChecked(false);
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

	odometrystoragewidget->disconnectSignals();
	odometrythread.exit();
	odometrythread.wait();

	delete camera;
	delete camerastorage;
	delete laser;
	delete laserstorage;
	delete encoder;
	delete encoderstorage;
	delete odometry;
	delete odometrystorage;
}

#define pack_header (char)0xf8
#define pack_tail (char)0x8f	

void POSS_Goblin_Collector::sendControlOrderSlot()
{
	static CONTROLORDER controlorder;
	//=========================
	char * dataput; 
	int data_size = 0;
	data_size=sizeof(short)+1; // sizeof(short) = 2
	dataput=(char*)malloc(data_size+3);
	dataput[0]=pack_header;
	dataput[1]=data_size ;
	dataput[2]=0x01;
	*(short*)&dataput[3]= ui.order->text().toInt();
	if(dataput[0]==pack_header)
	{
		controlorder.order.clear();
		controlorder.order.append(dataput,data_size+2);
		controlorder.order.append(pack_tail);
		free(dataput);
		emit sendControlOrderSignal((void *)&controlorder);
	}
	//=========================	
}

void POSS_Goblin_Collector::startSendSlot()
{
	controltimer.start();
	ui.startsend->setEnabled(false);
	ui.stopsend->setEnabled(true);
}

void POSS_Goblin_Collector::stopSendSlot()
{
	controltimer.stop();
	ui.startsend->setEnabled(true);
	ui.stopsend->setEnabled(false);
}

void POSS_Goblin_Collector::openStorageSlot()
{	
	//change laser's storage filename 
	URGSTORAGEPARAMS * urgparams=(URGSTORAGEPARAMS *)laserstorage->getParams();
	urgparams->extension=QString("%1.lms").arg(ui.order->text());

	if(ui.storecamera->isChecked())
	{//open camera storage
		camerastorage->openStorageSlot();
	}
	if(ui.storelaser->isChecked())
	{//open laser storage
		laserstorage->openStorageSlot();
	}
	if(ui.storeencoder->isChecked())
	{//open encode storage
		encoderstorage->openStorageSlot();
	}
	if(ui.storeodometry->isChecked())
	{
		odometrystorage->openStorageSlot();
	}

	//operators for UI
	ui.storecamera->setEnabled(false);
	ui.storeencoder->setEnabled(false);
	ui.storelaser->setEnabled(false);
	ui.openstorage->setEnabled(false);
	ui.closestorage->setEnabled(true);
}

void POSS_Goblin_Collector::closeStorageSlot()
{
	if(ui.storecamera->isChecked())
	{//close camera storage
		camerastorage->closeStorageSlot();
	}
	if(ui.storelaser->isChecked())
	{//close laser storage
		laserstorage->closeStorageSlot();
	}
	if(ui.storeencoder->isChecked())
	{//close encode storage
		encoderstorage->closeStorageSlot();
	}
	if(ui.storeodometry->isChecked())
	{
		odometrystorage->closeStorageSlot();
	}

	//operators for UI
	ui.storecamera->setEnabled(true);
	ui.storeencoder->setEnabled(true);
	ui.storelaser->setEnabled(true);
	ui.openstorage->setEnabled(true);
	ui.closestorage->setEnabled(false);
}
#include "sensor_storage.h"

#pragma comment(lib,"Sensor.lib")
#pragma comment(lib,"Communicator.lib")
#pragma comment(lib,"Storage.lib")

Sensor_Storage::Sensor_Storage(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	
	sensor=NULL;
	sensorwidget=NULL;
	storage=NULL;
	storagewidget=NULL;

	flag=1;	
	flag&=connect(ui.setsensor,SIGNAL(clicked()),this,SLOT(setSensor()));
	flag&=connect(ui.browse,SIGNAL(clicked()),this,SLOT(browseParamsFile()));
	flag&=connect(ui.loadparams,SIGNAL(clicked()),this,SLOT(loadParamsFile()));
	flag&=connect(ui.start,SIGNAL(clicked()),this,SLOT(startSensor()));
	flag&=connect(ui.stop,SIGNAL(clicked()),this,SLOT(stopSensor()));
	flag&=connect(ui.close,SIGNAL(clicked()),this,SLOT(stopSensor()));
	flag=0;
}

Sensor_Storage::~Sensor_Storage()
{
	if(flag)
	{
		timer.stop();

		storagewidget->disconnectSignals();
		storagethread.exit();
		storagethread.wait();
		
		sensorwidget->disconnectSignals();
		sensorthread.exit();
		sensorthread.wait();

		delete storagewidget;
		delete sensorwidget;
		delete storage;
		delete sensor;
	}
}

void Sensor_Storage::setSensor()
{
	if(flag)
	{
		timer.stop();

		storagewidget->disconnectSignals();
		storagethread.exit();
		storagethread.wait();
		
		sensorwidget->disconnectSignals();
		sensorthread.exit();
		sensorthread.wait();

		delete storagewidget;
		delete sensorwidget;
		delete storage;
		delete sensor;
	}
	flag=1;
//=================================
	//sensor=new Sensor(ui.sensorclass->text(),ui.sensorname->text(),ui.buffersize->text().toInt());
	sensor=new Communicator(ui.sensorclass->text(),ui.sensorname->text(),ui.buffersize->text().toInt());
	sensor->moveToThread(&sensorthread);

	storage=new Storage(sensor);
	storage->moveToThread(&storagethread);

//	flag&=sensor->connectCaptureDataSignal(&timer,SIGNAL(timeout()));
	//flag&=sensor->connectDataCaptureSlot(storage,SLOT(storeDataSlot(void *)));
	//flag&=sensor->connectOpenSensorSignal(ui.open,SIGNAL(clicked()));
	//flag&=sensor->connectCloseSensorSignal(ui.close,SIGNAL(clicked()));

	flag&=sensor->connectDataReceivedSlot(storage,SLOT(storeDataSlot(void *)));
	flag&=sensor->connectOpenCommunicatorSignal(ui.open,SIGNAL(clicked()));
	flag&=sensor->connectCloseCommunicatorSignal(ui.close,SIGNAL(clicked()));

	flag&=storage->connectOpenStorageSignal(ui.openstorage,SIGNAL(clicked()));
	flag&=storage->connectCloseStorageSignal(ui.closestorage,SIGNAL(clicked()));
//=================================
	//sensorwidget=new SensorWidget(sensor);
	sensorwidget=new CommunicatorWidget(sensor);
	ui.sensorlayout->addWidget(sensorwidget);
	sensorwidget->connectSignals();

	storagewidget=new StorageWidget(storage);
	ui.storagelayout->addWidget(storagewidget);
	storagewidget->connectSignals();
//==================================
	sensorthread.start();
	storagethread.start();
//==================================
	flag=1;
}

void Sensor_Storage::browseParamsFile()
{
	ui.paramsfilename->setText(QFileDialog::getOpenFileName(this,QString("Params Config File"),QString(),QString("XML (*.xml)")));
}

void Sensor_Storage::loadParamsFile()
{
	if(sensor)
	{
		sensor->loadParamsSlot(ui.paramsfilename->text());
	}
	if(storage)
	{
		storage->loadParamsSlot(ui.paramsfilename->text());
	}
}

void Sensor_Storage::startSensor()
{
	timer.start(ui.interval->text().toInt());
}

void Sensor_Storage::stopSensor()
{
	timer.stop();
}
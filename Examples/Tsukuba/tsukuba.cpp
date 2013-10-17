#include "tsukuba.h"

#pragma comment(lib,"Sensor.lib")
#pragma comment(lib,"Communicator.lib")
#pragma comment(lib,"Storage.lib")

Tsukuba::Tsukuba(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

//====================================================
//Create Nodes

	URG=new Sensor("URG","URG",20);
	Xtion=new Sensor("Xtion","Xtion",20);
	UDPReceiver=new Sensor("UDPReceiver","UDPReceiver",20);
	Encoder=new Communicator("Encoder","Encoder",20);

	URGstorage=new Storage(URG);
	Xtionstorage=new Storage(Xtion);
	UDPReceiverstorage=new Storage(UDPReceiver);
	Encoderstorage=new Storage(Encoder);

	URGwidget=new SensorWidget(URG);
	Xtionwidget=new SensorWidget(Xtion);
	UDPReceiverwidget=new SensorWidget(UDPReceiver);
	Encoderwidget=new CommunicatorWidget(Encoder);

	URGstoragewidget=new StorageWidget(URGstorage);
	Xtionstoragewidget=new StorageWidget(Xtionstorage);
	UDPReceiverstoragewidget=new StorageWidget(UDPReceiverstorage);
	Encoderstoragewidget=new StorageWidget(Encoderstorage);

//=======================================================
//Form linkages;

	bool flag=1;

	flag&=URG->connectOpenSensorSignal(ui.open,SIGNAL(clicked()));
	flag&=Xtion->connectOpenSensorSignal(ui.open,SIGNAL(clicked()));
	flag&=UDPReceiver->connectOpenSensorSignal(ui.open,SIGNAL(clicked()));
	flag&=Encoder->connectOpenCommunicatorSignal(ui.open,SIGNAL(clicked()));
	flag&=URGstorage->connectOpenStorageSignal(ui.open,SIGNAL(clicked()));
	flag&=Xtionstorage->connectOpenStorageSignal(ui.open,SIGNAL(clicked()));
	flag&=UDPReceiverstorage->connectOpenStorageSignal(ui.open,SIGNAL(clicked()));
	flag&=Encoderstorage->connectOpenStorageSignal(ui.open,SIGNAL(clicked()));

	flag&=connect(ui.start,SIGNAL(clicked()),&URGtimer,SLOT(start()));
	flag&=connect(ui.start,SIGNAL(clicked()),&Xtiontimer,SLOT(start()));

	flag&=URG->connectCaptureDataSignal(&URGtimer,SIGNAL(timeout()));
	flag&=Xtion->connectCaptureDataSignal(&Xtiontimer,SIGNAL(timeout()));

	flag&=connect(ui.stop,SIGNAL(clicked()),&URGtimer,SLOT(stop()));
	flag&=connect(ui.stop,SIGNAL(clicked()),&Xtiontimer,SLOT(stop()));
	flag&=connect(ui.close,SIGNAL(clicked()),&URGtimer,SLOT(stop()));
	flag&=connect(ui.close,SIGNAL(clicked()),&Xtiontimer,SLOT(stop()));

	flag&=URG->connectCloseSensorSignal(ui.close,SIGNAL(clicked()));
	flag&=Xtion->connectCloseSensorSignal(ui.close,SIGNAL(clicked()));
	flag&=UDPReceiver->connectCloseSensorSignal(ui.close,SIGNAL(clicked()));
	flag&=Encoder->connectCloseCommunicatorSignal(ui.close,SIGNAL(clicked()));
	flag&=URGstorage->connectCloseStorageSignal(ui.close,SIGNAL(clicked()));
	flag&=Xtionstorage->connectCloseStorageSignal(ui.close,SIGNAL(clicked()));
	flag&=UDPReceiverstorage->connectCloseStorageSignal(ui.close,SIGNAL(clicked()));
	flag&=Encoderstorage->connectCloseStorageSignal(ui.close,SIGNAL(clicked()));

	flag&=URG->connectDataCaptureSlot(URGstorage,SLOT(storeDataSlot(void *)));
	flag&=Xtion->connectDataCaptureSlot(Xtionstorage,SLOT(storeDataSlot(void *)));
	flag&=UDPReceiver->connectDataCaptureSlot(UDPReceiverstorage,SLOT(storeDataSlot(void *)));
	flag&=Encoder->connectDataReceivedSlot(Encoderstorage,SLOT(storeDataSlot(void *)));

	flag&=URGwidget->connectSignals();
	flag&=Xtionwidget->connectSignals();
	flag&=UDPReceiverwidget->connectSignals();
	flag&=Encoderwidget->connectSignals();

	flag&=URGstoragewidget->connectSignals();
	flag&=Xtionstoragewidget->connectSignals();
	flag&=UDPReceiverstoragewidget->connectSignals();
	flag&=Encoderstoragewidget->connectSignals();
//=======================================================
//Configuration
	URGtimer.setInterval(50);
	Xtiontimer.setInterval(50);

	URG->loadParamsSlot("config.xml");
	Xtion->loadParamsSlot("config.xml");
	UDPReceiver->loadParamsSlot("config.xml");
	Encoder->loadParamsSlot("config.xml");

	URGstorage->loadParamsSlot("config.xml");
	Xtionstorage->loadParamsSlot("config.xml");
	UDPReceiverstorage->loadParamsSlot("config.xml");
	Encoderstorage->loadParamsSlot("config.xml");

	URG->moveToThread(&URGthread);
	Xtion->moveToThread(&Xtionthread);
	UDPReceiver->moveToThread(&UDPReceiverthread);
	Encoder->moveToThread(&Encoderthread);

	URGstorage->moveToThread(&URGthread);
	Xtionstorage->moveToThread(&Xtionthread);
	UDPReceiverstorage->moveToThread(&UDPReceiverthread);
	Encoderstorage->moveToThread(&Encoderthread);

	ui.layout->addWidget(URGwidget);
	ui.layout->addWidget(URGstoragewidget);
	ui.layout->addWidget(Xtionwidget);
	ui.layout->addWidget(Xtionstoragewidget);
	ui.layout->addWidget(UDPReceiverwidget);
	ui.layout->addWidget(UDPReceiverstoragewidget);
	ui.layout->addWidget(Encoderwidget);
	ui.layout->addWidget(Encoderstoragewidget);

	URGthread.start();
	Xtionthread.start();
	UDPReceiverthread.start();
	Encoderthread.start();
}

Tsukuba::~Tsukuba()
{
	URGtimer.stop();
	Xtiontimer.stop();

	URGwidget->disconnectSignals();
	URGstoragewidget->disconnectSignals();
	Xtionwidget->disconnectSignals();
	Xtionstoragewidget->disconnectSignals();
	UDPReceiverwidget->disconnectSignals();
	UDPReceiverstoragewidget->disconnectSignals();
	Encoderwidget->disconnectSignals();
	Encoderstoragewidget->disconnectSignals();

	URGthread.exit();
	URGthread.wait();
	Xtionthread.exit();
	Xtionthread.wait();
	UDPReceiverthread.exit();
	UDPReceiverthread.wait();
	Encoderthread.exit();
	Encoderthread.wait();

	delete URGstorage;
	delete URG;
	delete Xtionstorage;
	delete Xtion;
	delete UDPReceiverstorage;
	delete UDPReceiver;
	delete Encoderstorage;
	delete Encoder;
}

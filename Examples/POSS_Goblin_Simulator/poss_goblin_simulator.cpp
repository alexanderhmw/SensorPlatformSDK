#include "poss_goblin_simulator.h"
#pragma comment(lib,"Simulator.lib")
#pragma comment(lib,"Processor.lib")
#pragma comment(lib,"Storage.lib")


POSS_Goblin_Simulator::POSS_Goblin_Simulator(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	bool flag=1;

//==================================
//Encoder
	simulator=new Simulator("Encoder","Encoder",10);
	simulator->moveToThread(&simulatorthread);

	flag&=simulator->connectInitialSimulatorSignal(this,SIGNAL(initialSimulatorSignal(long)));
	flag&=simulator->connectStartSimulationSignal(ui.start,SIGNAL(clicked()));
	flag&=simulator->connectStopSimulatorSignal(ui.stop,SIGNAL(clicked()));
//==================================
//Odometry
	processor=new Processor("Odometry","Odometry",10,10);
	processor->moveToThread(&processorthread);

	processorstorage=new Storage(processor);
	processorstoragewidget=new StorageWidget(processorstorage);
	processorstoragewidget->connectSignals();

	ui.vlayout->addWidget(processorstoragewidget,0);

	flag&=processor->connectDataProcessedSlot(processorstorage,SLOT(storeDataSlot(void *)));
	flag&=processor->inputDataDriven(simulator,SIGNAL(dataEmitSignal(void *)));
//==================================
//Load Parameters
	QString configfile=QString("config.xml");
	simulator->loadParamsSlot(configfile);
	processor->loadParamsSlot(configfile);
	processorstorage->loadParamsSlot(configfile);
//===================================
//Open Sensor 
	simulator->openSimulatorSlot();
	processor->openProcessorSlot();
	processorstorage->openStorageSlot();
//==================================
//Start timer and thread
	simulatorthread.start();
	processorthread.start();
//===================
// init for UI
	flag&=connect(ui.initial,SIGNAL(clicked()),this,SLOT(initialSimulatorSlot()));
}

POSS_Goblin_Simulator::~POSS_Goblin_Simulator()
{

}

void POSS_Goblin_Simulator::initialSimulatorSlot()
{
	emit initialSimulatorSignal(ui.starttime->text().toLong());
}
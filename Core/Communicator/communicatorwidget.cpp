#include "communicatorwidget.h"

CommunicatorWidget::CommunicatorWidget(Communicator * communicator, QWidget *parent)
	: NodeWidgetBase(communicator, parent)
{
	FptrLoadCheck(communicatorOpenFptr,communicatorOpen,_library);
	FptrLoadCheck(communicatorOpenErrorFptr,communicatorOpenError,_library);
	FptrLoadCheck(dataReceivedFptr,dataReceived,_library);
	FptrLoadCheck(dataReceivedErrorFptr,dataReceivedError,_library);
	FptrLoadCheck(dataSentFptr,dataSent,_library);
	FptrLoadCheck(dataSentErrorFptr,dataSentError,_library);
	FptrLoadCheck(communicatorCloseFptr,communicatorClose,_library);
	FptrLoadCheck(communicatorCloseErrorFptr,communicatorCloseError,_library);

	_communicator=communicator;
}

CommunicatorWidget::~CommunicatorWidget()
{

}

void CommunicatorWidget::communicatorOpenSlot()
{
	communicatorOpen(_widgets);
}

void CommunicatorWidget::communicatorOpenErrorSlot()
{
	communicatorOpenError(_widgets);
}

void CommunicatorWidget::dataReceivedSlot(void * receivedata)
{
	dataReceived(_widgets,receivedata);
}

void CommunicatorWidget::dataReceivedErrorSlot()
{
	dataReceivedError(_widgets);
}

void CommunicatorWidget::dataSentSlot(void * senddata)
{
	dataSent(_widgets,senddata);
}

void CommunicatorWidget::dataSentErrorSlot()
{
	dataSentError(_widgets);
}

void CommunicatorWidget::communicatorCloseSlot()
{
	communicatorClose(_widgets);
}

void CommunicatorWidget::communicatorCloseErrorSlot()
{
	communicatorCloseError(_widgets);
}

bool CommunicatorWidget::connectSignals()
{
	bool flag=1;
	flag&=_communicator->connectCommunicatorOpenSlot(this,SLOT(communicatorOpenSlot()));
	flag&=_communicator->connectCommunicatorOpenErrorSlot(this,SLOT(communicatorOpenErrorSlot()));
	flag&=_communicator->connectDataReceivedSlot(this,SLOT(dataReceivedSlot(void *)));
	flag&=_communicator->connectDataReceivedErrorSlot(this,SLOT(dataReceivedErrorSlot()));
	flag&=_communicator->connectDataSentSlot(this,SLOT(dataSentSlot(void *)));
	flag&=_communicator->connectDataSentErrorSlot(this,SLOT(dataSentErrorSlot()));
	flag&=_communicator->connectCommunicatorCloseSlot(this,SLOT(communicatorCloseSlot()));
	flag&=_communicator->connectCommunicatorCloseErrorSlot(this,SLOT(communicatorCloseErrorSlot()));
	return flag;
}

bool CommunicatorWidget::disconnectSignals()
{
	bool flag=1;
	flag&=_communicator->disconnectCommunicatorOpenSlot(this,SLOT(communicatorOpenSlot()));
	flag&=_communicator->disconnectCommunicatorOpenErrorSlot(this,SLOT(communicatorOpenErrorSlot()));
	flag&=_communicator->disconnectDataReceivedSlot(this,SLOT(dataReceivedSlot(void *)));
	flag&=_communicator->disconnectDataReceivedErrorSlot(this,SLOT(dataReceivedErrorSlot()));
	flag&=_communicator->disconnectDataSentSlot(this,SLOT(dataSentSlot(void *)));
	flag&=_communicator->disconnectDataSentErrorSlot(this,SLOT(dataSentErrorSlot()));
	flag&=_communicator->disconnectCommunicatorCloseSlot(this,SLOT(communicatorCloseSlot()));
	flag&=_communicator->disconnectCommunicatorCloseErrorSlot(this,SLOT(communicatorCloseErrorSlot()));
	return flag;
}
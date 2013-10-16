#ifndef COMMUNICATORWIDGET_H
#define COMMUNICATORWIDGET_H

#include<NodeBase\nodewidgetbase.h>
#include<Communicator\communicator.h>

class CommunicatorWidget : public NodeWidgetBase
{
	Q_OBJECT
public:
	CommunicatorWidget(Communicator * communicator, QWidget *parent=NULL);
	~CommunicatorWidget();
protected:
	Communicator * _communicator;
protected:
	typedef void (*communicatorOpenFptr)(void * widgets);
	communicatorOpenFptr communicatorOpen;
	typedef void (*communicatorOpenErrorFptr)(void * widgets);
	communicatorOpenErrorFptr communicatorOpenError;
	typedef void (*dataReceivedFptr)(void * widgets, void * receivedata);
	dataReceivedFptr dataReceived;
	typedef void (*dataReceivedErrorFptr)(void * widgets);
	dataReceivedErrorFptr dataReceivedError;
	typedef void (*dataSentFptr)(void * widgets, void * senddata);
	dataSentFptr dataSent;
	typedef void (*dataSentErrorFptr)(void * widgets);
	dataSentErrorFptr dataSentError;
	typedef void (*communicatorCloseFptr)(void * widgets);
	communicatorCloseFptr communicatorClose;
	typedef void (*communicatorCloseErrorFptr)(void * widgets);
	communicatorCloseErrorFptr communicatorCloseError;
protected slots:
	void communicatorOpenSlot();
	void communicatorOpenErrorSlot();
	void dataReceivedSlot(void * receivedata);
	void dataReceivedErrorSlot();
	void dataSentSlot(void * senddata);
	void dataSentErrorSlot();
	void communicatorCloseSlot();
	void communicatorCloseErrorSlot();
public:
	bool connectSignals();
	bool disconnectSignals();
};

#endif // COMMUNICATORWIDGET_H

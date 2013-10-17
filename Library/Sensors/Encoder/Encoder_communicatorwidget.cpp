#include "Encoder.h"
#include<FuncLibrary\communicatorwidgetfunc.h>

void setWidgetsCommunicator(QWidget * widget, void ** widgets)	//initial the widget
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new ENCODERCOMMUNICATORWIDGETS;
		Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		
	}

	Encoderwidgets->receivelabel.setFrameStyle(QFrame::Box);
	Encoderwidgets->receivelabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Encoderwidgets->receivelabel.setText(widget->windowTitle()+QString("_Receiver"));
	Encoderwidgets->receivestatus.setFrameStyle(QFrame::Box);
	Encoderwidgets->receivestatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Encoderwidgets->receivestatus.setText("Standby");
	Encoderwidgets->receiveframenum.setToolTip("Frame count");
	Encoderwidgets->receiveframenum.setText("0");
	Encoderwidgets->receiveinfo.setToolTip("Data Timestamp");
	Encoderwidgets->receiveinfo.setText("No Data");

	Encoderwidgets->sendlabel.setFrameStyle(QFrame::Box);
	Encoderwidgets->sendlabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Encoderwidgets->sendlabel.setText(widget->windowTitle()+QString("_Sender"));
	Encoderwidgets->sendstatus.setFrameStyle(QFrame::Box);
	Encoderwidgets->sendstatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Encoderwidgets->sendstatus.setText("Standby");
	Encoderwidgets->sendframenum.setToolTip("Frame count");
	Encoderwidgets->sendframenum.setText("0");
	Encoderwidgets->sendinfo.setToolTip("Data Timestamp");
	Encoderwidgets->sendinfo.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;
	QHBoxLayout * hlayout3=new QHBoxLayout;
	QHBoxLayout * hlayout4=new QHBoxLayout;

	hlayout1->addWidget(&(Encoderwidgets->receivelabel));
	hlayout1->addWidget(&(Encoderwidgets->receivestatus));
	hlayout2->addWidget(&(Encoderwidgets->receiveframenum));
	hlayout2->addWidget(&(Encoderwidgets->receiveinfo));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);

	hlayout3->addWidget(&(Encoderwidgets->sendlabel));
	hlayout3->addWidget(&(Encoderwidgets->sendstatus));
	hlayout4->addWidget(&(Encoderwidgets->sendframenum));
	hlayout4->addWidget(&(Encoderwidgets->sendinfo));
	vlayout->addLayout(hlayout3);
	vlayout->addLayout(hlayout4);

	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsCommunicator(QWidget * widget, void ** widgets)	//release the widget
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		delete Encoderwidgets;
		*widgets=NULL;		
	}
}

void communicatorOpen(void * widgets)	//handle opencommunicator signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Opened"));
	Encoderwidgets->receiveframenum.setText("0");
	Encoderwidgets->receiveinfo.setText("No Data");
	Encoderwidgets->sendstatus.setText(QString("Opened"));
	Encoderwidgets->sendframenum.setText("0");
	Encoderwidgets->sendinfo.setText("No Data");
}

void communicatorOpenError(void * widgets)	//handle opencommunicatorerror signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Open Error"));
	Encoderwidgets->receiveframenum.setText("0");
	Encoderwidgets->receiveinfo.setText("No Data");
	Encoderwidgets->sendstatus.setText(QString("Opened"));
	Encoderwidgets->sendframenum.setText("0");
	Encoderwidgets->sendinfo.setText("No Data");
}

void dataReceived(void * widgets,void * receivedata)	//handle capturedata signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	ENCODERCOMMUNICATORRECEIVEDATA * Encoderreceivedata=(ENCODERCOMMUNICATORRECEIVEDATA *)receivedata;
	Encoderwidgets->receivestatus.setText(QString("Received"));
	int num=Encoderwidgets->receiveframenum.text().toInt()+1;
	Encoderwidgets->receiveframenum.setText(QString("%1").arg(num));
	Encoderwidgets->receiveinfo.setText(QString("%1_%2").arg(Encoderreceivedata->qtimestamp.toString("hh:mm:ss:zzz")).arg(QString(Encoderreceivedata->datagram)));
}

void dataReceivedError(void * widgets)	//handle capturedataerror signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Receive Error"));
	Encoderwidgets->receiveinfo.setText("No Data");
}

void dataSent(void * widgets,void * senddata)	//handle capturedata signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	ENCODERCOMMUNICATORSENDDATA * Encodersenddata=(ENCODERCOMMUNICATORSENDDATA *)senddata;
	Encoderwidgets->sendstatus.setText(QString("Sent"));
	int num=Encoderwidgets->sendframenum.text().toInt()+1;
	Encoderwidgets->sendframenum.setText(QString("%1").arg(num));
	Encoderwidgets->sendinfo.setText(QString(Encodersenddata->datagram));
}

void dataSentError(void * widgets)	//handle capturedataerror signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	Encoderwidgets->sendstatus.setText(QString("Sent Error"));
	Encoderwidgets->sendinfo.setText("No Data");
}

void communicatorClose(void * widgets)	//handle closecommunicator signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Closed"));
	Encoderwidgets->sendstatus.setText(QString("Closed"));
}

void communicatorCloseError(void * widgets)	//handle closecommunicatorerror signal
{
	ENCODERCOMMUNICATORWIDGETS * Encoderwidgets=(ENCODERCOMMUNICATORWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Close Error"));
	Encoderwidgets->sendstatus.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

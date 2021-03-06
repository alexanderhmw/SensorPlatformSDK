#include "UDPReceiver.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)(*widgets);
	if(UDPReceiverwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new UDPRECEIVERSENSORWIDGETS;
		UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: UDPReceiver point to a memory block
		
	}

	UDPReceiverwidgets->label.setFrameStyle(QFrame::Box);
	UDPReceiverwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	UDPReceiverwidgets->label.setText(widget->windowTitle());
	UDPReceiverwidgets->status.setFrameStyle(QFrame::Box);
	UDPReceiverwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	UDPReceiverwidgets->status.setText("Standby");
	UDPReceiverwidgets->framenum.setToolTip("Frame count");
	UDPReceiverwidgets->framenum.setText("0");
	UDPReceiverwidgets->info.setToolTip("Data Timestamp");
	UDPReceiverwidgets->info.setText("No Data");
	UDPReceiverwidgets->datagram.setToolTip("Datagram");
	UDPReceiverwidgets->datagram.setText("No Datagram");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(UDPReceiverwidgets->label));
	hlayout1->addWidget(&(UDPReceiverwidgets->status));
	hlayout2->addWidget(&(UDPReceiverwidgets->framenum));
	hlayout2->addWidget(&(UDPReceiverwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addWidget(&(UDPReceiverwidgets->datagram));
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)(*widgets);
	if(UDPReceiverwidgets==NULL)
	{//case1: widgets point to a NULL
		
		UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: UDPReceiver point to a memory block
		delete UDPReceiverwidgets;
		*widgets=NULL;
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Opened"));
	UDPReceiverwidgets->framenum.setText("0");
	UDPReceiverwidgets->info.setText("No Data");
	UDPReceiverwidgets->datagram.setText("No Datagram");
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Open Error"));
	UDPReceiverwidgets->framenum.setText("0");
	UDPReceiverwidgets->info.setText("No Data");
	UDPReceiverwidgets->datagram.setText("No Datagram");
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)widgets;
	UDPRECEIVERSENSORDATA * UDPReceiverdata=(UDPRECEIVERSENSORDATA *)data;
	UDPReceiverwidgets->status.setText(QString("Captured"));
	int num=UDPReceiverwidgets->framenum.text().toInt()+1;
	UDPReceiverwidgets->framenum.setText(QString("%1").arg(num));
	UDPReceiverwidgets->info.setText(QString("%1_%2_%3").arg(UDPReceiverdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(UDPReceiverdata->senderip.toString()).arg(UDPReceiverdata->senderport));
	UDPReceiverwidgets->datagram.setText(QString(UDPReceiverdata->datagram));
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Capture Error"));
	UDPReceiverwidgets->info.setText(QString("No Data"));
	UDPReceiverwidgets->datagram.setText("No Datagram");
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Closed"));
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	UDPRECEIVERSENSORWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSENSORWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

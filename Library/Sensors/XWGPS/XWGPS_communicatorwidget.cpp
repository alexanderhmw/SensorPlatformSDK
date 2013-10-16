#include "XWGPS.h"
#include<FuncLibrary\communicatorwidgetfunc.h>

void setWidgetsCommunicator(QWidget * widget, void ** widgets)	//initial the widget
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new XWGPSCOMMUNICATORWIDGETS;
		XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}

	XWGPSwidgets->receivelabel.setFrameStyle(QFrame::Box);
	XWGPSwidgets->receivelabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	XWGPSwidgets->receivelabel.setText(widget->windowTitle()+QString("_Receiver"));
	XWGPSwidgets->receivestatus.setFrameStyle(QFrame::Box);
	XWGPSwidgets->receivestatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	XWGPSwidgets->receivestatus.setText("Standby");
	XWGPSwidgets->receiveframenum.setToolTip("Frame count");
	XWGPSwidgets->receiveframenum.setText("0");
	XWGPSwidgets->receiveinfo.setToolTip("Data Timestamp");
	XWGPSwidgets->receiveinfo.setText("No Data");
	XWGPSwidgets->receivedatagram.setToolTip("Datagram");
	XWGPSwidgets->receivedatagram.clear();

	XWGPSwidgets->sendlabel.setFrameStyle(QFrame::Box);
	XWGPSwidgets->sendlabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	XWGPSwidgets->sendlabel.setText(widget->windowTitle()+QString("_Sender"));
	XWGPSwidgets->sendstatus.setFrameStyle(QFrame::Box);
	XWGPSwidgets->sendstatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	XWGPSwidgets->sendstatus.setText("Standby");
	XWGPSwidgets->sendframenum.setToolTip("Frame count");
	XWGPSwidgets->sendframenum.setText("0");
	XWGPSwidgets->sendinfo.setToolTip("Data Timestamp");
	XWGPSwidgets->sendinfo.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;
	QHBoxLayout * hlayout3=new QHBoxLayout;
	QHBoxLayout * hlayout4=new QHBoxLayout;

	hlayout1->addWidget(&(XWGPSwidgets->receivelabel));
	hlayout1->addWidget(&(XWGPSwidgets->receivestatus));
	hlayout2->addWidget(&(XWGPSwidgets->receiveframenum));
	hlayout2->addWidget(&(XWGPSwidgets->receiveinfo));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addWidget(&(XWGPSwidgets->receivedatagram));

	hlayout3->addWidget(&(XWGPSwidgets->sendlabel));
	hlayout3->addWidget(&(XWGPSwidgets->sendstatus));
	hlayout4->addWidget(&(XWGPSwidgets->sendframenum));
	hlayout4->addWidget(&(XWGPSwidgets->sendinfo));
	vlayout->addLayout(hlayout3);
	vlayout->addLayout(hlayout4);

	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsCommunicator(QWidget * widget, void ** widgets)	//release the widget
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		delete XWGPSwidgets;
		*widgets=NULL;
	}
}

void communicatorOpen(void * widgets)	//handle opencommunicator signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Opened"));
	XWGPSwidgets->receiveframenum.setText("0");
	XWGPSwidgets->receiveinfo.setText("No Data");
	XWGPSwidgets->receivedatagram.clear();
	XWGPSwidgets->sendstatus.setText(QString("Opened"));
	XWGPSwidgets->sendframenum.setText("0");
	XWGPSwidgets->sendinfo.setText("No Data");
}

void communicatorOpenError(void * widgets)	//handle opencommunicatorerror signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Open Error"));
	XWGPSwidgets->receiveframenum.setText("0");
	XWGPSwidgets->receiveinfo.setText("No Data");
	XWGPSwidgets->receivedatagram.clear();
	XWGPSwidgets->sendstatus.setText(QString("Opened"));
	XWGPSwidgets->sendframenum.setText("0");
	XWGPSwidgets->sendinfo.setText("No Data");
}

void dataReceived(void * widgets,void * receivedata)	//handle capturedata signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSCOMMUNICATORRECEIVEDATA * XWGPSreceivedata=(XWGPSCOMMUNICATORRECEIVEDATA *)receivedata;
	XWGPSwidgets->receivestatus.setText(QString("Received"));
	int num=XWGPSwidgets->receiveframenum.text().toInt()+1;
	XWGPSwidgets->receiveframenum.setText(QString("%1").arg(num));
	XWGPSwidgets->receiveinfo.setText(QString("%1_Shv<%2,%3,%4>_Rot<%5,%6,%7>").arg(XWGPSreceivedata->qtimestamp.toString("hh:mm:ss:zzz")).arg(XWGPSreceivedata->sx).arg(XWGPSreceivedata->sy).arg(XWGPSreceivedata->sz).arg(XWGPSreceivedata->rx).arg(XWGPSreceivedata->ry).arg(XWGPSreceivedata->rz));
	XWGPSwidgets->receivedatagram.appendPlainText(QString(XWGPSreceivedata->datagram));
}

void dataReceivedError(void * widgets)	//handle capturedataerror signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Receive Error"));
	XWGPSwidgets->receiveinfo.setText("No Data");
}

void dataSent(void * widgets,void * senddata)	//handle capturedata signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSCOMMUNICATORSENDDATA * XWGPSsenddata=(XWGPSCOMMUNICATORSENDDATA *)senddata;
	XWGPSwidgets->sendstatus.setText(QString("Sent"));
	int num=XWGPSwidgets->sendframenum.text().toInt()+1;
	XWGPSwidgets->sendframenum.setText(QString("%1").arg(num));
	XWGPSwidgets->sendinfo.setText(QString(XWGPSsenddata->datagram));
}

void dataSentError(void * widgets)	//handle capturedataerror signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSwidgets->sendstatus.setText(QString("Sent Error"));
	XWGPSwidgets->sendinfo.setText("No Data");
}

void communicatorClose(void * widgets)	//handle closecommunicator signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Closed"));
	XWGPSwidgets->sendstatus.setText(QString("Closed"));
}

void communicatorCloseError(void * widgets)	//handle closecommunicatorerror signal
{
	XWGPSCOMMUNICATORWIDGETS * XWGPSwidgets=(XWGPSCOMMUNICATORWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Close Error"));
	XWGPSwidgets->sendstatus.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

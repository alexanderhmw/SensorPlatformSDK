#include "URG.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)(*widgets);
	if(URGwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new URGSENSORWIDGETS;
		URGwidgets=(URGSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: URG point to a memory block
		
	}

	URGwidgets->label.setFrameStyle(QFrame::Box);
	URGwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	URGwidgets->label.setText(widget->windowTitle());
	URGwidgets->status.setFrameStyle(QFrame::Box);
	URGwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	URGwidgets->status.setText("Standby");
	URGwidgets->framenum.setToolTip("Frame count");
	URGwidgets->framenum.setText("0");
	URGwidgets->info.setToolTip("Data Timestamp");
	URGwidgets->info.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(URGwidgets->label));
	hlayout1->addWidget(&(URGwidgets->status));
	hlayout2->addWidget(&(URGwidgets->framenum));
	hlayout2->addWidget(&(URGwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)(*widgets);
	if(URGwidgets==NULL)
	{//case1: widgets point to a NULL
		
		URGwidgets=(URGSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: URG point to a memory block
		delete URGwidgets;
		*widgets=NULL;
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Opened"));
	URGwidgets->framenum.setText("0");
	URGwidgets->info.setText("No Data");
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Open Error"));
	URGwidgets->framenum.setText("0");
	URGwidgets->info.setText("No Data");
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)widgets;
	URGSENSORDATA * URGdata=(URGSENSORDATA *)data;
	URGwidgets->status.setText(QString("Captured"));
	int num=URGwidgets->framenum.text().toInt()+1;
	URGwidgets->framenum.setText(QString("%1").arg(num));
	URGwidgets->info.setText(QString("%1 - %2").arg(URGdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(URGdata->timestamp));
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Capture Error"));
	URGwidgets->info.setText(QString("No Data"));
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)widgets;
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	URGSENSORWIDGETS * URGwidgets=(URGSENSORWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Closed"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

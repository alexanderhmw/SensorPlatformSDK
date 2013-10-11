#include "urg.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)
{
	if(*widgets==NULL)
	{
		*widgets=(void *)new URGWIDGETS;
	}
	URGWIDGETS * tempwidgets=(URGWIDGETS *)(*widgets);

	tempwidgets->label.setFrameStyle(QFrame::Box);
	tempwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	tempwidgets->label.setText(widget->windowTitle());
	tempwidgets->status.setFrameStyle(QFrame::Box);
	tempwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	tempwidgets->status.setText("Standby");
	tempwidgets->framenum.setToolTip("Frame count");
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setToolTip("Data Timestamp");
	tempwidgets->info.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(tempwidgets->label));
	hlayout1->addWidget(&(tempwidgets->status));
	hlayout2->addWidget(&(tempwidgets->framenum));
	hlayout2->addWidget(&(tempwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)(*widgets);
	if(tempwidgets!=NULL)
	{
		delete tempwidgets;
		*widgets=NULL;
	}
}

void sensorOpen(void * widgets)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Opened"));
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
}

void sensorOpenError(void * widgets)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Open Error"));
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
}

void dataCapture(void * widgets,void * data)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Captured"));
	int num=tempwidgets->framenum.text().toInt()+1;
	tempwidgets->framenum.setText(QString("%1").arg(num));
	URGDATA * tempdata=(URGDATA *)data;
	tempwidgets->info.setText(QString("%1 - %2").arg(tempdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(tempdata->timestamp));
}

void dataCaptureError(void * widgets)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Capture Error"));
	tempwidgets->info.setText(QString("No Data"));
}

void sensorClose(void * widgets)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Closed"));
}

void sensorCloseError(void * widgets)
{
	URGWIDGETS * tempwidgets=(URGWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Close Error"));
}
#include "Xtion.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)(*widgets);
	if(Xtionwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new XTIONSENSORWIDGETS;
		Xtionwidgets=(XTIONSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: Xtion point to a memory block
		
	}
	Xtionwidgets->label.setFrameStyle(QFrame::Box);
	Xtionwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Xtionwidgets->label.setText(widget->windowTitle());
	Xtionwidgets->status.setFrameStyle(QFrame::Box);
	Xtionwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Xtionwidgets->status.setText("Standby");
	Xtionwidgets->framenum.setToolTip("Frame count");
	Xtionwidgets->framenum.setText("0");
	Xtionwidgets->info.setToolTip("Data Timestamp");
	Xtionwidgets->info.setText("No Data");
	Xtionwidgets->showdepth.setText("Show Depth");
	Xtionwidgets->showdepth.setCheckState(Qt::Checked);
	Xtionwidgets->showcolor.setText("Show Color");
	Xtionwidgets->showcolor.setCheckState(Qt::Checked);
	
	QSizePolicy sizepolicy;
	sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizepolicy.setHorizontalStretch(1);
	sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
	sizepolicy.setVerticalStretch(1);
	Xtionwidgets->depthimage.setFrameStyle(QFrame::Box);
	Xtionwidgets->depthimage.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Xtionwidgets->depthimage.setSizePolicy(sizepolicy);
	Xtionwidgets->depthimage.setText("No Depth Image");
	Xtionwidgets->colorimage.setFrameStyle(QFrame::Box);
	Xtionwidgets->colorimage.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Xtionwidgets->colorimage.setSizePolicy(sizepolicy);
	Xtionwidgets->colorimage.setText("No Color Image");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;
	QHBoxLayout * hlayout3=new QHBoxLayout;

	hlayout1->addWidget(&(Xtionwidgets->label));
	hlayout1->addWidget(&(Xtionwidgets->status));
	hlayout2->addWidget(&(Xtionwidgets->framenum));
	hlayout2->addWidget(&(Xtionwidgets->info));
	hlayout2->addWidget(&(Xtionwidgets->showdepth));
	hlayout2->addWidget(&(Xtionwidgets->showcolor));
	hlayout3->addWidget(&(Xtionwidgets->depthimage));
	hlayout3->addWidget(&(Xtionwidgets->colorimage));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addLayout(hlayout3);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)(*widgets);
	if(Xtionwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Xtionwidgets=(XTIONSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: Xtion point to a memory block
		delete Xtionwidgets;
		*widgets=NULL;
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Opened"));
	Xtionwidgets->framenum.setText("0");
	Xtionwidgets->info.setText("No Data");
	Xtionwidgets->depthimage.setText("No Depth Image");
	Xtionwidgets->colorimage.setText("No Color Image");
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Open Error"));
	Xtionwidgets->framenum.setText("0");
	Xtionwidgets->info.setText("No Data");
	Xtionwidgets->depthimage.setText("No Depth Image");
	Xtionwidgets->colorimage.setText("No Color Image");
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)widgets;
	XTIONSENSORDATA * Xtiondata=(XTIONSENSORDATA *)data;
	Xtionwidgets->status.setText(QString("Captured"));
	int num=Xtionwidgets->framenum.text().toInt()+1;
	Xtionwidgets->framenum.setText(QString("%1").arg(num));
	Xtionwidgets->info.setText(QString("%1 - %2").arg(Xtiondata->colortimestamp.toString("hh:mm:ss:zzz")).arg(Xtiondata->depthtimestamp.toString("hh:mm:ss:zzz")));
	if(Xtionwidgets->showdepth.isChecked())
	{
		QImage img;
		img=QImage((const uchar*)(Xtiondata->depth.data),Xtiondata->depth.cols,Xtiondata->depth.rows,QImage::Format_Indexed8);
		Xtionwidgets->depthimage.setPixmap(QPixmap::fromImage(img));  
	}
	else
	{
		Xtionwidgets->depthimage.setText("No Image");
	}
	if(Xtionwidgets->showcolor.isChecked())
	{
		QImage img;
		img=QImage((const uchar*)(Xtiondata->color.data),Xtiondata->color.cols,Xtiondata->color.rows,QImage::Format_RGB888);
		Xtionwidgets->colorimage.setPixmap(QPixmap::fromImage(img));  
	}
	else
	{
		Xtionwidgets->colorimage.setText("No Image");
	}
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Capture Error"));
	Xtionwidgets->info.setText("No Data");
	Xtionwidgets->depthimage.setText("No Depth Image");
	Xtionwidgets->colorimage.setText("No Color Image");
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Closed"));
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	XTIONSENSORWIDGETS * Xtionwidgets=(XTIONSENSORWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

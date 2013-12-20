#include "PointGreyFlea2.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)(*widgets);
	if(PointGreyFlea2widgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new POINTGREYFLEA2SENSORWIDGETS;
		PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}

	PointGreyFlea2widgets->label.setFrameStyle(QFrame::Box);
	PointGreyFlea2widgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	PointGreyFlea2widgets->label.setText(widget->windowTitle());
	PointGreyFlea2widgets->status.setFrameStyle(QFrame::Box);
	PointGreyFlea2widgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	PointGreyFlea2widgets->status.setText("Standby");
	PointGreyFlea2widgets->framenum.setToolTip("Frame count");
	PointGreyFlea2widgets->framenum.setText("0");
	PointGreyFlea2widgets->info.setToolTip("Data Timestamp");
	PointGreyFlea2widgets->info.setText("No Data");
	PointGreyFlea2widgets->showimage.setText("Show Image");
	PointGreyFlea2widgets->showimage.setCheckState(Qt::Checked);
	
	QSizePolicy sizepolicy;
	sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizepolicy.setHorizontalStretch(1);
	sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
	sizepolicy.setVerticalStretch(1);
	PointGreyFlea2widgets->image.setFrameStyle(QFrame::Box);
	PointGreyFlea2widgets->image.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	PointGreyFlea2widgets->image.setSizePolicy(sizepolicy);
	PointGreyFlea2widgets->image.setText("No Image");
	
	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;
	QHBoxLayout * hlayout3=new QHBoxLayout;

	hlayout1->addWidget(&(PointGreyFlea2widgets->label));
	hlayout1->addWidget(&(PointGreyFlea2widgets->status));
	hlayout2->addWidget(&(PointGreyFlea2widgets->framenum));
	hlayout2->addWidget(&(PointGreyFlea2widgets->info));
	hlayout2->addWidget(&(PointGreyFlea2widgets->showimage));
	hlayout3->addWidget(&(PointGreyFlea2widgets->image));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addLayout(hlayout3);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)(*widgets);
	if(PointGreyFlea2widgets==NULL)
	{//case1: widgets point to a NULL
		
		PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2widgets;
		*widgets=NULL;
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Opened"));
	PointGreyFlea2widgets->framenum.setText("0");
	PointGreyFlea2widgets->info.setText("No Data");
	PointGreyFlea2widgets->image.setText("No Image");
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Open Error"));
	PointGreyFlea2widgets->framenum.setText("0");
	PointGreyFlea2widgets->info.setText("No Data");
	PointGreyFlea2widgets->image.setText("No Image");
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)widgets;
	POINTGREYFLEA2SENSORDATA * pointgreyflea2data=(POINTGREYFLEA2SENSORDATA *)data;
	PointGreyFlea2widgets->status.setText(QString("Captured"));
	int num=PointGreyFlea2widgets->framenum.text().toInt()+1;
	PointGreyFlea2widgets->framenum.setText(QString("%1").arg(num));
	if(PointGreyFlea2widgets->showimage.isChecked())
	{
		QImage img;
		img=QImage((const uchar*)(pointgreyflea2data->image.data),pointgreyflea2data->image.cols,pointgreyflea2data->image.rows,QImage::Format_RGB888);
		PointGreyFlea2widgets->image.setPixmap(QPixmap::fromImage(img));  
	}
	else
	{
		PointGreyFlea2widgets->image.setText("No Image");
	}
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Capture Error"));
	PointGreyFlea2widgets->info.setText("No Data");
	PointGreyFlea2widgets->image.setText("No Image");
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Closed"));
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	POINTGREYFLEA2SENSORWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2SENSORWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

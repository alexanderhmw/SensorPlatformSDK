#include"usbcamera.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)
{
	if(*widgets==NULL)
	{
		*widgets=(void *)new USBCAMERAWIDGETS;
	}
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)(*widgets);

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
	tempwidgets->showimage.setText("Show Image");
	tempwidgets->showimage.setCheckState(Qt::Unchecked);
	tempwidgets->image.setFrameStyle(QFrame::Box);
	tempwidgets->image.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	QSizePolicy sizepolicy;
	sizepolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizepolicy.setHorizontalStretch(1);
	sizepolicy.setVerticalPolicy(QSizePolicy::Expanding);
	sizepolicy.setVerticalStretch(1);
	tempwidgets->image.setSizePolicy(sizepolicy);
	tempwidgets->image.setText("No Image");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(tempwidgets->label));
	hlayout1->addWidget(&(tempwidgets->status));
	hlayout2->addWidget(&(tempwidgets->framenum));
	hlayout2->addWidget(&(tempwidgets->info));
	hlayout2->addWidget(&(tempwidgets->showimage));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addWidget(&(tempwidgets->image));
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)(*widgets);
	if(tempwidgets!=NULL)
	{
		delete tempwidgets;
		*widgets=NULL;
	}
}

void sensorOpen(void * widgets)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Opened"));
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
	tempwidgets->image.setText("No Image");
}

void sensorOpenError(void * widgets)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Open Error"));
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
	tempwidgets->image.setText("No Image");
}

void dataCapture(void * widgets,void * data)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Captured"));
	int num=tempwidgets->framenum.text().toInt()+1;
	tempwidgets->framenum.setText(QString("%1").arg(num));
	USBCAMERADATA * tempdata=(USBCAMERADATA *)data;
	tempwidgets->info.setText(QString("%1 (%2 x %3)").arg(tempdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(tempdata->image.cols).arg(tempdata->image.rows));
	if(tempwidgets->showimage.isChecked())
	{
		cv::Mat rgb; 
		QImage img;  
		cv::cvtColor(tempdata->image,rgb,CV_BGR2RGB);  
		img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,QImage::Format_RGB888);
		tempwidgets->image.setPixmap(QPixmap::fromImage(img));  
	}
	else
	{
		tempwidgets->image.setText("No Image");
	}
    //tempwidgets->image.resize(tempwidgets->image.pixmap()->size()); 
}

void dataCaptureError(void * widgets)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Capture Error"));
	tempwidgets->info.setText(QString("No Data"));
	tempwidgets->image.setText("No Image");
}

void sensorClose(void * widgets)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Closed"));
}

void sensorCloseError(void * widgets)
{
	USBCAMERAWIDGETS * tempwidgets=(USBCAMERAWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Close Error"));
}
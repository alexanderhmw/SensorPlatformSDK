#include "usbcamera.h"

#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

bool loadParamsSensor(QString configfilename,QString nodetype, QString & nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
	nodeclass=QString("USBCamera");
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	releaseParamsSensor(params);
	*params=(void *)new USBCAMERAPARAMS;
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)(*params);
	bool flag=1;
	flag&=loader.getParam("deviceid",tempparams->deviceid);
	flag&=loader.getParam("width",tempparams->width);
	flag&=loader.getParam("height",tempparams->height);
	return flag;
}

void releaseParamsSensor(void ** params)
{
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)(*params);
	if(tempparams!=NULL)
	{
		delete tempparams;
		*params=NULL;
	}
}

bool openSensor(void * params)
{
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)params;
	tempparams->cap.open(tempparams->deviceid);
	if(!tempparams->cap.isOpened())
	{
		return 0;
	}
	bool flag=1;
	flag&=tempparams->cap.set(CV_CAP_PROP_FRAME_WIDTH,tempparams->width);
	flag&=tempparams->cap.set(CV_CAP_PROP_FRAME_HEIGHT,tempparams->height);
	return flag;
}

bool captureData(void * params, void ** data)
{
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)params;

	QTime qtimestamp;
	cv::Mat image;	
	tempparams->cap>>image;
	qtimestamp=QTime::currentTime();
	
	if(*data==NULL)
	{
		*data=(void *)new USBCAMERADATA;
	}
	USBCAMERADATA * tempdata=(USBCAMERADATA *)(*data);
	tempdata->qtimestamp=qtimestamp;
	image.copyTo(tempdata->image);
	return 1;
}

bool closeSensor(void * params)
{
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)params;
	tempparams->cap.release();
	return 1;
}

void releaseData(void ** data)
{
	USBCAMERADATA * tempdata=(USBCAMERADATA *)(*data);
	if(tempdata!=NULL)
	{
		delete tempdata;
		*data=NULL;
	}
}

//=============================================================

bool loadParamsStorage(QString configfilename,QString nodetype, QString & nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
	nodeclass=QString("USBCamera");
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	releaseParamsStorage(params);
	*params=(void *)new USBCAMERASTORAGEPARAMS;
	USBCAMERASTORAGEPARAMS * tempparams=(USBCAMERASTORAGEPARAMS *)(*params);
	bool flag=1;
	flag&=loader.getParam("fps",tempparams->fps);
	flag&=loader.getParam("storagepath",tempparams->storagepath);
	flag&=loader.getParam("extension",tempparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)
{
	USBCAMERASTORAGEPARAMS * tempparams=(USBCAMERASTORAGEPARAMS *)(*params);
	if(tempparams!=NULL)
	{
		delete tempparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * sensorparams)
{
	USBCAMERASTORAGEPARAMS * tempparams=(USBCAMERASTORAGEPARAMS *)params;
	USBCAMERAPARAMS * tempsensorparams=(USBCAMERAPARAMS *)sensorparams;
	if(tempparams->writer.isOpened())
	{
		tempparams->writer.release();
		if(tempparams->timestampwriter.isOpen())
		{
			tempparams->timestampwriter.close();
		}
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2-%3.%4").arg(tempparams->storagepath).arg(tempsensorparams->deviceid).arg(timestamp).arg(tempparams->extension);
	cv::Size framesize(tempsensorparams->width,tempsensorparams->height);
	if(tempparams->writer.open(filename.toStdString(),CV_FOURCC('P','I','M','1'),tempparams->fps,framesize))
	{
		tempparams->timestampwriter.setFileName(QString("%1_timestamp.log").arg(filename));
		if(tempparams->timestampwriter.open(QFile::WriteOnly | QFile::Text))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int storeData(void * params, void * data)
{
	USBCAMERASTORAGEPARAMS * tempparams=(USBCAMERASTORAGEPARAMS *)params;
	USBCAMERADATA * tempdata=(USBCAMERADATA *)data;
	if(tempparams->writer.isOpened())
	{
		long timestamp=((tempdata->qtimestamp.hour()*60+tempdata->qtimestamp.minute())*60
		+tempdata->qtimestamp.second())*1000+tempdata->qtimestamp.msec();
		tempparams->timestampwriter.write(QString("%1\n").arg(timestamp).toAscii());
		tempparams->writer.write(tempdata->image);
		return 1;
	}
	else
	{
		return 0;
	}
}

bool closeStorage(void * params)
{
	USBCAMERASTORAGEPARAMS * tempparams=(USBCAMERASTORAGEPARAMS *)params;
	tempparams->timestampwriter.close();
	tempparams->writer.release();
	return 1;
}

//==================================================================
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
	tempwidgets->image.setFrameStyle(QFrame::Box);
	tempwidgets->image.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	tempwidgets->image.setText("No Image");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(tempwidgets->label));
	hlayout1->addWidget(&(tempwidgets->status));
	hlayout2->addWidget(&(tempwidgets->framenum));
	hlayout2->addWidget(&(tempwidgets->info));
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
	cv::Mat rgb; 
	QImage img;  
	cv::cvtColor(tempdata->image,rgb,CV_BGR2RGB);  
    img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,QImage::Format_RGB888);
	tempwidgets->image.setPixmap(QPixmap::fromImage(img));  
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
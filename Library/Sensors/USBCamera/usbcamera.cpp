#include "usbcamera.h"

#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

bool loadParams(QString & configfilename, QString & sensorclass, QString & sensorname, void ** params)
{
	XMLParamsLoader loader;
	sensorclass=QString("USBCamera");
	if(!loader.loadParams(configfilename,QString("Sensor"),sensorclass,sensorname))
	{
		return 0;
	}
	releaseParams(params);
	*params=(void *)new USBCAMERAPARAMS;
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)(*params);
	bool flag=1;
	flag&=loader.getParam("deviceid",tempparams->deviceid);
	flag&=loader.getParam("width",tempparams->width);
	flag&=loader.getParam("height",tempparams->height);
	return flag;
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

void releaseParams(void ** params)
{
	USBCAMERAPARAMS * tempparams=(USBCAMERAPARAMS *)(*params);
	if(tempparams!=NULL)
	{
		delete tempparams;
		*params=NULL;
	}
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
#include "usbcamera.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
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
	if(!(tempparams->cap.read(image)))
	{
		return 0;
	}
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
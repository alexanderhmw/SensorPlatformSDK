#include"usbcamera.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
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
	tempparams->videofilename=QString("%1\\%2-%3.%4").arg(tempparams->storagepath).arg(tempsensorparams->deviceid).arg(timestamp).arg(tempparams->extension);
	cv::Size framesize(tempsensorparams->width,tempsensorparams->height);
	if(tempparams->writer.open(tempparams->videofilename.toStdString(),CV_FOURCC('P','I','M','1'),tempparams->fps,framesize))
	{
		tempparams->timestampwriter.setFileName(QString("%1_timestamp.log").arg(tempparams->videofilename));
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

bool storeData(void * params, void * data)
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
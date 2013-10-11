#include "Xtion.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	XTIONSTORAGEPARAMS * Xtionparams=(XTIONSTORAGEPARAMS *)(*params);
	if(Xtionparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new XTIONSTORAGEPARAMS;
		Xtionparams=(XTIONSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Xtion point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("fps",Xtionparams->fps);
	flag&=loader.getParam("storagepath",Xtionparams->storagepath);
	flag&=loader.getParam("extension",Xtionparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	XTIONSTORAGEPARAMS * Xtionparams=(XTIONSTORAGEPARAMS *)(*params);
	if(Xtionparams==NULL)
	{//case1: params point to a NULL
		
		Xtionparams=(XTIONSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Xtion point to a memory block
		delete Xtionparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * sensorparams)	//open for store
{
	XTIONSTORAGEPARAMS * Xtionparams=(XTIONSTORAGEPARAMS *)params;
	XTIONSENSORPARAMS * Xtionsensorparams=(XTIONSENSORPARAMS *)sensorparams;
	if(Xtionparams->depthwriter.isOpened())
	{
		Xtionparams->depthwriter.release();
	}
	if(Xtionparams->colorwriter.isOpened())
	{
		Xtionparams->colorwriter.release();
	}
	if(Xtionparams->timestampwriter.isOpen())
	{
		Xtionparams->timestampwriter.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	Xtionparams->depthvideofilename=QString("%1\\%2_depth.%3").arg(Xtionparams->storagepath).arg(timestamp).arg(Xtionparams->extension);
	Xtionparams->colorvideofilename=QString("%1\\%2_color.%3").arg(Xtionparams->storagepath).arg(timestamp).arg(Xtionparams->extension);
	cv::Size framesize(Xtionsensorparams->resolutionx,Xtionsensorparams->resolutiony);
	if(Xtionparams->depthwriter.open(Xtionparams->depthvideofilename.toStdString(),CV_FOURCC('P','I','M','1'),Xtionparams->fps,framesize,0))
	{
		if(Xtionparams->colorwriter.open(Xtionparams->colorvideofilename.toStdString(),CV_FOURCC('P','I','M','1'),Xtionparams->fps,framesize))
		{
			Xtionparams->timestampwriter.setFileName(QString("%1\\%2_Xtion_timestamp.log").arg(Xtionparams->storagepath).arg(timestamp));
			if(Xtionparams->timestampwriter.open(QFile::WriteOnly | QFile::Text))
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
	else
	{
		return 0;
	}
}

bool storeData(void * params, void * data)	//store data
{
	XTIONSTORAGEPARAMS * Xtionparams=(XTIONSTORAGEPARAMS *)params;
	XTIONSENSORDATA * Xtiondata=(XTIONSENSORDATA *)data;
	if(Xtionparams->depthwriter.isOpened())
	{
		Xtionparams->depthwriter.write(Xtiondata->depth);	
	}
	else
	{
		return 0;
	}
	if(Xtionparams->colorwriter.isOpened())
	{
		
		Xtionparams->colorwriter.write(Xtiondata->color);		
	}
	else
	{
		return 0;
	}
	if(Xtionparams->timestampwriter.isOpen())
	{
		long depthtimestamp=((Xtiondata->depthtimestamp.hour()*60+Xtiondata->depthtimestamp.minute())*60
			+Xtiondata->depthtimestamp.second())*1000+Xtiondata->depthtimestamp.msec();
		Xtionparams->timestampwriter.write(QString("%1\t").arg(depthtimestamp).toUtf8());
		long colortimestamp=((Xtiondata->colortimestamp.hour()*60+Xtiondata->colortimestamp.minute())*60
			+Xtiondata->colortimestamp.second())*1000+Xtiondata->colortimestamp.msec();
		Xtionparams->timestampwriter.write(QString("%1\n").arg(colortimestamp).toUtf8());
	}
	else
	{
		return 0;
	}
	return 1;
}

bool closeStorage(void * params)	//close storage
{
	XTIONSTORAGEPARAMS * Xtionparams=(XTIONSTORAGEPARAMS *)params;
	Xtionparams->timestampwriter.close();
	Xtionparams->depthwriter.release();
	Xtionparams->colorwriter.release();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

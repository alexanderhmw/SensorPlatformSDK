#include "PointGreyFlea2.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	POINTGREYFLEA2STORAGEPARAMS * PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)(*params);
	if(PointGreyFlea2params==NULL)
	{//case1: params point to a NULL
		*params=(void *)new POINTGREYFLEA2STORAGEPARAMS;
		PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)(*params);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("fps",PointGreyFlea2params->fps);
	flag&=loader.getParam("storagepath",PointGreyFlea2params->storagepath);
	flag&=loader.getParam("extension",PointGreyFlea2params->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	POINTGREYFLEA2STORAGEPARAMS * PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)(*params);
	if(PointGreyFlea2params==NULL)
	{//case1: params point to a NULL
		
		PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)(*params);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2params;
		*params=NULL;
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	POINTGREYFLEA2STORAGEPARAMS * PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)params;
	POINTGREYFLEA2SENSORPARAMS * PointGreyFlea2nodeparams=(POINTGREYFLEA2SENSORPARAMS *)nodeparams;
	if(PointGreyFlea2params->imagewriter.isOpened())
	{
		PointGreyFlea2params->imagewriter.release();
	}
	if(PointGreyFlea2params->timestampwriter.isOpen())
	{
		PointGreyFlea2params->timestampwriter.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	PointGreyFlea2params->videofilename=QString("%1\\%2.%3").arg(PointGreyFlea2params->storagepath).arg(timestamp).arg(PointGreyFlea2params->extension);
	cv::Size framesize(PointGreyFlea2nodeparams->resolutionx,PointGreyFlea2nodeparams->resolutiony);
	if(PointGreyFlea2params->imagewriter.open(PointGreyFlea2params->videofilename.toStdString(),CV_FOURCC('P','I','M','1'),PointGreyFlea2params->fps,framesize,1))
	{
		PointGreyFlea2params->timestampwriter.setFileName(QString("%1\\%2_PointGreyFlea2_timestamp.log").arg(PointGreyFlea2params->storagepath).arg(timestamp));
		if(PointGreyFlea2params->timestampwriter.open(QFile::WriteOnly | QFile::Text))
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

bool storeData(void * params, void * data)	//store data
{
	POINTGREYFLEA2STORAGEPARAMS * PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)params;
	POINTGREYFLEA2SENSORDATA * PointGreyFlea2data=(POINTGREYFLEA2SENSORDATA *)data;
	if(PointGreyFlea2params->imagewriter.isOpened())
	{
		PointGreyFlea2params->imagewriter.write(PointGreyFlea2data->image);	
	}
	else
	{
		return 0;
	}
	if(PointGreyFlea2params->timestampwriter.isOpen())
	{
		long timestamp=((PointGreyFlea2data->timestamp.hour()*60+PointGreyFlea2data->timestamp.minute())*60
			+PointGreyFlea2data->timestamp.second())*1000+PointGreyFlea2data->timestamp.msec();
		PointGreyFlea2params->timestampwriter.write(QString("%1\n").arg(timestamp).toUtf8());
	}
	else
	{
		return 0;
	}
	return 1;
}

bool closeStorage(void * params)	//close storage
{
	POINTGREYFLEA2STORAGEPARAMS * PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)params;
	PointGreyFlea2params->timestampwriter.close();
	PointGreyFlea2params->imagewriter.release();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

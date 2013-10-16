#include "XWGPS.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new XWGPSSTORAGEPARAMS;
		XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("storagepath",XWGPSparams->storagepath);
	flag&=loader.getParam("extension",XWGPSparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		
		XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		delete XWGPSparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
	if(XWGPSparams->file.isOpen())
	{
		XWGPSparams->file.close();
	}
	if(XWGPSparams->logfile.isOpen())
	{
		XWGPSparams->logfile.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2.%3").arg(XWGPSparams->storagepath).arg(timestamp).arg(XWGPSparams->extension);
	XWGPSparams->file.setFileName(filename);
	if(XWGPSparams->file.open(QFile::WriteOnly | QFile::Text))
	{
		XWGPSparams->logfile.setFileName(filename+QString(".log"));
		if(XWGPSparams->logfile.open(QFile::WriteOnly | QFile::Text))
		{
			return 1;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

bool storeData(void * params, void * data)	//store data
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
	XWGPSSTORAGEDATA * XWGPSdata=(XWGPSSTORAGEDATA *)data;
	if(XWGPSparams->file.isOpen())
	{
		long timestamp=((XWGPSdata->qtimestamp.hour()*60+XWGPSdata->qtimestamp.minute())*60
		+XWGPSdata->qtimestamp.second())*1000+XWGPSdata->qtimestamp.msec();
		XWGPSparams->file.write(QString("%1\t%2\t%3\t%4\t%5\t%6\t%7\t%8\n").arg(int(XWGPSdata->gpstime*1000+0.5)).arg(timestamp).arg(XWGPSdata->rx).arg(XWGPSdata->ry).arg(XWGPSdata->rz).arg(XWGPSdata->sx).arg(XWGPSdata->sy).arg(XWGPSdata->sz).toUtf8());
	}
	else
	{
		return 0;
	}
	if(XWGPSparams->logfile.isOpen())
	{
		XWGPSparams->logfile.write(XWGPSdata->datagram);
	}
	else
	{
		return 0;
	}
	return 1;
}

bool closeStorage(void * params)	//close storage
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
	XWGPSparams->file.close();
	XWGPSparams->logfile.close();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

#include "Odometry.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	ODOMETRYSTORAGEPARAMS * Odometryparams=(ODOMETRYSTORAGEPARAMS *)(*params);
	if(Odometryparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new ODOMETRYSTORAGEPARAMS;
		Odometryparams=(ODOMETRYSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Odometry point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("storagepath",Odometryparams->storagepath);
	flag&=loader.getParam("extension",Odometryparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	ODOMETRYSTORAGEPARAMS * Odometryparams=(ODOMETRYSTORAGEPARAMS *)(*params);
	if(Odometryparams==NULL)
	{//case1: params point to a NULL
		
		Odometryparams=(ODOMETRYSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Odometry point to a memory block
		delete Odometryparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	ODOMETRYSTORAGEPARAMS * Odometryparams=(ODOMETRYSTORAGEPARAMS *)params;
	if(Odometryparams->file.isOpen())
	{
		Odometryparams->file.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2.%3").arg(Odometryparams->storagepath).arg(timestamp).arg(Odometryparams->extension);
	Odometryparams->file.setFileName(filename);
	if(Odometryparams->file.open(QFile::WriteOnly | QFile::Text))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool storeData(void * params, void * data)	//store data
{
	ODOMETRYSTORAGEPARAMS * Odometryparams=(ODOMETRYSTORAGEPARAMS *)params;
	ODOMETRYSTORAGEDATA * Odometrydata=(ODOMETRYSTORAGEDATA *)data;
	if(Odometryparams->file.isOpen())
	{
		long timestamp=((Odometrydata->qtimestamp.hour()*60+Odometrydata->qtimestamp.minute())*60
		+Odometrydata->qtimestamp.second())*1000+Odometrydata->qtimestamp.msec();
		Odometryparams->file.write(QString("%1\t%2\t%3\t%4\n").arg(timestamp).arg(Odometrydata->theta).arg(Odometrydata->x).arg(Odometrydata->y).toUtf8());
		return 1;
	}
	else
	{
		return 0;
	}
}

bool closeStorage(void * params)	//close storage
{
	ODOMETRYSTORAGEPARAMS * Odometryparams=(ODOMETRYSTORAGEPARAMS *)params;
	Odometryparams->file.close();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

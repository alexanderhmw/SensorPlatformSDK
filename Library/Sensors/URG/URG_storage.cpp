#include "URG.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	URGSTORAGEPARAMS * URGparams=(URGSTORAGEPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new URGSTORAGEPARAMS;
		URGparams=(URGSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("storagepath",URGparams->storagepath);
	flag&=loader.getParam("extension",URGparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	URGSTORAGEPARAMS * URGparams=(URGSTORAGEPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		
		URGparams=(URGSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		delete URGparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	URGSTORAGEPARAMS * URGparams=(URGSTORAGEPARAMS *)params;
	if(URGparams->file.isOpen())
	{
		URGparams->file.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2.%3").arg(URGparams->storagepath).arg(timestamp).arg(URGparams->extension);
	URGparams->file.setFileName(filename);
	if(URGparams->file.open(QFile::WriteOnly))
	{
		URGSENSORPARAMS * URGnodeparams=(URGSENSORPARAMS *)nodeparams;
		float angrng=(URGnodeparams->last_step-URGnodeparams->first_step)*0.25;
		float angres=URGnodeparams->skip_step*0.25;
		float unit=100.0;
		URGparams->file.write((char *)&angrng,sizeof(angrng));
		URGparams->file.write((char *)&angres,sizeof(angres));
		URGparams->file.write((char *)&unit,sizeof(unit));
		return 1;
	}
	else
	{
		return 0;
	}
}

bool storeData(void * params, void * data)	//store data
{
	URGSTORAGEPARAMS * URGparams=(URGSTORAGEPARAMS *)params;
	URGSENSORDATA * URGdata=(URGSENSORDATA *)data;
	if(URGparams->file.isOpen())
	{
		long timestamp=((URGdata->qtimestamp.hour()*60+URGdata->qtimestamp.minute())*60
		+URGdata->qtimestamp.second())*1000+URGdata->qtimestamp.msec();
		URGparams->file.write((char *)&timestamp,sizeof(timestamp));
		URGparams->file.write((char *)URGdata->data,sizeof(short)*URGdata->datasize);
		return 1;
	}
	else
	{
		return 0;
	}
}

bool closeStorage(void * params)	//close storage
{
	URGSTORAGEPARAMS * URGparams=(URGSTORAGEPARAMS *)params;
	URGparams->file.close();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

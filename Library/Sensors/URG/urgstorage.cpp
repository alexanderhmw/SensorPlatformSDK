#include"urg.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	releaseParamsStorage(params);
	*params=(void *)new URGSTORAGEPARAMS;
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)(*params);
	bool flag=1;
	flag&=loader.getParam("storagepath",tempparams->storagepath);
	flag&=loader.getParam("extension",tempparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)
{
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)(*params);
	if(tempparams!=NULL)
	{
		delete tempparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * sensorparams)
{
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)params;
	if(tempparams->file.isOpen())
	{
		tempparams->file.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2.%3").arg(tempparams->storagepath).arg(timestamp).arg(tempparams->extension);
	tempparams->file.setFileName(filename);
	if(tempparams->file.open(QFile::WriteOnly))
	{
		URGPARAMS * tempsensorparams=(URGPARAMS *)sensorparams;
		float angrng=(tempsensorparams->last_step-tempsensorparams->first_step)*0.25;
		float angres=tempsensorparams->skip_step*0.25;
		float unit=100.0;
		tempparams->file.write((char *)&angrng,sizeof(angrng));
		tempparams->file.write((char *)&angres,sizeof(angres));
		tempparams->file.write((char *)&unit,sizeof(unit));
		return 1;
	}
	else
	{
		return 0;
	}
}

bool storeData(void * params, void * data)
{
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)params;
	URGDATA * tempdata=(URGDATA *)data;
	if(tempparams->file.isOpen())
	{
		long timestamp=((tempdata->qtimestamp.hour()*60+tempdata->qtimestamp.minute())*60
		+tempdata->qtimestamp.second())*1000+tempdata->qtimestamp.msec();
		tempparams->file.write((char *)&timestamp,sizeof(timestamp));
		tempparams->file.write((char *)tempdata->data,sizeof(short)*tempdata->datasize);
		return 1;
	}
	else
	{
		return 0;
	}
}

bool closeStorage(void * params)
{
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)params;
	tempparams->file.close();
	return 1;
}
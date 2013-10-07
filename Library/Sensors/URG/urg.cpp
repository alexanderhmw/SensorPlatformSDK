#include "urg.h"

#pragma comment(lib, "urgd.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

#define URGMAXSIZE 1081

bool loadParamsSensor(QString configfilename,QString nodetype, QString & nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
	nodeclass=QString("URG");
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	releaseParamsSensor(params);
	*params=(void *)new URGPARAMS;
	URGPARAMS * tempparams=(URGPARAMS *)(*params);
	bool flag=1;
	flag&=loader.getEnumParam("connection_type",tempparams->connection_type);
	flag&=loader.getParam("device_or_address",tempparams->device_or_address);
	flag&=loader.getParam("baudrate_or_port",tempparams->baudreate_or_port);
	flag&=loader.getEnumParam("measurement_type",tempparams->measurement_type);
	flag&=loader.getParam("skip_scan",tempparams->skip_scan);
	flag&=loader.getParam("first_step",tempparams->first_step);
	flag&=loader.getParam("last_step",tempparams->last_step);
	flag&=loader.getParam("skip_step",tempparams->skip_step);
	return flag;
}

void releaseParamsSensor(void ** params)
{
	URGPARAMS * tempparams=(URGPARAMS *)(*params);
	if(tempparams!=NULL)
	{
		delete tempparams;
		*params=NULL;
	}
}

bool openSensor(void * params)
{
	URGPARAMS * tempparams=(URGPARAMS *)params;
	int n=urg_open(&(tempparams->urg),tempparams->connection_type,tempparams->device_or_address.toStdString().c_str(),tempparams->baudreate_or_port);
	if(n<0)
	{
		return 0;
	}
	n=urg_set_scanning_parameter(&(tempparams->urg),tempparams->first_step,tempparams->last_step,tempparams->skip_step);
	if(n<0)
	{
		return 0;
	}
	return 1;
}

bool captureData(void * params, void ** data)
{
	URGPARAMS * tempparams=(URGPARAMS *)params;
	urg_start_measurement(&(tempparams->urg),tempparams->measurement_type,1,tempparams->skip_scan);
	long urgdata[URGMAXSIZE];
	long timestamp;
	int n=urg_get_distance(&(tempparams->urg),urgdata,&timestamp);
	QTime qtimestamp=QTime::currentTime();
	if(n<=0)
	{
		return 0;
	}

	URGDATA * tempdata;
	if(*data==NULL)
	{
		*data=(void *)new URGDATA;
		tempdata=(URGDATA *)(*data);
		tempdata->datasize=n;
		tempdata->data=new short[tempdata->datasize];
	}
	else
	{
		tempdata=(URGDATA *)(*data);
		if(tempdata->datasize!=n)
		{
			delete [](tempdata->data);
			tempdata->datasize=n;
			tempdata->data=new short[tempdata->datasize];
		}
	}
	tempdata->timestamp=timestamp;
	tempdata->qtimestamp=qtimestamp;
#pragma omp for schedule(dynamic,1)
	for(int i=0;i<n;i++)
	{
		tempdata->data[i]=short(urgdata[i]/10);
	}
	return 1;
}

bool closeSensor(void * params)
{
	URGPARAMS * tempparams=(URGPARAMS *)params;
	urg_close(&(tempparams->urg));
	return 1;
}

void releaseData(void ** data)
{
	URGDATA * tempdata=(URGDATA *)(*data);
	if(tempdata!=NULL)
	{
		delete tempdata;
		*data=NULL;
	}
}

//==================================================================

bool loadParamsStorage(QString configfilename,QString nodetype, QString & nodeclass, QString nodename, void ** params)
{
	XMLParamsLoader loader;
	nodeclass=QString("URG");
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

int storeData(void * params, void * data)
{
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)params;
	URGDATA * tempdata=(URGDATA *)data;
	if(tempparams->file.isOpen())
	{
		long timestamp=((tempdata->qtimestamp.hour()*60+tempdata->qtimestamp.minute())*60
		+tempdata->qtimestamp.second())*1000+tempdata->qtimestamp.msec();
		int count=0;
		count+=tempparams->file.write((char *)&timestamp,sizeof(timestamp));
		count+=tempparams->file.write((char *)tempdata->data,sizeof(short)*tempdata->datasize);
		return count;
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

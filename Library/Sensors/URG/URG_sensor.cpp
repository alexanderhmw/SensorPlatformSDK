#include "URG.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	URGSENSORPARAMS * URGparams=(URGSENSORPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new URGSENSORPARAMS;
		URGparams=(URGSENSORPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getEnumParam("connection_type",URGparams->connection_type);
	flag&=loader.getParam("device_or_address",URGparams->device_or_address);
	flag&=loader.getParam("baudrate_or_port",URGparams->baudreate_or_port);
	flag&=loader.getEnumParam("measurement_type",URGparams->measurement_type);
	flag&=loader.getParam("skip_scan",URGparams->skip_scan);
	flag&=loader.getParam("first_step",URGparams->first_step);
	flag&=loader.getParam("last_step",URGparams->last_step);
	flag&=loader.getParam("skip_step",URGparams->skip_step);
	return flag;
}

void releaseParamsSensor(void ** params)	//release params
{
	URGSENSORPARAMS * URGparams=(URGSENSORPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		
		URGparams=(URGSENSORPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		delete URGparams;
		*params=NULL;
	}
}

bool openSensor(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	URGSENSORPARAMS * URGparams=(URGSENSORPARAMS *)params;
	int n=urg_open(&(URGparams->urg),URGparams->connection_type,URGparams->device_or_address.toStdString().c_str(),URGparams->baudreate_or_port);
	if(n<0)
	{
		return 0;
	}
	n=urg_set_scanning_parameter(&(URGparams->urg),URGparams->first_step,URGparams->last_step,URGparams->skip_step);
	if(n<0)
	{
		return 0;
	}
	urg_start_measurement(&(URGparams->urg),URGparams->measurement_type,0,URGparams->skip_scan);
	return 1;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	URGSENSORPARAMS * URGparams=(URGSENSORPARAMS *)params;
	long urgdata[URGMAXSIZE];
	long timestamp;
	int n=urg_get_distance(&(URGparams->urg),urgdata,&timestamp);
	QTime qtimestamp=QTime::currentTime();
	if(n<=0)
	{
		return 0;
	}
	
	URGSENSORDATA * URGdata=(URGSENSORDATA *)(*data);
	if(URGdata==NULL)
	{//case1: data point to a NULL
		*data=(void *)new URGSENSORDATA;
		URGdata=(URGSENSORDATA *)(*data);
		URGdata->datasize=n;
		URGdata->data=new short[URGdata->datasize];
	}
	else
	{//case2: URG point to a memory block
		if(URGdata->datasize!=n)
		{
			delete [](URGdata->data);
			URGdata->datasize=n;
			URGdata->data=new short[URGdata->datasize];
		}
	}
	URGdata->timestamp=timestamp;
	URGdata->qtimestamp=qtimestamp;
#pragma omp for schedule(dynamic,1)
	for(int i=0;i<n;i++)
	{
		URGdata->data[i]=short(urgdata[i]/10);
	}
	return 1;
}

bool closeSensor(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	URGSENSORPARAMS * URGparams=(URGSENSORPARAMS *)params;	
	urg_close(&(URGparams->urg));
	return 1;
}

void releaseData(void ** data)	//release data
{
	URGSENSORDATA * URGdata=(URGSENSORDATA *)(*data);
	if(URGdata==NULL)
	{//case1: data point to a NULL
		
		URGdata=(URGSENSORDATA *)(*data);
	}
	else
	{//case2: URG point to a memory block
		delete URGdata;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

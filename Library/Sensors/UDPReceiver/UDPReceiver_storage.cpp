#include "UDPReceiver.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	UDPRECEIVERSTORAGEPARAMS * UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)(*params);
	if(UDPReceiverparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new UDPRECEIVERSTORAGEPARAMS;
		UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: UDPReceiver point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("storagepath",UDPReceiverparams->storagepath);
	flag&=loader.getParam("extension",UDPReceiverparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	UDPRECEIVERSTORAGEPARAMS * UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)(*params);
	if(UDPReceiverparams==NULL)
	{//case1: params point to a NULL
		
		UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: UDPReceiver point to a memory block
		delete UDPReceiverparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	UDPRECEIVERSTORAGEPARAMS * UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)params;
	if(UDPReceiverparams->file.isOpen())
	{
		UDPReceiverparams->file.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2.%3").arg(UDPReceiverparams->storagepath).arg(timestamp).arg(UDPReceiverparams->extension);
	UDPReceiverparams->file.setFileName(filename);
	if(UDPReceiverparams->file.open(QFile::WriteOnly))
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
	UDPRECEIVERSTORAGEPARAMS * UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)params;
	UDPRECEIVERSTORAGEDATA * UDPReceiverdata=(UDPRECEIVERSTORAGEDATA *)data;
	if(UDPReceiverparams->file.isOpen())
	{
		long timestamp=((UDPReceiverdata->qtimestamp.hour()*60+UDPReceiverdata->qtimestamp.minute())*60
		+UDPReceiverdata->qtimestamp.second())*1000+UDPReceiverdata->qtimestamp.msec();
		UDPReceiverparams->file.write((char *)&timestamp,sizeof(timestamp));
		int datagramsize=UDPReceiverdata->datagram.size();
		UDPReceiverparams->file.write((char *)&datagramsize,sizeof(datagramsize));
		UDPReceiverparams->file.write(UDPReceiverdata->datagram);
		return 1;
	}
	else
	{
		return 0;
	}
}

bool closeStorage(void * params)	//close storage
{
	UDPRECEIVERSTORAGEPARAMS * UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)params;
	UDPReceiverparams->file.close();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

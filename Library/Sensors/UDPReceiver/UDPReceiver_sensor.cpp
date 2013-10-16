#include "UDPReceiver.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	UDPRECEIVERSENSORPARAMS * UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)(*params);
	if(UDPReceiverparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new UDPRECEIVERSENSORPARAMS;
		UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)(*params);
	}
	else
	{//case2: UDPReceiver point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("port",UDPReceiverparams->port);
	return flag;
}

void releaseParamsSensor(void ** params)	//release params
{
	UDPRECEIVERSENSORPARAMS * UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)(*params);
	if(UDPReceiverparams==NULL)
	{//case1: params point to a NULL
		
		UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)(*params);
	}
	else
	{//case2: UDPReceiver point to a memory block
		delete UDPReceiverparams;
		*params=NULL;
	}
}

bool openSensor(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	UDPRECEIVERSENSORPARAMS * UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)params;
	*trigger=&(UDPReceiverparams->udpsocket);
	triggersignal=QString(SIGNAL(readyRead()));
	if(!(UDPReceiverparams->udpsocket.bind(UDPReceiverparams->port)))
	{
		return 0;
	}
	return 1;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	UDPRECEIVERSENSORPARAMS * UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)params;
	QByteArray datagram;
	QHostAddress senderip;
	quint16 senderport;
	QTime qtimestamp;
	if(UDPReceiverparams->udpsocket.hasPendingDatagrams())
	{
		datagram.resize(UDPReceiverparams->udpsocket.pendingDatagramSize());
		UDPReceiverparams->udpsocket.readDatagram(datagram.data(),datagram.size(),&senderip,&senderport);
		qtimestamp=QTime::currentTime();
	}
	else
	{
		return 0;
	}
	
	UDPRECEIVERSENSORDATA * UDPReceiverdata=(UDPRECEIVERSENSORDATA *)(*data);
	if(UDPReceiverdata==NULL)
	{//case1: data point to a NULL
		*data=(void *)new UDPRECEIVERSENSORDATA;
		UDPReceiverdata=(UDPRECEIVERSENSORDATA *)(*data);
	}
	else
	{//case2: UDPReceiver point to a memory block
		
	}
	UDPReceiverdata->datagram=datagram;
	UDPReceiverdata->senderip=senderip;
	UDPReceiverdata->senderport=senderport;
	UDPReceiverdata->qtimestamp=qtimestamp;
	return 1;
}

bool closeSensor(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	UDPRECEIVERSENSORPARAMS * UDPReceiverparams=(UDPRECEIVERSENSORPARAMS *)params;
	*trigger=&(UDPReceiverparams->udpsocket);
	triggersignal=QString(SIGNAL(readyRead()));
	UDPReceiverparams->udpsocket.close();
	return 1;
}

void releaseData(void ** data)	//release data
{
	UDPRECEIVERSENSORDATA * UDPReceiverdata=(UDPRECEIVERSENSORDATA *)(*data);
	if(UDPReceiverdata==NULL)
	{//case1: data point to a NULL
		
		UDPReceiverdata=(UDPRECEIVERSENSORDATA *)(*data);
	}
	else
	{//case2: UDPReceiver point to a memory block
		delete UDPReceiverdata;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

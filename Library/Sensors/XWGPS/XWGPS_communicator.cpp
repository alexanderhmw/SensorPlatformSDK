#include "XWGPS.h"
#include<FuncLibrary\communicatorfunc.h>
#include"datatransfer.h"

bool loadParamsCommunicator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	XWGPSCOMMUNICATORPARAMS * XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new XWGPSCOMMUNICATORPARAMS;
		XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("port",XWGPSparams->port);
	flag&=loader.getEnumParam("baudrate",XWGPSparams->baudrate);
	flag&=loader.getEnumParam("databitstype",XWGPSparams->databitstype);
	flag&=loader.getEnumParam("paritytype",XWGPSparams->paritytype);
	flag&=loader.getEnumParam("stopbitstype",XWGPSparams->stopbitstype);
	flag&=loader.getEnumParam("flowtype",XWGPSparams->flowtype);
	flag&=loader.getParam("timeout",XWGPSparams->timeout);
	flag&=loader.getEnumParam("querymode",XWGPSparams->querymode);
	flag&=loader.getParam("recvpacksize",XWGPSparams->recvpacksize);
	flag&=loader.getParam("packhead",XWGPSparams->packhead);
	flag&=loader.getParam("packtail",XWGPSparams->packtail);
	return flag;
}

void releaseParamsCommunicator(void ** params)	//release params
{
	XWGPSCOMMUNICATORPARAMS * XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		
		XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		delete XWGPSparams;
		*params=NULL;
	}
}

bool openCommunicator(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	XWGPSCOMMUNICATORPARAMS * XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)params;
	*trigger=&(XWGPSparams->serialport);
	triggersignal=QString(SIGNAL(readyRead()));
	XWGPSparams->serialport.setPortName(XWGPSparams->port);
	XWGPSparams->serialport.setBaudRate(XWGPSparams->baudrate);
	XWGPSparams->serialport.setDataBits(XWGPSparams->databitstype);
	XWGPSparams->serialport.setParity(XWGPSparams->paritytype);
	XWGPSparams->serialport.setStopBits(XWGPSparams->stopbitstype);
	XWGPSparams->serialport.setFlowControl(XWGPSparams->flowtype);
	XWGPSparams->serialport.setTimeout(XWGPSparams->timeout);
	XWGPSparams->serialport.setQueryMode(XWGPSparams->querymode);
	if(!(XWGPSparams->serialport.open(QIODevice::ReadWrite)))
	{
		return 0;
	}
	return 1;
}

bool receiveData(void * params, void ** receivedata)	//capture data using params and store in data
{
	XWGPSCOMMUNICATORPARAMS * XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)params;
	if(XWGPSparams->serialport.bytesAvailable()<XWGPSparams->recvpacksize)
	{
		return 0;
	}
	QByteArray datagram=XWGPSparams->serialport.readAll();
	XWGPSparams->databuffer.append(datagram);
	int startid=XWGPSparams->databuffer.indexOf(HeaderFPD);
	if(startid>=0)
	{
		int endid=XWGPSparams->databuffer.indexOf(EndGLL,startid);
		int valid=XWGPSparams->databuffer.indexOf(Invalid,startid);
		if(endid>startid)
		{
			XWGPSCOMMUNICATORRECEIVEDATA * XWGPSreceivedata=(XWGPSCOMMUNICATORRECEIVEDATA *)(*receivedata);
			if(XWGPSreceivedata==NULL)
			{//case1: data point to a NULL
				*receivedata=(void *)new XWGPSCOMMUNICATORRECEIVEDATA;
				XWGPSreceivedata=(XWGPSCOMMUNICATORRECEIVEDATA *)(*receivedata);
			}
			else
			{//case2: UDPReceiver point to a memory block

			}
			XWGPSreceivedata->valid=valid;
			XWGPSreceivedata->datagram=XWGPSparams->databuffer;
			XWGPSparams->databuffer.clear();
			dataTransfer(startid,endid,XWGPSreceivedata);
			return 1;
		}
	}
	return 0;
}

bool sendData(void * params, void * senddata)
{
	XWGPSCOMMUNICATORPARAMS * XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)params;
	XWGPSCOMMUNICATORSENDDATA * XWGPSsenddata=(XWGPSCOMMUNICATORSENDDATA *)senddata;
	qint64 n=XWGPSparams->serialport.write(XWGPSsenddata->datagram);
	if(n>0)
	{
		return 1;
	}
	return 0;
}

bool closeCommunicator(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	XWGPSCOMMUNICATORPARAMS * XWGPSparams=(XWGPSCOMMUNICATORPARAMS *)params;
	*trigger=&(XWGPSparams->serialport);
	triggersignal=QString(SIGNAL(readyRead()));
	XWGPSparams->serialport.close();
	return 1;
}

void flushReceiveData(void ** receivedata)	//release data
{
	XWGPSCOMMUNICATORRECEIVEDATA * XWGPSreceivedata=(XWGPSCOMMUNICATORRECEIVEDATA *)(*receivedata);
	if(XWGPSreceivedata==NULL)
	{//case1: data point to a NULL
		
		XWGPSreceivedata=(XWGPSCOMMUNICATORRECEIVEDATA *)(*receivedata);
	}
	else
	{//case2: XWGPS point to a memory block
		delete XWGPSreceivedata;
		*receivedata=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

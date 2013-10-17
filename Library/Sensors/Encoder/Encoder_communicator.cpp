#include "Encoder.h"
#include<FuncLibrary\communicatorfunc.h>

bool loadParamsCommunicator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	ENCODERCOMMUNICATORPARAMS * Encoderparams=(ENCODERCOMMUNICATORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new ENCODERCOMMUNICATORPARAMS;
		Encoderparams=(ENCODERCOMMUNICATORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("port",Encoderparams->port);
	flag&=loader.getEnumParam("baudrate",Encoderparams->baudrate);
	flag&=loader.getEnumParam("databitstype",Encoderparams->databitstype);
	flag&=loader.getEnumParam("paritytype",Encoderparams->paritytype);
	flag&=loader.getEnumParam("stopbitstype",Encoderparams->stopbitstype);
	flag&=loader.getEnumParam("flowtype",Encoderparams->flowtype);
	flag&=loader.getParam("timeout",Encoderparams->timeout);
	flag&=loader.getEnumParam("querymode",Encoderparams->querymode);
	flag&=loader.getParam("recvpacksize",Encoderparams->recvpacksize);
	flag&=loader.getParam("packhead",Encoderparams->packhead);
	flag&=loader.getParam("packtail",Encoderparams->packtail);
	return flag;
}

void releaseParamsCommunicator(void ** params)	//release params
{
	ENCODERCOMMUNICATORPARAMS * Encoderparams=(ENCODERCOMMUNICATORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERCOMMUNICATORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		delete Encoderparams;
		*params=NULL;
	}
}

bool openCommunicator(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	ENCODERCOMMUNICATORPARAMS * Encoderparams=(ENCODERCOMMUNICATORPARAMS *)params;
	*trigger=&(Encoderparams->serialport);
	triggersignal=QString(SIGNAL(readyRead()));
	Encoderparams->serialport.setPortName(Encoderparams->port);
	Encoderparams->serialport.setBaudRate(Encoderparams->baudrate);
	Encoderparams->serialport.setDataBits(Encoderparams->databitstype);
	Encoderparams->serialport.setParity(Encoderparams->paritytype);
	Encoderparams->serialport.setStopBits(Encoderparams->stopbitstype);
	Encoderparams->serialport.setFlowControl(Encoderparams->flowtype);
	Encoderparams->serialport.setTimeout(Encoderparams->timeout);
	Encoderparams->serialport.setQueryMode(Encoderparams->querymode);
	Encoderparams->databuffer.clear();
	if(!(Encoderparams->serialport.open(QIODevice::ReadWrite)))
	{
		return 0;
	}
	return 1;
}

bool receiveData(void * params, void ** receivedata)	//capture data using params and store in data
{
	ENCODERCOMMUNICATORPARAMS * Encoderparams=(ENCODERCOMMUNICATORPARAMS *)params;
	if(Encoderparams->serialport.bytesAvailable()<Encoderparams->recvpacksize)
	{
		return 0;
	}
	QByteArray datagram=Encoderparams->serialport.readAll();
	Encoderparams->databuffer.append(datagram);
	int startid=Encoderparams->databuffer.indexOf(Encoderparams->packhead);
	if(startid>=0)
	{
		int endid=Encoderparams->databuffer.indexOf(Encoderparams->packtail,startid+5);
		if((endid-5)==startid)
		{
			ENCODERCOMMUNICATORRECEIVEDATA * Encoderreceivedata=(ENCODERCOMMUNICATORRECEIVEDATA *)(*receivedata);
			if(Encoderreceivedata==NULL)
			{//case1: receivedata point to a NULL
				*receivedata=(void *)new ENCODERCOMMUNICATORRECEIVEDATA;
				Encoderreceivedata=(ENCODERCOMMUNICATORRECEIVEDATA *)(*receivedata);
			}
			else
			{//case2: Encoder point to a memory block

			}
			Encoderreceivedata->qtimestamp=QTime::currentTime();
			Encoderreceivedata->datagram=Encoderparams->databuffer.mid(startid+Encoderparams->packhead.size(),endid-(startid+Encoderparams->packhead.size()));
			Encoderparams->databuffer.clear();
			return 1;
		}
	}
	return 0;	
}

bool sendData(void * params, void * senddata)
{
	ENCODERCOMMUNICATORPARAMS * Encoderparams=(ENCODERCOMMUNICATORPARAMS *)params;
	ENCODERCOMMUNICATORSENDDATA * Encodersenddata=(ENCODERCOMMUNICATORSENDDATA *)senddata;
	qint64 n=Encoderparams->serialport.write(Encodersenddata->datagram);
	if(n>0)
	{
		return 1;
	}
	return 0;
}

bool closeCommunicator(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	ENCODERCOMMUNICATORPARAMS * Encoderparams=(ENCODERCOMMUNICATORPARAMS *)params;
	*trigger=&(Encoderparams->serialport);
	triggersignal=QString(SIGNAL(readyRead()));
	Encoderparams->serialport.close();
	return 1;
}

void flushReceiveData(void ** receivedata)	//release data
{
	ENCODERCOMMUNICATORRECEIVEDATA * Encoderreceivedata=(ENCODERCOMMUNICATORRECEIVEDATA *)(*receivedata);
	if(Encoderreceivedata==NULL)
	{//case1: receivedata point to a NULL
		
		Encoderreceivedata=(ENCODERCOMMUNICATORRECEIVEDATA *)(*receivedata);
	}
	else
	{//case2: Encoder point to a memory block
		delete Encoderreceivedata;
		*receivedata=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

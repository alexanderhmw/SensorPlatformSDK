#include "SENSOR_COMPORT.h"

#pragma comment(lib, "serialport.lib")

SENSORCOMPORT::SENSORCOMPORT()
{
	setSensorClass("COMPort");
}

SENSORCOMPORT::~SENSORCOMPORT()
{
	clearBuffer();
}

void SENSORCOMPORT::parseParam()
{
	getParam("port",port);
	getEnumParam("baudrate",baudrate);
	getEnumParam("databitstype",databitstype);
	getEnumParam("paritytype",paritytype);
	getEnumParam("stopbitstype",stopbitstype);
	getEnumParam("flowtype",flowtype);
	getParam("timeout",timeout);
	getEnumParam("querymode",querymode);
	getParam("recvpacksize",recvpacksize);
	getParam("packhead",packhead);
	getParam("packtail", packtail);

	setDataBuffer();
}

void SENSORCOMPORT::initialData(void * sensordata)
{
}

void SENSORCOMPORT::destroyData(void * sensordata)
{
}

void SENSORCOMPORT::openSensor()
{
	bool flag;
	serialcom.setPortName(port);
	serialcom.setBaudRate(baudrate);
	serialcom.setDataBits(databitstype);
	serialcom.setParity(paritytype);
	serialcom.setStopBits(stopbitstype);
	serialcom.setFlowControl(flowtype);
	serialcom.setTimeout(timeout);
	serialcom.setQueryMode(querymode);
	serialcom.close();
	if(!serialcom.open(QIODevice::ReadWrite))
	{
		emit sensorOpenError();
		return;
	}
	if(!connectSignalSlot(&serialcom,SIGNAL(readyRead()),getSensorCapObject(),SLOT(captureData())))
	{
		emit sensorOpenError();
		return;
	}
	emit sensorStart();
	return;
}

void SENSORCOMPORT::captureData()
{
	if(serialcom.bytesAvailable()>=recvpacksize )
	{//read until
		QByteArray re_data=serialcom.readAll();
		COMPORT_databuf.append(re_data);
		int startindex=COMPORT_databuf.indexOf(packhead);
		if(startindex>=0)
		{
			int endindex=COMPORT_databuf.indexOf(packtail,startindex+5);
			if((endindex-5)==startindex)
			{
			COMPORTDATA * tempdata=getDataPtr();
			tempdata->timestamp=QTime::currentTime();
			tempdata->datagram=COMPORT_databuf.mid(startindex+packhead.size(),endindex-(startindex+packhead.size()));
			emit sensorCapture();
			nextBufferPtr();
			COMPORT_databuf.clear();
			}
			else
			{
			COMPORT_databuf.clear();
			}
		}
		else
		{
			emit sensorCapError();
		}	
	}
	else
	{
		emit sensorCapError();
	}
	return;
}

void SENSORCOMPORT::closeSensor()
{
	serialcom.close();
	emit sensorStop();
	return;
}

void SENSORCOMPORT::transmitData(void * dataptr, QReadWriteLock * proclockptr)
{
	if(proclockptr!=NULL)
	{
		proclockptr->lockForRead();
	}
	QByteArray * datagram=(QByteArray *)dataptr;	
	qint64 sendsize=serialcom.write(datagram->data(),datagram->size());
	if(proclockptr!=NULL)
	{
		proclockptr->unlock();
	}
	if(sendsize>0)
	{
		emit dataTransmitted();
	}
	else
	{
		emit transmitError();
	}	
}
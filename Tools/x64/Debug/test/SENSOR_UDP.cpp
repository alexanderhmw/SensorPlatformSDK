#include "SENSOR_UDP.h"

SENSORUDP::SENSORUDP()
{
	setSensorClass("UDP");
}

SENSORUDP::~SENSORUDP()
{
	clearBuffer();
}

void SENSORUDP::parseParam()
{
	getParam("recvport",recvport);
	getParam("targetport",targetport);
	getParam("targetip",targetip);
	setDataBuffer();
}

void SENSORUDP::initialData(void * sensordata)
{
}

void SENSORUDP::destroyData(void * sensordata)
{
}

void SENSORUDP::openSensor()
{
	if(!udprecvsocket.bind(recvport))
	{
		emit sensorOpenError();
		return;
	}
	if(!connectSignalSlot(&udprecvsocket,SIGNAL(readyRead()),getSensorCapObject(),SLOT(captureData())))
	{
		emit sensorOpenError();
		return;
	}
	emit sensorStart();
	return;
}

void SENSORUDP::captureData()
{
	UDPDATA * tempdata=getDataPtr();
	if(udprecvsocket.hasPendingDatagrams())
	{
		tempdata->datagram.resize(udprecvsocket.pendingDatagramSize());
		udprecvsocket.readDatagram(tempdata->datagram.data(),tempdata->datagram.size(),&(tempdata->sender),&(tempdata->senderport));
		emit sensorCapture();
		nextBufferPtr();
	}
	else
	{
		emit sensorCapError();
	}
	return;
}

void SENSORUDP::closeSensor()
{
	udprecvsocket.close();
	udpsendsocket.close();
	emit sensorStop();
	return;
}

void SENSORUDP::transmitData(void *dataptr, QReadWriteLock * proclockptr)
{
	if(proclockptr!=NULL)
	{
		proclockptr->lockForRead();
	}
	QByteArray * datagram=(QByteArray *)dataptr;	
	qint64 sendsize=udpsendsocket.writeDatagram(*datagram,QHostAddress::QHostAddress(targetip),targetport);
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
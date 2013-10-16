#ifndef SENSOR_UDP_H
#define SENSOR_UDP_H

#include<Core\SensorFramework\SENSORBASE.h>
#include<Core\SensorFramework\TransmitterPlug\TRANSMITTERPLUG.h>

#include<qudpsocket.h>
#include<qhostaddress.h>
#include<qhostinfo.h>

struct UDPDATA
{
	QByteArray datagram;
	QHostAddress sender;
	quint16 senderport;
};

class SENSORUDP : public SENSORBASE<UDPDATA> , public TRANSMITTERPLUG
{	
protected:
	QUdpSocket udprecvsocket;
	quint16 recvport;
	QUdpSocket udpsendsocket;
	quint16 targetport;
	QString targetip;
public:
	SENSORUDP();
	~SENSORUDP();
public:
	void parseParam();
protected:
	void initialData(void * sensordata);
	void destroyData(void * sensordata);
protected slots:
	void openSensor();
	void captureData();
	void closeSensor();
protected slots:
	void transmitData(void * dataptr, QReadWriteLock * proclockptr);
};

#endif
#ifndef SENSOR_COMPORT_H
#define SENSOR_COMPORT_H

#include<Core\SensorFramework\SENSORBASE.h>
#include<Core\SensorFramework\TransmitterPlug\TRANSMITTERPLUG.h>

#include<serialport\win_qextserialport.h>

#define RE_BYTE	24
#define Pack_Head (char)0xa2
#define Pack_Tail (char)0x2a

struct COMPORTDATA
{
	QTime timestamp;
	QByteArray datagram;
};

class SENSORCOMPORT: public SENSORBASE<COMPORTDATA> , public TRANSMITTERPLUG
{
protected:
	Win_QextSerialPort serialcom;
	QString port;
	BaudRateType baudrate;
	DataBitsType databitstype;
	ParityType paritytype;
	StopBitsType stopbitstype;
	FlowType flowtype;
	long timeout;
	QextSerialBase::QueryMode querymode;
	int recvpacksize;
	QByteArray packhead;
	QByteArray packtail;
	QByteArray COMPORT_databuf;
public:
	SENSORCOMPORT();
	~SENSORCOMPORT();
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
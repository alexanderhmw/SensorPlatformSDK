#ifndef SENSOR_XWGPS_H
#define SENSOR_XWGPS_H

#include<Core\SensorFramework\SENSORBASE.h>
#include<Core\SensorFramework\TransmitterPlug\TRANSMITTERPLUG.h>
//#include<Device\Sensor\XWGPS\GpsLib.h>
#include <Device\Sensor\UBLOX\CoordinateConvertion.h>
//#include<Device\Sensor\XWGPS\CoordinateConvertion.h>
#include<serialport\win_qextserialport.h>
#include<QFile>
#include<QDateTime>

#define PI 3.141592653589

struct point3d1{
	double		x,y,z;
} ;

struct GPSrecord{
	long		milli;
	point3d1		ang;
	point3d1		shv;
	BYTE		gpsstatus;
} ;

struct XWGPSDATA
{
	double gpstime;
//	QByteArray GLLdatagram;
//	QByteArray ZDAdatagram;
	QByteArray FPDdatagram;
	GPSrecord data;
	int valid;
	QByteArray log;
};




class SENSORXWGPS: public SENSORBASE<XWGPSDATA> , public TRANSMITTERPLUG
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
	//databuff  until get the header and the tail..
	QByteArray XWGPS_databuf;
	QFile fp;
	FILE* fout;
public:
	SENSORXWGPS();
	~SENSORXWGPS();
private:
	void datatransfer(int startindex, int endindex, int valid);
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
#include "SENSOR_XWGPS.h"

#pragma comment(lib, "serialport.lib")

SENSORXWGPS::SENSORXWGPS()
{
	setSensorClass("XWGPS");
}

SENSORXWGPS::~SENSORXWGPS()
{
	clearBuffer();
}

void SENSORXWGPS::parseParam()
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

void SENSORXWGPS::initialData(void * sensordata)
{
}

void SENSORXWGPS::destroyData(void * sensordata)
{
}
#define Enable_log
void SENSORXWGPS::openSensor()
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
#ifdef Enable_log
	
	QString f_name=QString("C:\\POSS_Demo\\HMW-Alexander\\SensingPlatform\\SensingPlatform\\data\\log\\XWGPS_LOG");
	f_name.append(QDateTime::currentDateTime().toString("_yyyyMMdd_hhmmss"));
	f_name.append(".log");

	//fout = fopen(f_name.toAscii(),"w");

	
	fp.setFileName(f_name);

	if (!fp.open(QFile::WriteOnly | QFile::Text))
	{
		int tmpdebug;
		tmpdebug=0;
	}
	
#endif
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

static const char *HeaderGLL = "$GPGLL" ;
static const char *HeaderZDA = "$GPZDA" ;
static const char *HeaderFPD = "$GPFPD" ;
static const char *EndGLL= "\r\n";
static const char *Invalid=",,,";
void SENSORXWGPS::captureData()
{
	if(serialcom.bytesAvailable()>=recvpacksize )
	{//read until
		QByteArray tmp_data=serialcom.readAll();
		XWGPS_databuf.append(tmp_data);

		int startindex = XWGPS_databuf.indexOf(HeaderFPD); 
		if(startindex>=0)
		{
			int endindex = XWGPS_databuf.indexOf(EndGLL,startindex);
			int valid= XWGPS_databuf.indexOf(Invalid,startindex);
			if(endindex>startindex)
			{
			//	if(valid==-1)
				datatransfer(startindex, endindex, valid);
				//save log
				#ifdef Enable_log
				fp.write(XWGPS_databuf);
				#endif
			XWGPS_databuf.clear();
			}
		}
		else
		{
			emit sensorCapError();
		}	
	}
	return;
}

void SENSORXWGPS::closeSensor()
{
	serialcom.close();
	#ifdef Enable_log
	//fclose(fout);
	fp.close();
	#endif
	emit sensorStop();
	return;
}

void SENSORXWGPS::transmitData(void * dataptr, QReadWriteLock * proclockptr)
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

void SENSORXWGPS::datatransfer(int startindex, int endindex, int valid)
{				
	char N,E,Valid;
	int dumy;
	bool gpsOn=true;
	double	gpstime,heading,pitch,roll;
	double	lat=0, lon=0,altitude=0;
	double	lbh[3], xyz[3], dat[4];

	XWGPSDATA * tempdata=getDataPtr();
	tempdata->data.milli=((QTime::currentTime().hour()*60+QTime::currentTime().minute())*60
	+QTime::currentTime().second())*1000+(QTime::currentTime()).msec();
	tempdata->FPDdatagram=XWGPS_databuf.mid(startindex+sizeof(HeaderGLL)-1,endindex-(startindex+sizeof(HeaderGLL))-5);
	sscanf(tempdata->FPDdatagram.data(),"%lf,%c,%lf,%c,%lf,%c",&lat,&N,&lon,&E,&gpstime,&Valid);
	tempdata->valid=valid;
	//if (tempdata->valid==-1) {
	//	sscanf(tempdata->FPDdatagram.data(),"%d,%lf,%lf,%lf,%lf",&dumy,&gpstime,&heading,&pitch,&roll);
	//	xyz[0] = xyz[1] = xyz[2] = 0;
	//	gpsOn=false;
	//}
	//else
	{
		sscanf(tempdata->FPDdatagram.data(),"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&dumy,&gpstime,&heading,&pitch,&roll,
			&lat,&lon,&altitude);
		lbh[0] = lat;
		lbh[1] = lon;
		lbh[2] = altitude;
		CCoordinateConvertion	ctest;
		SetCoordinateParameters(_BEIJINGLOCAL);
		ctest.GPS84LBH_LocalXYZ (lbh, xyz);
	}
	tempdata->gpstime=gpstime;
	tempdata->data.ang.x = pitch*PI/180.0;
	tempdata->data.ang.y = roll*PI/180.0;
	tempdata->data.ang.z = -heading*PI/180.0;
	tempdata->data.shv.y = xyz[0];
	tempdata->data.shv.x = xyz[1];
	tempdata->data.shv.z = xyz[2];
	tempdata->data.gpsstatus = gpsOn?1:0;


	emit sensorCapture();
	nextBufferPtr();
}
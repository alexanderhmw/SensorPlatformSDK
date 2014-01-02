#include "SICKLMS.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	SICKLMSSENSORPARAMS * SICKLMSparams=(SICKLMSSENSORPARAMS *)(*params);
	if(SICKLMSparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new SICKLMSSENSORPARAMS;
		SICKLMSparams=(SICKLMSSENSORPARAMS *)(*params);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("port",SICKLMSparams->port);
	flag&=loader.getEnumParam("baudrate",SICKLMSparams->baudrate);
	flag&=loader.getEnumParam("resultion",SICKLMSparams->resolution);
	flag&=loader.getEnumParam("measurement",SICKLMSparams->measurement);
	return flag;
}

void releaseParamsSensor(void ** params)	//release params
{
	SICKLMSSENSORPARAMS * SICKLMSparams=(SICKLMSSENSORPARAMS *)(*params);
	if(SICKLMSparams==NULL)
	{//case1: params point to a NULL
		
		SICKLMSparams=(SICKLMSSENSORPARAMS *)(*params);
	}
	else
	{//case2: SICKLMS point to a memory block
		delete SICKLMSparams;
		*params=NULL;
	}
}

bool openSensor(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	SICKLMSSENSORPARAMS * SICKLMSparams=(SICKLMSSENSORPARAMS *)params;
	*trigger=&(SICKLMSparams->serialport);
	triggersignal=QString(SIGNAL(readyRead()));
	SICKLMSparams->serialport.setPortName(SICKLMSparams->port);
	SICKLMSparams->serialport.setBaudRate(BAUD9600);
	SICKLMSparams->serialport.setDataBits(DATA_8);
	SICKLMSparams->serialport.setParity(PAR_NONE);
	SICKLMSparams->serialport.setStopBits(STOP_1);
	SICKLMSparams->serialport.setFlowControl(FLOW_OFF);
	SICKLMSparams->serialport.setTimeout(500);
	SICKLMSparams->serialport.setQueryMode(QextSerialPort::EventDriven);
	if(!(SICKLMSparams->serialport.open(QIODevice::WriteOnly)))
	{
		return 0;
	}
	char	cmd_baudrate9600[]={ 0x02,0x00,0x02,0x00,0x20,0x42,0x52,0x08 };
	char	cmd_baudrate19200[]={ 0x02,0x00,0x02,0x00,0x20,0x41,0x51,0x08 }; 
	char	cmd_baudrate38400[]={ 0x02,0x00,0x02,0x00,0x20,0x40,0x50,0x08 };
	char	cmd_baudrate500k[]={ 0x02,0x00,0x02,0x00,0x20,0x48,0x58,0x08 };
	BaudRateType baudrate;
	switch(SICKLMSparams->baudrate)
	{
	case BAUD_9600:
		baudrate=BAUD9600;
		SICKLMSparams->serialport.write(cmd_baudrate9600,8);
		break;
	case BAUD_19200:
		baudrate=BAUD19200;
		SICKLMSparams->serialport.write(cmd_baudrate19200,8);
		break;
	case BAUD_38400:
		baudrate=BAUD38400;
		SICKLMSparams->serialport.write(cmd_baudrate38400,8);
		break;
	case BAUD_500000:
		baudrate=BAUD500000;
		SICKLMSparams->serialport.write(cmd_baudrate500k,8);
		break;
	}
	SICKLMSparams->serialport.close();
	SICKLMSparams->serialport.setBaudRate(baudrate);
	if(!(SICKLMSparams->serialport.open(QIODevice::ReadWrite)))
	{
		return 0;
	}
	char	cmd_180_050[]={ 0x02,0x00,0x05,0x00,0x3B,0xB4,0x00,0x32,0x00,0x3B,0x1F };
	char	cmd_180_100[]={ 0x02,0x00,0x05,0x00,0x3B,0xB4,0x00,0x64,0x00,0x97,0x49 };
	char	cmd_100_025[]={ 0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x19,0x00,0xE7,0x72 };
	char	cmd_100_050[]={ 0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x32,0x00,0xB1,0x59 };
	char	cmd_100_100[]={ 0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x64,0x00,0x1D,0x0F };
	char cmd_180_025[]={  0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x19,0x00,0xE7,0x72 } ; 
	switch(SICKLMSparams->resolution)
	{
	case RES_180_050:
		SICKLMSparams->serialport.write(cmd_180_050,11);
		break;
	case RES_180_100:
		SICKLMSparams->serialport.write(cmd_180_100,11);
		break;
	case RES_100_025:
		SICKLMSparams->serialport.write(cmd_100_025,11);
		break;
	case RES_100_050:
		SICKLMSparams->serialport.write(cmd_100_050,11);
		break;
	case RES_100_100:
		SICKLMSparams->serialport.write(cmd_100_100,11);
		break;
	case RES_180_025:
		SICKLMSparams->serialport.write(cmd_180_025,11);
		break;
	}
	char	cmd_lmssetmode[]={ 0x02,0x00,0x0A,0x00,0x20,0x00,0x53,0x49,0x43,0x4B,0x5F,0x4C,0x4D,0x53,0xBE,0xC5 };
	SICKLMSparams->serialport.write(cmd_lmssetmode,16);
	char	cmd_cm_mode[]=
		{0x02,0x00,0x21,0x00,0x77,0x00,0x00,0x46,
		0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0xC7,0x25 };
	char	cmd_mm_mode[]=
		{ 0x02,0x00,0x21,0x00,0x77,0x00,0x00,0x46,
		0x00,0x00,0x00,0x01,0x00,0x00,0x02,0x02,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0xD3,0x29 };
	switch(SICKLMSparams->measurement)
	{
	case UNIT_CM:
		SICKLMSparams->serialport.write(cmd_cm_mode,39);
		break;
	case UNIT_MM:
		SICKLMSparams->serialport.write(cmd_mm_mode,39);
		break;
	}

}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	SICKLMSSENSORPARAMS * SICKLMSparams=(SICKLMSSENSORPARAMS *)params;
	SICKLMSSENSORDATA * SICKLMSdata=(SICKLMSSENSORDATA *)(*data);
	if(SICKLMSdata==NULL)
	{//case1: data point to a NULL
		
		SICKLMSdata=(SICKLMSSENSORDATA *)(*data);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

bool closeSensor(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	SICKLMSSENSORPARAMS * SICKLMSparams=(SICKLMSSENSORPARAMS *)params;
}

void releaseData(void ** data)	//release data
{
	SICKLMSSENSORDATA * SICKLMSdata=(SICKLMSSENSORDATA *)(*data);
	if(SICKLMSdata==NULL)
	{//case1: data point to a NULL
		
		SICKLMSdata=(SICKLMSSENSORDATA *)(*data);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

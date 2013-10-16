#include "Encoder.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	ENCODERSENSORPARAMS * Encoderparams=(ENCODERSENSORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSENSORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void releaseParamsSensor(void ** params)	//release params
{
	ENCODERSENSORPARAMS * Encoderparams=(ENCODERSENSORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSENSORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

bool openSensor(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	ENCODERSENSORPARAMS * Encoderparams=(ENCODERSENSORPARAMS *)params;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	ENCODERSENSORPARAMS * Encoderparams=(ENCODERSENSORPARAMS *)params;
	ENCODERSENSORDATA * Encoderdata=(ENCODERSENSORDATA *)(*data);
	if(Encoderdata==NULL)
	{//case1: data point to a NULL
		
		Encoderdata=(ENCODERSENSORDATA *)(*data);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

bool closeSensor(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	ENCODERSENSORPARAMS * Encoderparams=(ENCODERSENSORPARAMS *)params;
}

void releaseData(void ** data)	//release data
{
	ENCODERSENSORDATA * Encoderdata=(ENCODERSENSORDATA *)(*data);
	if(Encoderdata==NULL)
	{//case1: data point to a NULL
		
		Encoderdata=(ENCODERSENSORDATA *)(*data);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

#include "XWGPS.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XWGPSSENSORPARAMS * XWGPSparams=(XWGPSSENSORPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		
		XWGPSparams=(XWGPSSENSORPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

void releaseParamsSensor(void ** params)	//release params
{
	XWGPSSENSORPARAMS * XWGPSparams=(XWGPSSENSORPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		
		XWGPSparams=(XWGPSSENSORPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

bool openSensor(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	XWGPSSENSORPARAMS * XWGPSparams=(XWGPSSENSORPARAMS *)params;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	XWGPSSENSORPARAMS * XWGPSparams=(XWGPSSENSORPARAMS *)params;
	XWGPSSENSORDATA * XWGPSdata=(XWGPSSENSORDATA *)(*data);
	if(XWGPSdata==NULL)
	{//case1: data point to a NULL
		
		XWGPSdata=(XWGPSSENSORDATA *)(*data);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

bool closeSensor(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	XWGPSSENSORPARAMS * XWGPSparams=(XWGPSSENSORPARAMS *)params;
}

void releaseData(void ** data)	//release data
{
	XWGPSSENSORDATA * XWGPSdata=(XWGPSSENSORDATA *)(*data);
	if(XWGPSdata==NULL)
	{//case1: data point to a NULL
		
		XWGPSdata=(XWGPSSENSORDATA *)(*data);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

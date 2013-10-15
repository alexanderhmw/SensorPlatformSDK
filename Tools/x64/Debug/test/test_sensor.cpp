#include "test.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	TESTSENSORPARAMS * testparams=(TESTSENSORPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTSENSORPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsSensor(void ** params)	//release params
{
	TESTSENSORPARAMS * testparams=(TESTSENSORPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTSENSORPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool openSensor(void * params)	//open the sensor using params
{
	TESTSENSORPARAMS * testparams=(TESTSENSORPARAMS *)params;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	TESTSENSORPARAMS * testparams=(TESTSENSORPARAMS *)params;
	TESTSENSORDATA * testdata=(TESTSENSORDATA *)(*data);
	if(testdata==NULL)
	{//case1: data point to a NULL
		
		testdata=(TESTSENSORDATA *)(*data);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool closeSensor(void * params)	//close the sensor using params
{
	TESTSENSORPARAMS * testparams=(TESTSENSORPARAMS *)params;
}

void releaseData(void ** data)	//release data
{
	TESTSENSORDATA * testdata=(TESTSENSORDATA *)(*data);
	if(testdata==NULL)
	{//case1: data point to a NULL
		
		testdata=(TESTSENSORDATA *)(*data);
	}
	else
	{//case2: test point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

#include "test.h"
#include<FuncLibrary\transmitterfunc.h>

bool loadParamsTransmitter(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	TESTTRANSMITTERPARAMS * testparams=(TESTTRANSMITTERPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTTRANSMITTERPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsTransmitter(void ** params)	//release params
{
	TESTTRANSMITTERPARAMS * testparams=(TESTTRANSMITTERPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTTRANSMITTERPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool openTransmitter(void * params, void * nodeparams)	//open for transmit
{
	TESTTRANSMITTERPARAMS * testparams=(TESTTRANSMITTERPARAMS *)params;
}

bool transmitData(void * params, void * data)	//transmit data
{
	TESTTRANSMITTERPARAMS * testparams=(TESTTRANSMITTERPARAMS *)params;
	TESTSTRANSMITTERDATA * testdata=(TESTSTRANSMITTERDATA *)data;
}

bool closeTransmitter(void * params)	//close transmitter
{
	TESTTRANSMITTERPARAMS * testparams=(TESTTRANSMITTERPARAMS *)params;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

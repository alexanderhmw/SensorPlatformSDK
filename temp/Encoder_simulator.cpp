#include "Encoder.h"
#include<FuncLibrary\simulatorfunc.h>

bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void releaseParamsSimulator(void ** params)	//release params
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

bool openSimulator(void * params)
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)params;
}

long loadData(void * params, void ** data)
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)params;
	ENCODERSIMULATORDATA * Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	if(Encoderdata==NULL)
	{//case1: data point to a NULL
		
		Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

bool closeSimulator(void * params)
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)params;
}

void dumpData(void ** data)
{
	ENCODERSIMULATORDATA * Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	if(Encoderdata==NULL)
	{//case1: data point to a NULL
		
		Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

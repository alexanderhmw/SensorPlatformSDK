#include "Encoder.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void releaseParamsStorage(void ** params)	//release params
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
}

bool storeData(void * params, void * data)	//store data
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
	ENCODERSTORAGEDATA * Encoderdata=(ENCODERSTORAGEDATA *)data;
}

bool closeStorage(void * params)	//close storage
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

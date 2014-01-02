#include "SICKLMS.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	SICKLMSSTORAGEPARAMS * SICKLMSparams=(SICKLMSSTORAGEPARAMS *)(*params);
	if(SICKLMSparams==NULL)
	{//case1: params point to a NULL
		
		SICKLMSparams=(SICKLMSSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

void releaseParamsStorage(void ** params)	//release params
{
	SICKLMSSTORAGEPARAMS * SICKLMSparams=(SICKLMSSTORAGEPARAMS *)(*params);
	if(SICKLMSparams==NULL)
	{//case1: params point to a NULL
		
		SICKLMSparams=(SICKLMSSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	SICKLMSSTORAGEPARAMS * SICKLMSparams=(SICKLMSSTORAGEPARAMS *)params;
}

bool storeData(void * params, void * data)	//store data
{
	SICKLMSSTORAGEPARAMS * SICKLMSparams=(SICKLMSSTORAGEPARAMS *)params;
	SICKLMSSTORAGEDATA * SICKLMSdata=(SICKLMSSTORAGEDATA *)data;
}

bool closeStorage(void * params)	//close storage
{
	SICKLMSSTORAGEPARAMS * SICKLMSparams=(SICKLMSSTORAGEPARAMS *)params;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

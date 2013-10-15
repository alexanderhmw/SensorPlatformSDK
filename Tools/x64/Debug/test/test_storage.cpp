#include "test.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	TESTSTORAGEPARAMS * testparams=(TESTSTORAGEPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsStorage(void ** params)	//release params
{
	TESTSTORAGEPARAMS * testparams=(TESTSTORAGEPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	TESTSTORAGEPARAMS * testparams=(TESTSTORAGEPARAMS *)params;
}

bool storeData(void * params, void * data)	//store data
{
	TESTSTORAGEPARAMS * testparams=(TESTSTORAGEPARAMS *)params;
	TESTSTORAGEDATA * testdata=(TESTSTORAGEDATA *)data;
}

bool closeStorage(void * params)	//close storage
{
	TESTSTORAGEPARAMS * testparams=(TESTSTORAGEPARAMS *)params;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

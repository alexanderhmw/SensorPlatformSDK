#include "XWGPS.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		
		XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

void releaseParamsStorage(void ** params)	//release params
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	if(XWGPSparams==NULL)
	{//case1: params point to a NULL
		
		XWGPSparams=(XWGPSSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
}

bool storeData(void * params, void * data)	//store data
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
	XWGPSSTORAGEDATA * XWGPSdata=(XWGPSSTORAGEDATA *)data;
}

bool closeStorage(void * params)	//close storage
{
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

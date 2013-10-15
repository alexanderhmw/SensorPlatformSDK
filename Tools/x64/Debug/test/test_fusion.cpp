#include "test.h"
#include<FuncLibrary\fusionfunc.h>

bool loadParamsFusion(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTFUSIONPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsFusion(void ** params)	//release params
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTFUSIONPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void getSupportInputNodes(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename)
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)params;
}

bool openFusion (void * params)
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)params;
}

bool inputData (void * params, int typeclassid, int nameid, void * data, void ** inputdata)
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)params;
}

bool fuseData (void * params, QVector<QVector<QVector<void *>>> inputdataset, void ** outputdata)
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)params;
	TESTFUSIONOUTPUTDATA * testoutputdata=(TESTFUSIONOUTPUTDATA *)(*outputdata);
	if(testoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		testoutputdata=(TESTFUSIONOUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool closeFusion (void * params)
{
	TESTFUSIONPARAMS * testparams=(TESTFUSIONPARAMS *)params;
}

void releaseInputData (int typeclassid, int nameid, void ** outputdata)
{
	TESTFUSIONOUTPUTDATA * testoutputdata=(TESTFUSIONOUTPUTDATA *)(*outputdata);
	if(testoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		testoutputdata=(TESTFUSIONOUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseOutputData (void ** inputdata)
{
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

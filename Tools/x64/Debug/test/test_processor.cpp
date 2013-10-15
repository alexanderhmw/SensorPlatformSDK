#include "test.h"
#include<FuncLibrary\processorfunc.h>

bool loadParamsProcessor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	TESTPROCESSORPARAMS * testparams=(TESTPROCESSORPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTPROCESSORPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsProcessor(void ** params)	//release params
{
	TESTPROCESSORPARAMS * testparams=(TESTPROCESSORPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTPROCESSORPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool openProcessor(void * params)	//open the processor using params
{
	TESTPROCESSORPARAMS * testparams=(TESTPROCESSORPARAMS *)params;
}

bool inputData(void * params, void * data, void ** inputdata)	//input data and store in inputdata
{
	TESTPROCESSORPARAMS * testparams=(TESTPROCESSORPARAMS *)params;
	TESTPROCESSORINPUTDATA * testinputdata=(TESTPROCESSORINPUTDATA *)(*inputdata);
	if(testinputdata==NULL)
	{//case1: inputdata point to a NULL
		
		testinputdata=(TESTPROCESSORINPUTDATA *)(*inputdata);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool processData(void * params, QVector<void *> inputdataset, void **outputdata)	//process inputdataset and store in outputdata
{
	TESTPROCESSORPARAMS * testparams=(TESTPROCESSORPARAMS *)params;
	TESTPROCESSOROUTPUTDATA * testoutputdata=(TESTPROCESSOROUTPUTDATA *)(*outputdata);
	if(testoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		testoutputdata=(TESTPROCESSOROUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool closeProcessor(void * params)	//close the processor using params
{
	TESTPROCESSORPARAMS * testparams=(TESTPROCESSORPARAMS *)params;
}

void releaseInputData(void ** inputdata)	//release inputdata
{
	TESTPROCESSORINPUTDATA * testinputdata=(TESTPROCESSORINPUTDATA *)(*inputdata);
	if(testinputdata==NULL)
	{//case1: inputdata point to a NULL
		
		testinputdata=(TESTPROCESSORINPUTDATA *)(*inputdata);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseOutputData(void ** outputdata)	//release outputdata
{
	TESTPROCESSOROUTPUTDATA * testoutputdata=(TESTPROCESSOROUTPUTDATA *)(*outputdata);
	if(testoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		testoutputdata=(TESTPROCESSOROUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: test point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

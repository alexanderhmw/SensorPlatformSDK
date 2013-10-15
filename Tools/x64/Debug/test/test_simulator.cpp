#include "test.h"
#include<FuncLibrary\simulatorfunc.h>

bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	TESTSIMULATORPARAMS * testparams=(TESTSIMULATORPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsSimulator(void ** params)	//release params
{
	TESTSIMULATORPARAMS * testparams=(TESTSIMULATORPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool openSimulator(void * params)
{
	TESTSIMULATORPARAMS * testparams=(TESTSIMULATORPARAMS *)params;
}

long loadData(void * params, void ** data)
{
	TESTSIMULATORPARAMS * testparams=(TESTSIMULATORPARAMS *)params;
	TESTSIMULATORDATA * testdata=(TESTSIMULATORDATA *)(*data);
	if(testdata==NULL)
	{//case1: data point to a NULL
		
		testdata=(TESTSIMULATORDATA *)(*data);
	}
	else
	{//case2: test point to a memory block
		
	}
}

bool closeSimulator(void * params)
{
	TESTSIMULATORPARAMS * testparams=(TESTSIMULATORPARAMS *)params;
}

void dumpData(void ** data)
{
	TESTSIMULATORDATA * testdata=(TESTSIMULATORDATA *)(*data);
	if(testdata==NULL)
	{//case1: data point to a NULL
		
		testdata=(TESTSIMULATORDATA *)(*data);
	}
	else
	{//case2: test point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

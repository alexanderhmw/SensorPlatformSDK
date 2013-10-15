#include "test.h"
#include<FuncLibrary\distributionfunc.h>

bool loadParamsDistribution(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	TESTDISTRIBUTIONPARAMS * testparams=(TESTDISTRIBUTIONPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTDISTRIBUTIONPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void releaseParamsDistribution(void ** params)	//release params
{
	TESTDISTRIBUTIONPARAMS * testparams=(TESTDISTRIBUTIONPARAMS *)(*params);
	if(testparams==NULL)
	{//case1: params point to a NULL
		
		testparams=(TESTDISTRIBUTIONPARAMS *)(*params);
	}
	else
	{//case2: test point to a memory block
		
	}
}

void getSupportOutputNodes(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename)
{
	TESTDISTRIBUTIONPARAMS * testparams=(TESTDISTRIBUTIONPARAMS *)params;
}

bool openDistribution(void * params)
{
	TESTDISTRIBUTIONPARAMS * testparams=(TESTDISTRIBUTIONPARAMS *)params;
}

bool parseDataFptr(void * params, void * data, QVector<QVector<int>> & distids)
{
	TESTDISTRIBUTIONPARAMS * testparams=(TESTDISTRIBUTIONPARAMS *)params;
	TESTDISTRIBUTIONDATA * testdata=(TESTDISTRIBUTIONDATA *)data;
}

bool closeDistribution(void * params)
{
	TESTDISTRIBUTIONPARAMS * testparams=(TESTDISTRIBUTIONPARAMS *)params;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

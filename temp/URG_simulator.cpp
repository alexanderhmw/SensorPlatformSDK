#include "URG.h"
#include<FuncLibrary\simulatorfunc.h>

bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		
		URGparams=(URGSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		
	}
}

void releaseParamsSimulator(void ** params)	//release params
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		
		URGparams=(URGSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		
	}
}

bool openSimulator(void * params)
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)params;
}

long loadData(void * params, void ** data)
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)params;
	URGSIMULATORDATA * URGdata=(URGSIMULATORDATA *)(*data);
	if(URGdata==NULL)
	{//case1: data point to a NULL
		
		URGdata=(URGSIMULATORDATA *)(*data);
	}
	else
	{//case2: URG point to a memory block
		
	}
}

bool closeSimulator(void * params)
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)params;
}

void dumpData(void ** data)
{
	URGSIMULATORDATA * URGdata=(URGSIMULATORDATA *)(*data);
	if(URGdata==NULL)
	{//case1: data point to a NULL
		
		URGdata=(URGSIMULATORDATA *)(*data);
	}
	else
	{//case2: URG point to a memory block
		
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

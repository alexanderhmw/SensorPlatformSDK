#include "Planning.h"
#include<FuncLibrary\fusionfunc.h>

bool loadParamsFusion(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)(*params);
	if(Planningparams==NULL)
	{//case1: params point to a NULL
		
		Planningparams=(PLANNINGFUSIONPARAMS *)(*params);
	}
	else
	{//case2: Planning point to a memory block
		
	}
}

void releaseParamsFusion(void ** params)	//release params
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)(*params);
	if(Planningparams==NULL)
	{//case1: params point to a NULL
		
		Planningparams=(PLANNINGFUSIONPARAMS *)(*params);
	}
	else
	{//case2: Planning point to a memory block
		
	}
}

void getSupportInputNodes(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename)
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)params;
}

bool openFusion (void * params)
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)params;
}

bool inputData (void * params, int typeclassid, int nameid, void * data, void ** inputdata)
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)params;
}

bool fuseData (void * params, QVector<QVector<QVector<void *>>> inputdataset, void ** outputdata)
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)params;
	PLANNINGFUSIONOUTPUTDATA * Planningoutputdata=(PLANNINGFUSIONOUTPUTDATA *)(*outputdata);
	if(Planningoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		Planningoutputdata=(PLANNINGFUSIONOUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: Planning point to a memory block
		
	}
}

bool closeFusion (void * params)
{
	PLANNINGFUSIONPARAMS * Planningparams=(PLANNINGFUSIONPARAMS *)params;
}

void releaseInputData (int typeclassid, int nameid, void ** outputdata)
{
	PLANNINGFUSIONOUTPUTDATA * Planningoutputdata=(PLANNINGFUSIONOUTPUTDATA *)(*outputdata);
	if(Planningoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		Planningoutputdata=(PLANNINGFUSIONOUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: Planning point to a memory block
		
	}
}

void releaseOutputData (void ** inputdata)
{
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

#include "Odometry.h"
#include<FuncLibrary\processorfunc.h>

bool loadParamsProcessor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	ODOMETRYPROCESSORPARAMS * Odometryparams=(ODOMETRYPROCESSORPARAMS *)(*params);
	if(Odometryparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new ODOMETRYPROCESSORPARAMS;
		Odometryparams=(ODOMETRYPROCESSORPARAMS *)(*params);
	}
	else
	{//case2: Odometry point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("curx",Odometryparams->curx);
	flag&=loader.getParam("cury",Odometryparams->cury);
	flag&=loader.getParam("curtheta",Odometryparams->curtheta);
	flag&=loader.getParam("stepsize",Odometryparams->stepsize);
	return flag;
}

void releaseParamsProcessor(void ** params)	//release params
{
	ODOMETRYPROCESSORPARAMS * Odometryparams=(ODOMETRYPROCESSORPARAMS *)(*params);
	if(Odometryparams==NULL)
	{//case1: params point to a NULL
		
		Odometryparams=(ODOMETRYPROCESSORPARAMS *)(*params);
	}
	else
	{//case2: Odometry point to a memory block
		delete Odometryparams;
		*params=NULL;
	}
}

bool openProcessor(void * params)	//open the processor using params
{
	ODOMETRYPROCESSORPARAMS * Odometryparams=(ODOMETRYPROCESSORPARAMS *)params;
	return 1;
}

bool inputData(void * params, void * data, void ** inputdata)	//input data and store in inputdata
{
	ODOMETRYPROCESSORPARAMS * Odometryparams=(ODOMETRYPROCESSORPARAMS *)params;
	ODOMETRYPROCESSORINPUTDATA * Odometryinputdata=(ODOMETRYPROCESSORINPUTDATA *)(*inputdata);
	if(Odometryinputdata==NULL)
	{//case1: inputdata point to a NULL
		*inputdata=(void *)new ODOMETRYPROCESSORINPUTDATA;
		Odometryinputdata=(ODOMETRYPROCESSORINPUTDATA *)(*inputdata);
	}
	else
	{//case2: Odometry point to a memory block
		
	}
	memcpy(*inputdata,data,sizeof(ODOMETRYPROCESSORINPUTDATA));
	return 1;
}

bool processData(void * params, QVector<void *> inputdataset, void **outputdata)	//process inputdataset and store in outputdata
{
	ODOMETRYPROCESSORPARAMS * Odometryparams=(ODOMETRYPROCESSORPARAMS *)params;
	ODOMETRYPROCESSOROUTPUTDATA * Odometryoutputdata=(ODOMETRYPROCESSOROUTPUTDATA *)(*outputdata);
	if(Odometryoutputdata==NULL)
	{//case1: outputdata point to a NULL
		*outputdata=(void *)new ODOMETRYPROCESSOROUTPUTDATA;
		Odometryoutputdata=(ODOMETRYPROCESSOROUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: Odometry point to a memory block
		
	}
	//================================
	if(inputdataset.size()<2)
	{
		return 0;
	}
	int id=inputdataset.size()-1;
	ODOMETRYPROCESSORINPUTDATA * curdata=(ODOMETRYPROCESSORINPUTDATA *) inputdataset[id];
	ODOMETRYPROCESSORINPUTDATA * prevdata=(ODOMETRYPROCESSORINPUTDATA *) inputdataset[id-1];
	short angle=*((short *)(curdata->datagram.data()));
	short d0 = *((short *)(curdata->datagram.data()+sizeof(angle)));
	short d1 = *((short *)(prevdata->datagram.data()+sizeof(angle)));
	short encoder= d0 - d1 ;
	static double PI = 3.1415926535897932384626433832795;
	double curOrientation = (angle)*PI/1800.0;
	if(encoder < -15000)
		encoder += 30000.0;
	double delta = encoder * Odometryparams->stepsize;
	Odometryparams->curx = Odometryparams->curx + delta*cos(curOrientation);
	Odometryparams->cury = Odometryparams->cury + delta*sin(curOrientation);
	Odometryoutputdata->theta = curOrientation;
	Odometryoutputdata->x = Odometryparams->curx;
	Odometryoutputdata->y = Odometryparams->cury;
	Odometryoutputdata->qtimestamp = curdata->qtimestamp;
	//================================
	return 1;
}

bool closeProcessor(void * params)	//close the processor using params
{
	ODOMETRYPROCESSORPARAMS * Odometryparams=(ODOMETRYPROCESSORPARAMS *)params;
	return 1;
}

void releaseInputData(void ** inputdata)	//release inputdata
{
	ODOMETRYPROCESSORINPUTDATA * Odometryinputdata=(ODOMETRYPROCESSORINPUTDATA *)(*inputdata);
	if(Odometryinputdata==NULL)
	{//case1: inputdata point to a NULL
		
		Odometryinputdata=(ODOMETRYPROCESSORINPUTDATA *)(*inputdata);
	}
	else
	{//case2: Odometry point to a memory block
		delete Odometryinputdata;
		*inputdata=NULL;
	}
}

void releaseOutputData(void ** outputdata)	//release outputdata
{
	ODOMETRYPROCESSOROUTPUTDATA * Odometryoutputdata=(ODOMETRYPROCESSOROUTPUTDATA *)(*outputdata);
	if(Odometryoutputdata==NULL)
	{//case1: outputdata point to a NULL
		
		Odometryoutputdata=(ODOMETRYPROCESSOROUTPUTDATA *)(*outputdata);
	}
	else
	{//case2: Odometry point to a memory block
		delete Odometryoutputdata;
		*outputdata=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

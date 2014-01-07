#include "URG.h"
#include<FuncLibrary\simulatorfunc.h>

bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)(*params);
	if(URGparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new URGSIMULATORPARAMS;
		URGparams=(URGSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: URG point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("datafile",URGparams->datafile);
	return flag;
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
		delete URGparams;
		*params=NULL;
	}
}

bool openSimulator(void * params)
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)params;
	URGparams->lmsFile.setFileName(URGparams->datafile);
	if(URGparams->lmsFile.open(QFile::ReadOnly))
	{
		float angrng, angres, unit;
		URGparams->lmsFile.read((char*)&angrng,sizeof(angrng));
		URGparams->lmsFile.read((char*)&angres,sizeof(angres));
		URGparams->lmsFile.read((char*)&unit,sizeof(unit));
		URGparams->dataNum = int(angrng / angres) + 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

long loadData(void * params, void ** data)
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)params;
	URGSIMULATORDATA * URGdata=(URGSIMULATORDATA *)(*data);
	if(URGdata==NULL)
	{//case1: data point to a NULL
		*data=(void *)new URGSIMULATORDATA;
		URGdata=(URGSIMULATORDATA *)(*data);
		URGdata->data = new short[URGparams->dataNum];
	}
	else
	{//case2: URG point to a memory block
		
	}
	if(URGparams->lmsFile.atEnd())
	{
		return -1;
	}
	else
	{
		URGparams->lmsFile.read((char*)&(URGdata->timestamp),sizeof(URGdata->timestamp));
		URGdata->qtimestamp=QTime(0,0,0,0).addMSecs(URGdata->timestamp);
		URGdata->datasize = URGparams->dataNum;
		URGparams->lmsFile.read((char*)(URGdata->data),URGdata->datasize*sizeof(short));
		return URGdata->timestamp;
	}
}

bool closeSimulator(void * params)
{
	URGSIMULATORPARAMS * URGparams=(URGSIMULATORPARAMS *)params;
	URGparams->lmsFile.close();
	return 1;
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
		delete [] (URGdata->data);
		delete URGdata;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

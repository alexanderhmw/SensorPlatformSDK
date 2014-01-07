#include "PointGreyFlea2.h"
#include<FuncLibrary\simulatorfunc.h>

bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
	if(PointGreyFlea2params==NULL)
	{//case1: params point to a NULL
		*params=(void *)new POINTGREYFLEA2SIMULATORPARAMS;
		PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("datafile",PointGreyFlea2params->datafile);
	return flag;
}

void releaseParamsSimulator(void ** params)	//release params
{
	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
	if(PointGreyFlea2params==NULL)
	{//case1: params point to a NULL
		
		PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2params;
		*params=NULL;
	}
}

bool openSimulator(void * params)
{
	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)params;
	PointGreyFlea2params->videoCap.open(PointGreyFlea2params->datafile.toStdString());
	if(!PointGreyFlea2params->videoCap.isOpened())
	{
		return 0;
	}
	QString logFPath = PointGreyFlea2params->datafile;
	int i = logFPath.size()-1;
	while(i>=0 && logFPath[i] != '.')
	{
		--i;
	}
	if(i<0)
	{
		PointGreyFlea2params->videoCap.release();
		return 0;
	}
	logFPath = logFPath.left(i)+QString("_PointGreyFlea2_timestamp.log");
	PointGreyFlea2params->logFile.setFileName(logFPath);
	if(PointGreyFlea2params->logFile.open(QFile::ReadOnly | QFile::Text))
	{
		PointGreyFlea2params->textstream.setDevice(&(PointGreyFlea2params->logFile));
		return 1;
	}
	else
	{
		PointGreyFlea2params->videoCap.release();
		return 0;
	}
}

long loadData(void * params, void ** data)
{
	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)params;
	POINTGREYFLEA2SIMULATORDATA * PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
	if(PointGreyFlea2data==NULL)
	{//case1: data point to a NULL
		*data=(void *)new POINTGREYFLEA2SIMULATORDATA;
		PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}

	if(!PointGreyFlea2params->videoCap.read(PointGreyFlea2data->image))
	{
		return -1;
	}
	if(PointGreyFlea2params->textstream.atEnd())
	{
		return -1;
	}
	else
	{
		long timestamp;
		PointGreyFlea2params->textstream>>timestamp;
		PointGreyFlea2data->timestamp=QTime(0,0,0,0).addMSecs(timestamp);
		return timestamp;
	}
}

bool closeSimulator(void * params)
{
	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)params;
	PointGreyFlea2params->textstream.reset();
	PointGreyFlea2params->logFile.close();
	PointGreyFlea2params->videoCap.release();
	return 1;
}

void dumpData(void ** data)
{
	POINTGREYFLEA2SIMULATORDATA * PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
	if(PointGreyFlea2data==NULL)
	{//case1: data point to a NULL
		
		PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2data;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

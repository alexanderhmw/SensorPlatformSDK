#include "Encoder.h"
#include<FuncLibrary\simulatorfunc.h>

bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new ENCODERSIMULATORPARAMS;
		Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("datafile",Encoderparams->datafile);
	return flag;
}

void releaseParamsSimulator(void ** params)	//release params
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSIMULATORPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		delete Encoderparams;
		*params=NULL;
	}
}

bool openSimulator(void * params)
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)params;
	Encoderparams->file.setFileName(Encoderparams->datafile);
	if(Encoderparams->file.open(QFile::ReadOnly | QFile::Text))
	{
		Encoderparams->textstream.setDevice(&(Encoderparams->file));
		return 1;
	}
	else
	{
		return 0;
	}
}

long loadData(void * params, void ** data)
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)params;
	ENCODERSIMULATORDATA * Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	if(Encoderdata==NULL)
	{//case1: data point to a NULL
		*data=(void *)new ENCODERSIMULATORDATA;
		Encoderdata=(ENCODERSIMULATORDATA *)(*data);
		Encoderdata->datagram.resize(2*sizeof(short));
	}
	else
	{//case2: Encoder point to a memory block
		
	}
	if(Encoderparams->textstream.atEnd())
	{
		return -1;
	}
	else
	{
		long timestamp;
		short angle;
		short encoder;
		Encoderparams->textstream>>timestamp;
		Encoderparams->textstream>>angle;
		Encoderparams->textstream>>encoder;
		Encoderdata->qtimestamp=QTime(0,0,0,0).addMSecs(timestamp);
		*((short *)(Encoderdata->datagram.data()))=angle;
		*((short *)(Encoderdata->datagram.data()+sizeof(short)))=encoder;
		return timestamp;
	}
}

bool closeSimulator(void * params)
{
	ENCODERSIMULATORPARAMS * Encoderparams=(ENCODERSIMULATORPARAMS *)params;
	Encoderparams->textstream.reset();
	Encoderparams->file.close();
	return 1;
}

void dumpData(void ** data)
{
	ENCODERSIMULATORDATA * Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	if(Encoderdata==NULL)
	{//case1: data point to a NULL
		
		Encoderdata=(ENCODERSIMULATORDATA *)(*data);
	}
	else
	{//case2: Encoder point to a memory block
		delete Encoderdata;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

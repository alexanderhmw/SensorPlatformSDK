#include "Encoder.h"
#include<FuncLibrary\storagefunc.h>

bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from xml
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)new ENCODERSTORAGEPARAMS;
		Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("storagepath",Encoderparams->storagepath);
	flag&=loader.getParam("extension",Encoderparams->extension);
	return flag;
}

void releaseParamsStorage(void ** params)	//release params
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	if(Encoderparams==NULL)
	{//case1: params point to a NULL
		
		Encoderparams=(ENCODERSTORAGEPARAMS *)(*params);
	}
	else
	{//case2: Encoder point to a memory block
		delete Encoderparams;
		*params=NULL;
	}
}

bool openStorage(void * params, void * nodeparams)	//open for store
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
	if(Encoderparams->file.isOpen())
	{
		Encoderparams->file.close();
	}
	QDateTime datetime=QDateTime::currentDateTime();
	QString timestamp=datetime.toString(QString("yyyyMMdd_hhmmss_zzz"));
	QString filename=QString("%1\\%2.%3").arg(Encoderparams->storagepath).arg(timestamp).arg(Encoderparams->extension);
	Encoderparams->file.setFileName(filename);
	if(Encoderparams->file.open(QFile::WriteOnly | QFile::Text))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool storeData(void * params, void * data)	//store data
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
	ENCODERSTORAGEDATA * Encoderdata=(ENCODERSTORAGEDATA *)data;
	if(Encoderparams->file.isOpen())
	{
		long timestamp=((Encoderdata->qtimestamp.hour()*60+Encoderdata->qtimestamp.minute())*60
		+Encoderdata->qtimestamp.second())*1000+Encoderdata->qtimestamp.msec();
		Encoderparams->file.write(QString("%1\t%2\n").arg(timestamp).arg(QString(Encoderdata->datagram)).toUtf8());
		return 1;
	}
	else
	{
		return 0;
	}
}

bool closeStorage(void * params)	//close storage
{
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
	Encoderparams->file.close();
	return 1;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

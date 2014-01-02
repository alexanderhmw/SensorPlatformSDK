#include "processor.h"

#pragma comment(lib, "NodeBase.lib")

Processor::Processor(QString libraryname, QString processorname, int inputbuffersize, int outputbuffersize)
	: NodeBase(libraryname,QString("Processor"),processorname)
{
	FptrLoadCheck(openProcessorFptr,openProcessor,_library);
	FptrLoadCheck(inputDataFptr,inputData,_library);
	FptrLoadCheck(processDataFptr,processData,_library);
	FptrLoadCheck(closeProcessorFptr,closeProcessor,_library);
	FptrLoadCheck(releaseInputDataFptr,releaseInputData,_library);
	FptrLoadCheck(releaseOutputDataFptr,releaseOutputData,_library);

	inputdatabuffer.resize(inputbuffersize);
	curinputdataid=0;
	outputdatabuffer.resize(outputbuffersize);
	curoutputdataid=0;
	openflag=0;
}

Processor::~Processor()
{
	if(openflag)
	{
		closeProcessorSlot();
	}
	int i,n;
	n=inputdatabuffer.size();
	for(i=0;i<n;i++)
	{
		releaseInputData(&(inputdatabuffer[i]));
	}
	inputdatabuffer.clear();
	n=outputdatabuffer.size();
	for(i=0;i<n;i++)
	{
		releaseOutputData(&(outputdatabuffer[i]));
	}
	outputdatabuffer.clear();
}

void Processor::openProcessorSlot()
{
	if(!openflag&&openProcessor(_params))
	{
		openflag=1;
		emit processorOpenSignal();
	}
	else
	{
		emit processorOpenErrorSignal();
	}
}

void Processor::inputDataSlot(void * data)
{
	if(openflag&&inputData(_params,data,&(inputdatabuffer[curinputdataid])))
	{
		curinputdataid=(curinputdataid+1)%inputdatabuffer.size();
		emit dataInputSignal();
	}
	else
	{
		emit dataInputErrorSignal();
	}
}

void Processor::processDataSlot()
{
	if(openflag)
	{
		QVector<void *> inputdataset;
		if(inputdatabuffer[curinputdataid]==NULL)
		{
			inputdataset=inputdatabuffer.mid(0,curinputdataid);
		}
		else
		{
			inputdataset=inputdatabuffer.mid(curinputdataid);
			inputdataset+=inputdatabuffer.mid(0,curinputdataid);
		}
		if(processData(_params,inputdataset,&(outputdatabuffer[curoutputdataid])))
		{
			emit dataProcessedSignal(outputdatabuffer[curoutputdataid]);
			curoutputdataid=(curoutputdataid+1)%outputdatabuffer.size();
		}
		else
		{
			emit dataProcessedErrorSignal();
		}
	}
}

void Processor::closeProcessorSlot()
{
	if(openflag&&closeProcessor(_params))
	{
		openflag=0;
		emit processorCloseSignal();
	}
	else
	{
		emit processorCloseErrorSignal();
	}
}

bool Processor::connectOpenProcessorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(openProcessorSlot()));
}

bool Processor::connectInputDataSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(inputDataSlot(void *)));
}

bool Processor::connectProcessDataSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(processDataSlot()));
}

bool Processor::connectCloseProcessorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(closeProcessorSlot()));
}

bool Processor::disconnectOpenProcessorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(openProcessorSlot()));
}

bool Processor::disconnectInputDataSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(inputDataSlot(void *)));
}

bool Processor::disconnectProcessDataSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(processDataSlot()));
}

bool Processor::disconnectCloseProcessorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(closeProcessorSlot()));
}

bool Processor::connectProcessorOpenSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(processorOpenSignal()),receiver,slot);
}

bool Processor::connectProcessorOpenErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(processorOpenErrorSignal()),receiver,slot);
}

bool Processor::connectDataInputSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataInputSignal()),receiver,slot);
}

bool Processor::connectDataInputErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataInputErrorSignal()),receiver,slot);
}

bool Processor::connectDataProcessedSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataProcessedSignal(void *)),receiver,slot);
}

bool Processor::connectDataProcessedErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataProcessedErrorSignal()),receiver,slot);
}

bool Processor::connectProcessorCloseSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(processorCloseSignal()),receiver,slot);
}

bool Processor::connectProcessorCloseErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(processorCloseErrorSignal()),receiver,slot);
}

bool Processor::disconnectProcessorOpenSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(processorOpenSignal()),receiver,slot);
}

bool Processor::disconnectProcessorOpenErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(processorOpenErrorSignal()),receiver,slot);
}

bool Processor::disconnectDataInputSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataInputSignal()),receiver,slot);
}

bool Processor::disconnectDataInputErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataInputErrorSignal()),receiver,slot);
}

bool Processor::disconnectDataProcessedSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataProcessedSignal(void *)),receiver,slot);
}

bool Processor::disconnectDataProcessedErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataProcessedErrorSignal()),receiver,slot);
}

bool Processor::disconnectProcessorCloseSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(processorCloseSignal()),receiver,slot);
}

bool Processor::disconnectProcessorCloseErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(processorCloseErrorSignal()),receiver,slot);
}

bool Processor::inputDataDriven(QObject * sender, const char * signal)
{
	bool flag=1;
	flag&=connectInputDataSignal(sender,signal);
	flag&=connectProcessDataSignal(this,SIGNAL(dataInputSignal()));
	return flag;
}
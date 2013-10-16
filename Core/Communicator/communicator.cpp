#include "communicator.h"

#pragma comment(lib,"NodeBase.lib")

Communicator::Communicator(QString libraryname, QString sensorname, int buffersize)
	: NodeBase(libraryname,QString("Sensor"),sensorname)
{
	FptrLoadCheck(openCommunicatorFptr,openCommunicator,_library);
	FptrLoadCheck(receiveDataFptr,receiveData,_library);
	FptrLoadCheck(sendDataFptr,sendData,_library);
	FptrLoadCheck(closeCommunicatorFptr,closeCommunicator,_library);
	FptrLoadCheck(flushReceiveDataFptr,flushReceiveData,_library);

	databuffer.resize(buffersize);
	curdataid=0;
	openflag=0;
}

Communicator::~Communicator()
{
	if(openflag)
	{
		closeCommunicatorSlot();
	}
	int i,n=databuffer.size();
	for(i=0;i<n;i++)
	{
		flushReceiveData(&(databuffer[i]));
	}
	databuffer.clear();
}

void Communicator::openCommunicatorSlot()
{
	QObject * trigger=NULL;
	QString triggersignal;
	if(!openflag&&openCommunicator(_params,&trigger,triggersignal))
	{
		openflag=1;
		if(trigger!=NULL)
		{
			if(connect(trigger,triggersignal.toUtf8().constData(),this,SLOT(receiveDataSlot())))
			{
				emit communicatorOpenSignal();
			}
			else
			{
				emit communicatorOpenErrorSignal();
			}
		}
		else
		{
			emit communicatorOpenSignal();
		}
	}
	else if(!openflag)
	{
		emit communicatorOpenErrorSignal();
	}
}

void Communicator::receiveDataSlot()
{
	if(openflag&&receiveData(_params,&(databuffer[curdataid])))
	{
		emit dataReceivedSignal(databuffer[curdataid]);
		curdataid=(curdataid+1)%databuffer.size();
	}
	else if(openflag)
	{
		emit dataReceivedErrorSignal();
	}	
}

void Communicator::sendDataSlot(void * data)
{
	if(openflag&&sendData(_params,data))
	{
		emit dataSentSignal(data);
	}
	else if(openflag)
	{
		emit dataSentErrorSignal();
	}	
}

void Communicator::closeCommunicatorSlot()
{
	QObject * trigger=NULL;
	QString triggersignal;
	if(openflag&&closeCommunicator(_params,&trigger,triggersignal))
	{
		openflag=0;
		if(trigger!=NULL)
		{
			if(disconnect(trigger,triggersignal.toUtf8().constData(),this,SLOT(captureDataSlot())))
			{
				emit communicatorCloseSignal();
			}
			else
			{
				emit communicatorCloseErrorSignal();
			}
		}
		else
		{
			emit communicatorOpenSignal();
		}
		emit communicatorCloseSignal();
	}
	else if(openflag)
	{
		emit communicatorCloseErrorSignal();
	}
}

bool Communicator::connectOpenCommunicatorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(openCommunicatorSlot()));
}

bool Communicator::connectReceiverDataSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(receiveDataSlot()));
}

bool Communicator::connectSendDataSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(sendDataSlot(void *)));
}

bool Communicator::connectCloseCommunicatorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(closeCommunicatorSlot()));
}

bool Communicator::disconnectOpenCommunicatorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(openCommunicatorSlot()));
}

bool Communicator::disconnectReceiverDataSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(receiveDataSlot()));
}

bool Communicator::disconnectSendDataSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(sendDataSlot(void *)));
}

bool Communicator::disconnectCloseCommunicatorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(closeCommunicatorSlot()));
}

bool Communicator::connectCommunicatorOpenSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(communicatorOpenSignal()),receiver,slot);
}

bool Communicator::connectCommunicatorOpenErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(communicatorOpenErrorSignal()),receiver,slot);
}

bool Communicator::connectDataReceivedSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataReceivedSignal(void *)),receiver,slot);
}

bool Communicator::connectDataReceivedErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataReceivedErrorSignal()),receiver,slot);
}

bool Communicator::connectDataSentSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataSentSignal(void *)),receiver,slot);
}

bool Communicator::connectDataSentErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataSentErrorSignal()),receiver,slot);
}

bool Communicator::connectCommunicatorCloseSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(communicatorCloseSignal()),receiver,slot);
}

bool Communicator::connectCommunicatorCloseErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(communicatorCloseErrorSignal()),receiver,slot);
}

bool Communicator::disconnectCommunicatorOpenSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(communicatorOpenSignal()),receiver,slot);
}

bool Communicator::disconnectCommunicatorOpenErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(communicatorOpenErrorSignal()),receiver,slot);
}

bool Communicator::disconnectDataReceivedSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataReceivedSignal(void *)),receiver,slot);
}

bool Communicator::disconnectDataReceivedErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataReceivedErrorSignal()),receiver,slot);
}

bool Communicator::disconnectDataSentSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataSentSignal(void *)),receiver,slot);
}

bool Communicator::disconnectDataSentErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataSentErrorSignal()),receiver,slot);
}

bool Communicator::disconnectCommunicatorCloseSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(communicatorCloseSignal()),receiver,slot);
}

bool Communicator::disconnectCommunicatorCloseErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(communicatorCloseErrorSignal()),receiver,slot);
}
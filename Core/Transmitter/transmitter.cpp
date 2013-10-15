#include "transmitter.h"

#pragma comment(lib,"NodeBase.lib")

Transmitter::Transmitter(NodeBase * nodebase)
	: NodeBase(nodebase->getLibraryName(),QString("Transmitter"),nodebase->getNodeName())
{
	_nodebase=nodebase;
	FptrLoadCheck(openTransmitterFptr,openTransmitter,_library);
	FptrLoadCheck(transmitDataFptr,transmitData,_library);
	FptrLoadCheck(closeTransmitterFptr,closeTransmitter,_library);
	openflag=0;
}

Transmitter::Transmitter(NodeBase * nodebase, QString libraryname)
	: NodeBase(libraryname,QString("Transmitter"),nodebase->getNodeName())
{
	_nodebase=nodebase;
	FptrLoadCheck(openTransmitterFptr,openTransmitter,_library);
	FptrLoadCheck(transmitDataFptr,transmitData,_library);
	FptrLoadCheck(closeTransmitterFptr,closeTransmitter,_library);
	openflag=0;
}

Transmitter::~Transmitter()
{
	if(openflag)
	{
		closeTransmitterSlot();
	}
}

void Transmitter::openTransmitterSlot()
{
	if(!openflag&&openTransmitter(_params,_nodebase->getParams()))
	{
		openflag=1;
		emit transmitterOpenSignal(_params);
	}
	else
	{
		emit transmitterOpenErrorSignal();
	}
}

void Transmitter::transmitDataSlot(void * data)
{
	if(openflag)
	{
		if(transmitData(_params,data))
		{
			emit dataTransmitSignal(data);
		}
		else
		{
			emit dataTransmitErrorSignal();
		}
	}
	else
	{
		emit dataTransmitErrorSignal();
	}
}

void Transmitter::closeTransmitterSlot()
{
	if(openflag&&closeTransmitter(_params))
	{
		openflag=0;
		emit transmitterCloseSignal();
	}
	else
	{
		emit transmitterCloseErrorSignal();
	}
}

bool Transmitter::connectOpenTransmitterSignal(QObject * sender, const char * signal)
{
    return connect(sender,signal,this,SLOT(openTransmitterSlot()));
}

bool Transmitter::connectTransmitDataSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(transmitDataSlot()));
}

bool Transmitter::connectCloseTransmitterSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(closeTransmitterSlot()));
}

bool Transmitter::disconnectOpenTransmitterSignal(QObject * sender, const char * signal)
{
    return disconnect(sender,signal,this,SLOT(openTransmitterSlot()));
}

bool Transmitter::disconnectTransmitDataSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(transmitDataSlot()));
}

bool Transmitter::disconnectCloseTransmitterSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(closeTransmitterSlot()));
}

bool Transmitter::connectTransmitterOpenSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(transmitterOpenSignal(void *)),receiver,slot);
}

bool Transmitter::connectTransmitterOpenErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(transmitterOpenErrorSignal()),receiver,slot);
}

bool Transmitter::connectDataTransmitSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(dataTransmitSignal(void *)),receiver,slot);
}

bool Transmitter::connectDataTransmitErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(dataTransmitErrorSignal()),receiver,slot);
}

bool Transmitter::connectTransmitterCloseSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(transmitterCloseSignal()),receiver,slot);
}

bool Transmitter::connectTransmitterCloseErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(transmitterCloseErrorSignal()),receiver,slot);
}

bool Transmitter::disconnectTransmitterOpenSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(transmitterOpenSignal(void *)),receiver,slot);
}

bool Transmitter::disconnectTransmitterOpenErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(transmitterOpenErrorSignal()),receiver,slot);
}

bool Transmitter::disconnectDataTransmitSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(dataTransmitSignal(void *)),receiver,slot);
}

bool Transmitter::disconnectDataTransmitErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(dataTransmitErrorSignal()),receiver,slot);
}

bool Transmitter::disconnectTransmitterCloseSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(transmitterCloseSignal()),receiver,slot);
}

bool Transmitter::disconnectTransmitterCloseErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(transmitterCloseErrorSignal()),receiver,slot);
}

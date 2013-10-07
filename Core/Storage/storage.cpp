#include "storage.h"

Storage::Storage(Sensor * sensor)
	: NodeBase(sensor->getLibraryName(),QString("Storage"),sensor->getNodeName())
{
	_sensor=sensor;
	FptrLoadCheck(openStorageFptr,openStorage,_library);
	FptrLoadCheck(storeDataFptr,storeData,_library);
	FptrLoadCheck(closeStorageFptr,closeStorage,_library);
	openflag=0;
}

Storage::~Storage()
{
	if(openflag)
	{
		closeStorageSlot();
	}
}

void Storage::openStorageSlot()
{
	if(!openflag&&openStorage(_params,_sensor->getParams()))
	{
		openflag=1;
		emit storageOpenSignal();
	}
	else
	{
		emit storageOpenErrorSignal();
	}
}

void Storage::storeDataSlot(void * data)
{
	if(openflag)
	{
		int n=storeData(_params,data);
		if(n>0)
		{
			emit dataStoreSignal(n);
		}
		else
		{
			emit dataStoreErrorSignal();
		}
	}
	else
	{
		emit dataStoreErrorSignal();
	}
}

void Storage::closeStorageSlot()
{
	if(openflag&&closeStorage(_params))
	{
		openflag=0;
		emit storageCloseSignal();
	}
	else
	{
		emit storageCloseErrorSignal();
	}
}

bool Storage::connectOpenStorageSignal(QObject * sender, const char * signal)
{
    return connect(sender,signal,this,SLOT(openStorageSlot()));
}

bool Storage::connectStoreDataSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(storeDataSlot()));
}

bool Storage::connectCloseStorageSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(closeStorageSlot()));
}

bool Storage::disconnectOpenStorageSignal(QObject * sender, const char * signal)
{
    return disconnect(sender,signal,this,SLOT(openStorageSlot()));
}

bool Storage::disconnectStoreDataSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(storeDataSlot()));
}

bool Storage::disconnectCloseStorageSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(closeStorageSlot()));
}

bool Storage::connectStorageOpenSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(storageOpenSignal()),receiver,slot);
}

bool Storage::connectStorageOpenErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(storageOpenErrorSignal()),receiver,slot);
}

bool Storage::connectDataStoreSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(dataStoreSignal(void*)),receiver,slot);
}

bool Storage::connectDataStoreErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(dataStoreErrorSignal()),receiver,slot);
}

bool Storage::connectStorageCloseSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(storageCloseSignal()),receiver,slot);
}

bool Storage::connectStorageCloseErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(storageCloseErrorSignal()),receiver,slot);
}

bool Storage::disconnectStorageOpenSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(storageOpenSignal()),receiver,slot);
}

bool Storage::disconnectStorageOpenErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(storageOpenErrorSignal()),receiver,slot);
}

bool Storage::disconnectDataStoreSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(dataStoreSignal()),receiver,slot);
}

bool Storage::disconnectDataStoreErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(dataStoreErrorSignal()),receiver,slot);
}

bool Storage::disconnectStorageCloseSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(storageCloseSignal()),receiver,slot);
}

bool Storage::disconnectStorageCloseErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(storageCloseErrorSignal()),receiver,slot);
}

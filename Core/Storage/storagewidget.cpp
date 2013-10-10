#include "storagewidget.h"

StorageWidget::StorageWidget(Storage * storage, QWidget *parent)
	: NodeWidgetBase(storage, parent)
{
	FptrLoadCheck(storageOpenFptr,storageOpen,_library);
	FptrLoadCheck(storageOpenErrorFptr,storageOpenError,_library);
	FptrLoadCheck(dataStoreFptr,dataStore,_library);
	FptrLoadCheck(dataStoreErrorFptr,dataStoreError,_library);
	FptrLoadCheck(storageCloseFptr,storageClose,_library);
	FptrLoadCheck(storageCloseErrorFptr,storageCloseError,_library);

	_storage=storage;
}

StorageWidget::~StorageWidget()
{

}

void StorageWidget::storageOpenSlot(void * params)
{
	storageOpen(_widgets,params);
}

void StorageWidget::storageOpenErrorSlot()
{
	storageOpenError(_widgets);
}

void StorageWidget::dataStoreSlot(void * data)
{
	dataStore(_widgets,data);
}

void StorageWidget::dataStoreErrorSlot()
{
	dataStoreError(_widgets);
}

void StorageWidget::storageCloseSlot()
{
	storageClose(_widgets);
}

void StorageWidget::storageCloseErrorSlot()
{
	storageCloseError(_widgets);
}

bool StorageWidget::connectSignals()
{
	bool flag=1;
	flag&=_storage->connectStorageOpenSlot(this,SLOT(storageOpenSlot(void *)));
	flag&=_storage->connectStorageOpenErrorSlot(this,SLOT(storageOpenErrorSlot()));
	flag&=_storage->connectDataStoreSlot(this,SLOT(dataStoreSlot(void *)));
	flag&=_storage->connectDataStoreErrorSlot(this,SLOT(dataStoreErrorSlot()));
	flag&=_storage->connectStorageCloseSlot(this,SLOT(storageCloseSlot()));
	flag&=_storage->connectStorageCloseErrorSlot(this,SLOT(storageCloseErrorSlot()));
	return flag;
}

bool StorageWidget::disconnectSignals()
{
	bool flag=1;
	flag&=_storage->disconnectStorageOpenSlot(this,SLOT(storageOpenSlot(void *)));
	flag&=_storage->disconnectStorageOpenErrorSlot(this,SLOT(storageOpenErrorSlot()));
	flag&=_storage->disconnectDataStoreSlot(this,SLOT(dataStoreSlot(void *)));
	flag&=_storage->disconnectDataStoreErrorSlot(this,SLOT(dataStoreErrorSlot()));
	flag&=_storage->disconnectStorageCloseSlot(this,SLOT(storageCloseSlot()));
	flag&=_storage->disconnectStorageCloseErrorSlot(this,SLOT(storageCloseErrorSlot()));
	return flag;
}
#ifndef STORAGEWIDGET_H
#define STORAGEWIDGET_H

#include<NodeBase\nodewidgetbase.h>
#include<Storage\storage.h>

class StorageWidget : public NodeWidgetBase
{
	Q_OBJECT
public:
	StorageWidget(Storage * storage, QWidget *parent=NULL);
	~StorageWidget();
protected:
	Storage * _storage;
protected:
	typedef void (*storageOpenFptr)(void * widgets, void * params);
	storageOpenFptr storageOpen;
	typedef void (*storageOpenErrorFptr)(void * widgets);
	storageOpenErrorFptr storageOpenError;
	typedef void (*dataStoreFptr)(void * widgets, void * data);
	dataStoreFptr dataStore;
	typedef void (*dataStoreErrorFptr)(void * widgets);
	dataStoreErrorFptr dataStoreError;
	typedef void (*storageCloseFptr)(void * widgets);
	storageCloseFptr storageClose;
	typedef void (*storageCloseErrorFptr)(void * widgets);
	storageCloseErrorFptr storageCloseError;
protected slots:
	void storageOpenSlot(void * params);
	void storageOpenErrorSlot();
	void dataStoreSlot(void * data);
	void dataStoreErrorSlot();
	void storageCloseSlot();
	void storageCloseErrorSlot();
public:
	bool connectSignals();
	bool disconnectSignals();
};

#endif // StorageWidget_H

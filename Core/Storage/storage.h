#ifndef STORAGE_H
#define STORAGE_H

#include<NodeBase\nodebase.h>

class Storage : public NodeBase
{
	Q_OBJECT
public:
	Storage(NodeBase * nodebase);
	Storage(NodeBase * nodebase, QString libraryname);
	~Storage();
protected:
	NodeBase * _nodebase;
protected:
	bool openflag;
protected:
	typedef bool (*openStorageFptr)(void * params, void * nodeparams);
	openStorageFptr openStorage;
	typedef bool (*storeDataFptr)(void * params, void * data);
	storeDataFptr storeData;
	typedef bool (*closeStorageFptr)(void * params);
	closeStorageFptr closeStorage;
public slots:
	void openStorageSlot();
	void storeDataSlot(void * data);
	void closeStorageSlot();
signals:
	void storageOpenSignal(void * params);
	void storageOpenErrorSignal();
	void dataStoreSignal(void * data);
	void dataStoreErrorSignal();
	void storageCloseSignal();
	void storageCloseErrorSignal();
public:
	bool connectOpenStorageSignal(QObject * sender, const char * signal);
	bool connectStoreDataSignal(QObject * sender, const char * signal);
	bool connectCloseStorageSignal(QObject * sender, const char * signal);

	bool disconnectOpenStorageSignal(QObject * sender, const char * signal);
	bool disconnectStoreDataSignal(QObject * sender, const char * signal);
	bool disconnectCloseStorageSignal(QObject * sender, const char * signal);

	bool connectStorageOpenSlot(QObject * receiver, const char * slot);
	bool connectStorageOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataStoreSlot(QObject * receiver, const char * slot);
	bool connectDataStoreErrorSlot(QObject * receiver, const char * slot);
	bool connectStorageCloseSlot(QObject * receiver, const char * slot);
	bool connectStorageCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectStorageOpenSlot(QObject * receiver, const char * slot);
	bool disconnectStorageOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataStoreSlot(QObject * receiver, const char * slot);
	bool disconnectDataStoreErrorSlot(QObject * receiver, const char * slot);
	bool disconnectStorageCloseSlot(QObject * receiver, const char * slot);
	bool disconnectStorageCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // SENSORSTORAGE_H

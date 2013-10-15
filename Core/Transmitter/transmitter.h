#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include<NodeBase\nodebase.h>

class Transmitter : public NodeBase
{
	Q_OBJECT
public:
	Transmitter(NodeBase * nodebase);
	Transmitter(NodeBase * nodebase, QString libraryname);
	~Transmitter();
protected:
	NodeBase * _nodebase;
protected:
	bool openflag;
protected:
	typedef bool (*openTransmitterFptr)(void * params, void * nodeparams);
	openTransmitterFptr openTransmitter;
	typedef bool (*transmitDataFptr)(void * params, void * data);
	transmitDataFptr transmitData;
	typedef bool (*closeTransmitterFptr)(void * params);
	closeTransmitterFptr closeTransmitter;
public slots:
	void openTransmitterSlot();
	void transmitDataSlot(void * data);
	void closeTransmitterSlot();
signals:
	void transmitterOpenSignal(void * params);
	void transmitterOpenErrorSignal();
	void dataTransmitSignal(void * data);
	void dataTransmitErrorSignal();
	void transmitterCloseSignal();
	void transmitterCloseErrorSignal();
public:
	bool connectOpenTransmitterSignal(QObject * sender, const char * signal);
	bool connectTransmitDataSignal(QObject * sender, const char * signal);
	bool connectCloseTransmitterSignal(QObject * sender, const char * signal);

	bool disconnectOpenTransmitterSignal(QObject * sender, const char * signal);
	bool disconnectTransmitDataSignal(QObject * sender, const char * signal);
	bool disconnectCloseTransmitterSignal(QObject * sender, const char * signal);

	bool connectTransmitterOpenSlot(QObject * receiver, const char * slot);
	bool connectTransmitterOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataTransmitSlot(QObject * receiver, const char * slot);
	bool connectDataTransmitErrorSlot(QObject * receiver, const char * slot);
	bool connectTransmitterCloseSlot(QObject * receiver, const char * slot);
	bool connectTransmitterCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectTransmitterOpenSlot(QObject * receiver, const char * slot);
	bool disconnectTransmitterOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataTransmitSlot(QObject * receiver, const char * slot);
	bool disconnectDataTransmitErrorSlot(QObject * receiver, const char * slot);
	bool disconnectTransmitterCloseSlot(QObject * receiver, const char * slot);
	bool disconnectTransmitterCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // TRANSMITTER_H

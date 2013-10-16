#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include<NodeBase\nodebase.h>
#include<qvector.h>

class Communicator : public NodeBase
{
	Q_OBJECT
public:
	Communicator(QString libraryname, QString communicatorname, int buffersize=10);
	~Communicator();
protected:
	QVector<void *> databuffer;
	int curdataid;
	bool openflag;
protected:
	typedef bool (*openCommunicatorFptr)(void * params, QObject ** trigger, QString & triggersignal);
	openCommunicatorFptr openCommunicator;
	typedef bool (*receiveDataFptr)(void * params, void ** receivedata);
	receiveDataFptr receiveData;
	typedef bool (*sendDataFptr)(void * params, void * senddata);
	sendDataFptr sendData;
	typedef bool (*closeCommunicatorFptr)(void * params, QObject ** trigger, QString & triggersignal);
	closeCommunicatorFptr closeCommunicator;
	typedef void (*flushReceiveDataFptr)(void ** receivedata);
	flushReceiveDataFptr flushReceiveData;
public slots:
	void openCommunicatorSlot();
	void receiveDataSlot();
	void sendDataSlot(void *);
	void closeCommunicatorSlot();
signals:
	void communicatorOpenSignal();
	void communicatorOpenErrorSignal();
	void dataReceivedSignal(void *);
	void dataReceivedErrorSignal();
	void dataSentSignal(void *);
	void dataSentErrorSignal();
	void communicatorCloseSignal();
	void communicatorCloseErrorSignal();
public:
	bool connectOpenCommunicatorSignal(QObject * sender, const char * signal);
	bool connectReceiverDataSignal(QObject * sender, const char * signal);
	bool connectSendDataSignal(QObject * sender, const char * signal);
	bool connectCloseCommunicatorSignal(QObject * sender, const char * signal);

	bool disconnectOpenCommunicatorSignal(QObject * sender, const char * signal);
	bool disconnectReceiverDataSignal(QObject * sender, const char * signal);
	bool disconnectSendDataSignal(QObject * sender, const char * signal);
	bool disconnectCloseCommunicatorSignal(QObject * sender, const char * signal);

	bool connectCommunicatorOpenSlot(QObject * receiver, const char * slot);
	bool connectCommunicatorOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataReceivedSlot(QObject * receiver, const char * slot);
	bool connectDataReceivedErrorSlot(QObject * receiver, const char * slot);
	bool connectDataSentSlot(QObject * receiver, const char * slot);
	bool connectDataSentErrorSlot(QObject * receiver, const char * slot);
	bool connectCommunicatorCloseSlot(QObject * receiver, const char * slot);
	bool connectCommunicatorCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectCommunicatorOpenSlot(QObject * receiver, const char * slot);
	bool disconnectCommunicatorOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataReceivedSlot(QObject * receiver, const char * slot);
	bool disconnectDataReceivedErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataSentSlot(QObject * receiver, const char * slot);
	bool disconnectDataSentErrorSlot(QObject * receiver, const char * slot);
	bool disconnectCommunicatorCloseSlot(QObject * receiver, const char * slot);
	bool disconnectCommunicatorCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // COMMUNICATOR_H

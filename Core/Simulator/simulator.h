#ifndef SIMULATOR_H
#define SIMULATOR_H

#include<NodeBase\nodebase.h>
#include<qvector.h>
#include<qtimer.h>
#include<qdatetime.h>

class Simulator : public NodeBase
{
	Q_OBJECT
public:
	Simulator(QString libraryname, QString simulatorname, int buffersize=10);
	~Simulator();
protected:
	QVector<void *> databuffer;
	int curdataid;
	bool openflag;
	QTimer timer;
	long curtimestamp;
	long nexttimestamp;
	int emitdataid;
	bool startflag;
protected:
	typedef bool (*openSimulatorFptr)(void * params);
	openSimulatorFptr openSimulator;
	typedef long (*loadDataFptr)(void * params, void ** data);
	loadDataFptr loadData;
	typedef bool (*closeSimulatorFptr)(void * params);
	closeSimulatorFptr closeSimulator;
	typedef void (*dumpDataFptr)(void ** data);
	dumpDataFptr dumpData;
private slots:
	void emitDataSlot();
public slots:
	void openSimulatorSlot();
	void initialSimulatorSlot(long starttime);
	void startSimulatorSlot();
	void stopSimulatorSlot();
	void closeSimulatorSlot();
signals:
	void simulatorOpenSignal();
	void simulatorOpenErrorSignal();
	void simulatorInitialSignal(long starttime);
	void simulatorInitialErrorSignal();
	void simulatorStartSignal();
	void simulatorStartErrorSignal();
	void dataEmitSignal(void * data);
	void dataEmitErrorSignal();
	void simulatorStopSignal();
	void simulatorStopErrorSignal();
	void simulatorCloseSignal();
	void simulatorCloseErrorSignal();
public:
	bool connectOpenSimulatorSignal(QObject * sender, const char * signal);
	bool connectInitialSimulatorSignal(QObject * sender, const char * signal);
	bool connectStartSimulationSignal(QObject * sender, const char * signal);
	bool connectStopSimulatorSignal(QObject * sender, const char * signal);
	bool connectCloseSimulatorSignal(QObject * sender, const char * signal);

	bool disconnectOpenSimulatorSignal(QObject * sender, const char * signal);
	bool disconnectInitialSimulatorSignal(QObject * sender, const char * signal);
	bool disconnectStartSimulationSignal(QObject * sender, const char * signal);
	bool disconnectStopSimulatorSignal(QObject * sender, const char * signal);
	bool disconnectCloseSimulatorSignal(QObject * sender, const char * signal);

	bool connectSimulatorOpenSlot(QObject * receiver, const char * slot);
	bool connectSimulatorOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectSimulatorInitialSlot(QObject * receiver, const char * slot);
	bool connectSimulatorInitialErrorSlot(QObject * receiver, const char * slot);
	bool connectSimulatorStartSlot(QObject * receiver, const char * slot);
	bool connectSimulatorStartErrorSlot(QObject * receiver, const char * slot);
	bool connectDataEmitSlot(QObject * receiver, const char * slot);
	bool connectDataEmitErrorSlot(QObject * receiver, const char * slot);
	bool connectSimulatorStopSlot(QObject * receiver, const char * slot);
	bool connectSimulatorStopErrorSlot(QObject * receiver, const char * slot);
	bool connectSimulatorCloseSlot(QObject * receiver, const char * slot);
	bool connectSimulatorCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectSimulatorOpenSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorInitialSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorInitialErrorSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorStartSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorStartErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataEmitSlot(QObject * receiver, const char * slot);
	bool disconnectDataEmitErrorSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorStopSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorStopErrorSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorCloseSlot(QObject * receiver, const char * slot);
	bool disconnectSimulatorCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // SIMULATOR_H

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<NodeBase\nodebase.h>
#include<qvector.h>

class Processor : public NodeBase
{
	Q_OBJECT
public:
	Processor(QString libraryname, QString processorname, int inputbuffersize=100, int outputbuffersize=10);
	~Processor();
protected:
	QVector<void *> inputdatabuffer;
	QVector<void *> outputdatabuffer;
	int curinputdataid;
	int curoutputdataid;
	bool openflag;
protected:
	typedef bool (*openProcessorFptr)(void * params);
	openProcessorFptr openProcessor;
	typedef bool (*inputDataFptr)(void * params, void * data, void ** inputdata);
	inputDataFptr inputData;
	typedef bool (*processDataFptr)(void * params, QVector<void *> inputdataset,void **outputdata);
	processDataFptr processData;
	typedef bool (*closeProcessorFptr)(void * params);
	closeProcessorFptr closeProcessor;
	typedef void (*releaseInputDataFptr)(void ** inputdata);
	releaseInputDataFptr releaseInputData;
	typedef void (*releaseOutputDataFptr)(void ** outputdata);
	releaseOutputDataFptr releaseOutputData;
public slots:
	void openProcessorSlot();
	void inputDataSlot(void * data);
	void processDataSlot();
	void closeProcessorSlot();
signals:
	void processorOpenSignal();
	void processorOpenErrorSignal();
	void dataInputSignal();
	void dataInputErrorSignal();
	void dataProcessedSignal(void * data);
	void dataProcessedErrorSignal();
	void processorCloseSignal();
	void processorCloseErrorSignal();
public:
	bool connectOpenProcessorSignal(QObject * sender, const char * signal);
	bool connectInputDataSignal(QObject * sender, const char * signal);
	bool connectProcessDataSignal(QObject * sender, const char * signal);
	bool connectCloseProcessorSignal(QObject * sender, const char * signal);

	bool disconnectOpenProcessorSignal(QObject * sender, const char * signal);
	bool disconnectInputDataSignal(QObject * sender, const char * signal);
	bool disconnectProcessDataSignal(QObject * sender, const char * signal);
	bool disconnectCloseProcessorSignal(QObject * sender, const char * signal);

	bool connectProcessorOpenSlot(QObject * receiver, const char * slot);
	bool connectProcessorOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataInputSlot(QObject * receiver, const char * slot);
	bool connectDataInputErrorSlot(QObject * receiver, const char * slot);
	bool connectDataProcessedSlot(QObject * receiver, const char * slot);
	bool connectDataProcessedErrorSlot(QObject * receiver, const char * slot);
	bool connectProcessorCloseSlot(QObject * receiver, const char * slot);
	bool connectProcessorCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectProcessorOpenSlot(QObject * receiver, const char * slot);
	bool disconnectProcessorOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataInputSlot(QObject * receiver, const char * slot);
	bool disconnectDataInputErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataProcessedSlot(QObject * receiver, const char * slot);
	bool disconnectDataProcessedErrorSlot(QObject * receiver, const char * slot);
	bool disconnectProcessorCloseSlot(QObject * receiver, const char * slot);
	bool disconnectProcessorCloseErrorSlot(QObject * receiver, const char * slot);
public:
	bool inputDataDriven(QObject * sender, const char * signal);
};

#endif // PROCESSOR_H

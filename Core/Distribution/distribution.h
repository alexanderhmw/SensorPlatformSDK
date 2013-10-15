#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include<NodeBase\nodebase.h>
#include<qvector.h>
#include<qstring.h>

class OutputLinker : public QObject
{
	Q_OBJECT
public:
	OutputLinker();
	~OutputLinker();
signals:
	void outputLinkerSignal(void * data);
public:
	void sendOutputLinkerSignal(void * data);
};

class Distribution : public NodeBase
{
	Q_OBJECT
public:
	Distribution(NodeBase * nodebase);
	Distribution(NodeBase * nodebase, QString libraryname);
	~Distribution();
private:
	QVector<QString> supportnodetypeclass;
	QVector<QVector<QString>> supportnodename;
	QVector<QVector<OutputLinker *>> outputlinkers;
	bool openflag;
protected:
	typedef void (*getSupportOutputNodesFptr)(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename);
	getSupportOutputNodesFptr getSupportOutputNodes;
	typedef bool (*openDistributionFptr)(void * params);
	openDistributionFptr openDistribution;
	typedef bool (*parseDataFptr)(void * params, void * data, QVector<QVector<int>> & distids);
	parseDataFptr parseData;
	typedef bool (*closeDistributionFptr)(void * params);
	closeDistributionFptr closeDistribution;
public slots:
	void generateOutputLinkersSlot();
	void openDistributionSlot();
	void parseDataSlot(void * data);
	void closeDistributionSlot();
signals:
	void outputLinkersGeneratedSignal();
	void outputLinkersGeneratedErrorSignal();
	void distributionOpenSignal();
	void distributionOpenErrorSignal();
	void dataParsedSignal();
	void dataParsedErrorSignal();
	void distributionCloseSignal();
	void distributionCloseErrorSignal();
public:
	bool connectGenerateOutputLinkerSignal(QObject * sender, const char * signal);
	bool connectOpenDistributionSignal(QObject * sender, const char * signal);
	bool connectParseDataSignal(NodeBase * sender, const char * signal);
	bool connectCloseDistributionSignal(QObject * sender, const char * signal);

	bool disconnectGenerateOutputLinkerSignal(QObject * sender, const char * signal);
	bool disconnectOpenDistributionSignal(QObject * sender, const char * signal);
	bool disconnectParseDataSignal(NodeBase * sender, const char * signal);
	bool disconnectCloseDistributionSignal(QObject * sender, const char * signal);

	bool connectOutputLinkersGeneratedSlot(QObject * receiver, const char * slot);
	bool connectOutputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot);
	bool connectDistributionOpenSlot(QObject * receiver, const char * slot);
	bool connectDistributionOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataParsedSlot(QObject * receiver, const char * slot);
	bool connectDataParsedErrorSlot(QObject * receiver, const char * slot);
	bool connectDistributionCloseSlot(QObject * receiver, const char * slot);
	bool connectDistributionCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectOutputLinkersGeneratedSlot(QObject * receiver, const char * slot);
	bool disconnectOutputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDistributionOpenSlot(QObject * receiver, const char * slot);
	bool disconnectDistributionOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataParsedSlot(QObject * receiver, const char * slot);
	bool disconnectDataParsedErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDistributionCloseSlot(QObject * receiver, const char * slot);
	bool disconnectDistributionCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // DISTRIBUTION_H

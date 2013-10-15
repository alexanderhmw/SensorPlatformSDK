#ifndef FUSION_H
#define FUSION_H

#include<NodeBase\nodebase.h>
#include<qvector.h>
#include<qstring.h>

class InputLinker : public QObject
{
	Q_OBJECT
public:
	InputLinker(int typeclassid,int nameid);
	~InputLinker();
protected:
	int _typeclassid;
	int _nameid;
public slots:
	void inputLinkerSlot(void * data);
signals:
	void inputLinkerSignal(int typeclassid, int nameid, void * data);
};

class Fusion : public NodeBase
{
	Q_OBJECT
public:
	Fusion(QString libraryname, QString fusionname, int inputbuffersize=100, int outputbuffersize=10);
	~Fusion();
protected:
	QVector<QString> supportnodetypeclass;
	QVector<QVector<QString>> supportnodename;
	QVector<QVector<InputLinker *>> inputlinkers;
	int _inputbuffersize;
	QVector<QVector<QVector<void *>>> inputdatabuffer;
	QVector<void *> outputdatabuffer;
	QVector<QVector<int>> curinputdataid;
	int curoutputdataid;
	bool openflag;
protected:
	typedef void (*getSupportInputNodesFptr)(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename);
	getSupportInputNodesFptr getSupportInputNodes;
	typedef bool (*openFusionFptr)(void * params);
	openFusionFptr openFusion;
	typedef bool (*inputDataFptr)(void * params, int typeclassid, int nameid, void * data, void ** inputdata);
	inputDataFptr inputData;
	typedef bool (*fuseDataFptr)(void * params, QVector<QVector<QVector<void *>>> inputdataset, void ** outputdata);
	fuseDataFptr fuseData;
	typedef bool (*closeFusionFptr)(void * params);
	closeFusionFptr closeFusion;
	typedef void (*releaseInputDataFptr)(int typeclassid, int nameid, void ** outputdata);
	releaseInputDataFptr releaseInputData;
	typedef void (*releaseOutputDataFptr)(void ** inputdata);
	releaseOutputDataFptr releaseOutputData;
public slots:
	void generateInputLinkersSlot();
	void openFusionSlot();
	void inputDataSlot(int typeclassid, int nameid, void * data);
	void fuseDataSlot();
	void closeFusionSlot();
signals:
	void inputLinkersGeneratedSignal();
	void inputLinkersGeneratedErrorSignal();
	void fusionOpenSignal();
	void fusionOpenErrorSignal();
	void dataInputSignal(int typeclassid, int nameid);
	void dataInputErrorSignal();
	void dataFusedSignal(void * data);
	void dataFusedErrorSignal();
	void fusionCloseSignal();
	void fusionCloseErrorSignal();
public:
	bool connectGenerateInputLinkersSignal(QObject * sender, const char * signal);
	bool connectOpenFusionSignal(QObject * sender, const char * signal);
	bool connectInputDataSignal(NodeBase * sender, const char * signal);
	bool connectFuseDataSignal(QObject * sender, const char * signal);
	bool connectCloseFusionSignal(QObject * sender, const char * signal);

	bool disconnectGenerateInputLinkersSignal(QObject * sender, const char * signal);
	bool disconnectOpenFusionSignal(QObject * sender, const char * signal);
	bool disconnectInputDataSignal(NodeBase * sender, const char * signal);
	bool disconnectFuseDataSignal(QObject * sender, const char * signal);
	bool disconnectCloseFusionSignal(QObject * sender, const char * signal);

	bool connectInputLinkersGeneratedSlot(QObject * receiver, const char * slot);
	bool connectInputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot);
	bool connectFusionOpenSlot(QObject * receiver, const char * slot);
	bool connectFusionOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataInputSlot(QObject * receiver, const char * slot);
	bool connectDataInputErrorSlot(QObject * receiver, const char * slot);
	bool connectDataFusedSlot(QObject * receiver, const char * slot);
	bool connectDataFusedErrorSlot(QObject * receiver, const char * slot);
	bool connectFusionCloseSlot(QObject * receiver, const char * slot);
	bool connectFusionCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectInputLinkersGeneratedSlot(QObject * receiver, const char * slot);
	bool disconnectInputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot);
	bool disconnectFusionOpenSlot(QObject * receiver, const char * slot);
	bool disconnectFusionOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataInputSlot(QObject * receiver, const char * slot);
	bool disconnectDataInputErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataFusedSlot(QObject * receiver, const char * slot);
	bool disconnectDataFusedErrorSlot(QObject * receiver, const char * slot);
	bool disconnectFusionCloseSlot(QObject * receiver, const char * slot);
	bool disconnectFusionCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // FUSION_H

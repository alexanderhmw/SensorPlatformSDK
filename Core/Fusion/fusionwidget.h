#ifndef FUSIONWIDGET_H
#define FUSIONWIDGET_H

#include<NodeBase\nodewidgetbase.h>
#include<Fusion\fusion.h>

class FusionWidget : public NodeWidgetBase
{
	Q_OBJECT
public:
	FusionWidget(Fusion * fusion, QWidget *parent=NULL);
	~FusionWidget();
protected:
	Fusion * _fusion;
protected:
	typedef void (*inputLinkersGeneratedFptr)(void * widgets, QVector<QString> supporttypeclass, QVector<QVector<QString>> supportname);
	inputLinkersGeneratedFptr inputLinkersGenerated;
	typedef void (*inputLinkersGeneratedErrorFptr)(void * widgets);
	inputLinkersGeneratedErrorFptr inputLinkersGeneratedError;
	typedef void (*fusionOpenFptr)(void * widgets);
	fusionOpenFptr fusionOpen;
	typedef void (*fusionOpenErrorFptr)(void * widgets);
	fusionOpenErrorFptr fusionOpenError;
	typedef void (*dataInputFptr)(void * widgets, int typeclassid, int nameid, void * data);
	dataInputFptr dataInput;
	typedef void (*dataInputErrorFptr)(void * widgets);
	dataInputErrorFptr dataInputError;
	typedef void (*dataFusedFptr)(void * widgets, void * data);
	dataFusedFptr dataFused;
	typedef void (*dataFusedErrorFptr)(void * widgets);
	dataFusedErrorFptr dataFusedError;
	typedef void (*fusionCloseFptr)(void * widgets);
	fusionCloseFptr fusionClose;
	typedef void (*fusionCloseErrorFptr)(void * widgets);
	fusionCloseErrorFptr fusionCloseError;
protected slots:
	void inputLinkersGeneratedSlot(QVector<QString> supporttypeclass, QVector<QVector<QString>> supportname);
	void inputLinkersGeneratedErrorSlot();
	void fusionOpenSlot();
	void fusionOpenErrorSlot();
	void dataInputSlot(int typeclassid, int nameid, void * data);
	void dataInputErrorSlot();
	void dataFusedSlot(void * data);
	void dataFusedErrorSlot();
	void fusionCloseSlot();
	void fusionCloseErrorSlot();
public:
	bool connectSignals();
	bool disconnectSignals();
};

#endif // SENSORWIDGET_H

#include "fusionwidget.h"

FusionWidget::FusionWidget(Fusion * fusion, QWidget *parent)
	: NodeWidgetBase(fusion,parent)
{
	FptrLoadCheck(inputLinkersGeneratedFptr,inputLinkersGenerated,_library);
	FptrLoadCheck(inputLinkersGeneratedErrorFptr,inputLinkersGeneratedError,_library);
	FptrLoadCheck(fusionOpenFptr,fusionOpen,_library);
	FptrLoadCheck(fusionOpenErrorFptr,fusionOpenError,_library);
	FptrLoadCheck(dataInputFptr,dataInput,_library);
	FptrLoadCheck(dataInputErrorFptr,dataInputError,_library);
	FptrLoadCheck(dataFusedFptr,dataFused,_library);
	FptrLoadCheck(dataFusedErrorFptr,dataFusedError,_library);
	FptrLoadCheck(fusionCloseFptr,fusionClose,_library);
	FptrLoadCheck(fusionCloseErrorFptr,fusionCloseError,_library);
	_fusion=fusion;
}

FusionWidget::~FusionWidget()
{

}

void FusionWidget::inputLinkersGeneratedSlot(QVector<QString> supporttypeclass, QVector<QVector<QString>> supportname)
{
	inputLinkersGenerated(_widgets,supporttypeclass,supportname);
}

void FusionWidget::inputLinkersGeneratedErrorSlot()
{
	inputLinkersGeneratedError(_widgets);
}

void FusionWidget::fusionOpenSlot()
{
	fusionOpen(_widgets);
}

void FusionWidget::fusionOpenErrorSlot()
{
	fusionOpenError(_widgets);
}

void FusionWidget::dataInputSlot(int typeclassid,int nameid, void * data)
{
	dataInput(_widgets,typeclassid,nameid,data);
}

void FusionWidget::dataInputErrorSlot()
{
	dataInputError(_widgets);
}

void FusionWidget::dataFusedSlot(void * data)
{
	dataFused(_widgets,data);
}

void FusionWidget::dataFusedErrorSlot()
{
	dataFusedError(_widgets);
}

void FusionWidget::fusionCloseSlot()
{
	fusionClose(_widgets);
}

void FusionWidget::fusionCloseErrorSlot()
{
	fusionCloseError(_widgets);
}

bool FusionWidget::connectSignals()
{
	bool flag=1;
	flag&=_fusion->connectInputLinkersGeneratedSlot(this,SLOT(inputLinkersGeneratedSlot(QVector<QString>,QVector<QVector<QString>>)));
	flag&=_fusion->connectInputLinkersGeneratedErrorSlot(this,SLOT(inputLinkersGeneratedErrorSlot()));
	flag&=_fusion->connectFusionOpenSlot(this,SLOT(fusionOpenSlot(void *)));
	flag&=_fusion->connectFusionOpenErrorSlot(this,SLOT(fusionOpenErrorSlot()));
	flag&=_fusion->connectDataInputSlot(this,SLOT(dataInputSlot(int,int,void *)));
	flag&=_fusion->connectDataInputErrorSlot(this,SLOT(dataInputErrorSlot()));
	flag&=_fusion->connectDataFusedSlot(this,SLOT(dataFusedSlot(void *)));
	flag&=_fusion->connectDataFusedErrorSlot(this,SLOT(dataFusedErrorSlot()));
	flag&=_fusion->connectFusionCloseSlot(this,SLOT(fusionCloseSlot()));
	flag&=_fusion->connectFusionCloseErrorSlot(this,SLOT(fusionCloseErrorSlot()));
	return flag;
}

bool FusionWidget::disconnectSignals()
{
	bool flag=1;
	flag&=_fusion->disconnectInputLinkersGeneratedSlot(this,SLOT(inputLinkersGeneratedSlot(QVector<QString>,QVector<QVector<QString>>)));
	flag&=_fusion->disconnectInputLinkersGeneratedErrorSlot(this,SLOT(inputLinkersGeneratedErrorSlot()));
	flag&=_fusion->disconnectFusionOpenSlot(this,SLOT(fusionOpenSlot(void *)));
	flag&=_fusion->disconnectFusionOpenErrorSlot(this,SLOT(fusionOpenErrorSlot()));
	flag&=_fusion->disconnectDataInputSlot(this,SLOT(dataInputSlot(int,int,void *)));
	flag&=_fusion->disconnectDataInputErrorSlot(this,SLOT(dataInputErrorSlot()));
	flag&=_fusion->disconnectDataFusedSlot(this,SLOT(dataFusedSlot(void *)));
	flag&=_fusion->disconnectDataFusedErrorSlot(this,SLOT(dataFusedErrorSlot()));
	flag&=_fusion->disconnectFusionCloseSlot(this,SLOT(fusionCloseSlot()));
	flag&=_fusion->disconnectFusionCloseErrorSlot(this,SLOT(fusionCloseErrorSlot()));
	return flag;
}
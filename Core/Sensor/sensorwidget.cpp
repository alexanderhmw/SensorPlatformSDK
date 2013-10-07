#include "sensorwidget.h"

SensorWidget::SensorWidget(Sensor * sensor, QWidget *parent)
	: NodeWidgetBase(sensor, parent)
{
	FptrLoadCheck(sensorOpenFptr,sensorOpen,_library);
	FptrLoadCheck(sensorOpenErrorFptr,sensorOpenError,_library);
	FptrLoadCheck(dataCaptureFptr,dataCapture,_library);
	FptrLoadCheck(dataCaptureErrorFptr,dataCaptureError,_library);
	FptrLoadCheck(sensorCloseFptr,sensorClose,_library);
	FptrLoadCheck(sensorCloseErrorFptr,sensorCloseError,_library);

	_sensor=sensor;
}

SensorWidget::~SensorWidget()
{

}

void SensorWidget::sensorOpenSlot()
{
	sensorOpen(_widgets);
}

void SensorWidget::sensorOpenErrorSlot()
{
	sensorOpenError(_widgets);
}

void SensorWidget::dataCaptureSlot(void * data)
{
	dataCapture(_widgets,data);
}

void SensorWidget::dataCaptureErrorSlot()
{
	dataCaptureError(_widgets);
}

void SensorWidget::sensorCloseSlot()
{
	sensorClose(_widgets);
}

void SensorWidget::sensorCloseErrorSlot()
{
	sensorCloseError(_widgets);
}

bool SensorWidget::connectSignals()
{
	bool flag=1;
	flag&=_sensor->connectSensorOpenSlot(this,SLOT(sensorOpenSlot()));
	flag&=_sensor->connectSensorOpenErrorSlot(this,SLOT(sensorOpenErrorSlot()));
	flag&=_sensor->connectDataCaptureSlot(this,SLOT(dataCaptureSlot(void *)));
	flag&=_sensor->connectDataCaptureErrorSlot(this,SLOT(dataCaptureErrorSlot()));
	flag&=_sensor->connectSensorCloseSlot(this,SLOT(sensorCloseSlot()));
	flag&=_sensor->connectSensorCloseErrorSlot(this,SLOT(sensorCloseErrorSlot()));
	return flag;
}

bool SensorWidget::disconnectSignals()
{
	bool flag=1;
	flag&=_sensor->disconnectSensorOpenSlot(this,SLOT(sensorOpenSlot()));
	flag&=_sensor->disconnectSensorOpenErrorSlot(this,SLOT(sensorOpenErrorSlot()));
	flag&=_sensor->disconnectDataCaptureSlot(this,SLOT(dataCaptureSlot(void *)));
	flag&=_sensor->disconnectDataCaptureErrorSlot(this,SLOT(dataCaptureErrorSlot()));
	flag&=_sensor->disconnectSensorCloseSlot(this,SLOT(sensorCloseSlot()));
	flag&=_sensor->disconnectSensorCloseErrorSlot(this,SLOT(sensorCloseErrorSlot()));
	return flag;
}
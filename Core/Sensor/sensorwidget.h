#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include<NodeBase\nodewidgetbase.h>
#include<Sensor\sensor.h>

class SensorWidget : public NodeWidgetBase
{
	Q_OBJECT
public:
	SensorWidget(Sensor * sensor, QWidget *parent=NULL);
	~SensorWidget();
protected:
	Sensor * _sensor;
protected:
	typedef void (*sensorOpenFptr)(void * widgets);
	sensorOpenFptr sensorOpen;
	typedef void (*sensorOpenErrorFptr)(void * widgets);
	sensorOpenErrorFptr sensorOpenError;
	typedef void (*dataCaptureFptr)(void * widgets, void * data);
	dataCaptureFptr dataCapture;
	typedef void (*dataCaptureErrorFptr)(void * widgets);
	dataCaptureErrorFptr dataCaptureError;
	typedef void (*sensorCloseFptr)(void * widgets);
	sensorCloseFptr sensorClose;
	typedef void (*sensorCloseErrorFptr)(void * widgets);
	sensorCloseErrorFptr sensorCloseError;
protected slots:
	void sensorOpenSlot();
	void sensorOpenErrorSlot();
	void dataCaptureSlot(void * data);
	void dataCaptureErrorSlot();
	void sensorCloseSlot();
	void sensorCloseErrorSlot();
public:
	bool connectSignals();
	bool disconnectSignals();
};

#endif // SENSORWIDGET_H

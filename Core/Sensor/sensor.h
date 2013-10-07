#ifndef SENSOR_H
#define SENSOR_H

#include<NodeBase\nodebase.h>
#include<qvector.h>

class Sensor : public NodeBase
{
	Q_OBJECT
public:
	Sensor(QString libraryname, QString sensorname, int buffersize=10);
	~Sensor();
protected:
	QVector<void *> databuffer;
	int curdataid;
	bool openflag;
protected:
	typedef bool (*openSensorFptr)(void * params);
	openSensorFptr openSensor;
	typedef bool (*captureDataFptr)(void * params, void ** data);
	captureDataFptr captureData;
	typedef bool (*closeSensorFptr)(void * params);
	closeSensorFptr closeSensor;
	typedef void (*releaseDataFptr)(void ** data);
	releaseDataFptr releaseData;
public slots:
	void openSensorSlot();
	void captureDataSlot();
	void closeSensorSlot();
signals:
	void sensorOpenSignal();
	void sensorOpenErrorSignal();
	void dataCaptureSignal(void * data);
	void dataCaptureErrorSignal();
	void sensorCloseSignal();
	void sensorCloseErrorSignal();
public:
	bool connectOpenSensorSignal(QObject * sender, const char * signal);
	bool connectCaptureDataSignal(QObject * sender, const char * signal);
	bool connectCloseSensorSignal(QObject * sender, const char * signal);

	bool disconnectOpenSensorSignal(QObject * sender, const char * signal);
	bool disconnectCaptureDataSignal(QObject * sender, const char * signal);
	bool disconnectCloseSensorSignal(QObject * sender, const char * signal);

	bool connectSensorOpenSlot(QObject * receiver, const char * slot);
	bool connectSensorOpenErrorSlot(QObject * receiver, const char * slot);
	bool connectDataCaptureSlot(QObject * receiver, const char * slot);
	bool connectDataCaptureErrorSlot(QObject * receiver, const char * slot);
	bool connectSensorCloseSlot(QObject * receiver, const char * slot);
	bool connectSensorCloseErrorSlot(QObject * receiver, const char * slot);

	bool disconnectSensorOpenSlot(QObject * receiver, const char * slot);
	bool disconnectSensorOpenErrorSlot(QObject * receiver, const char * slot);
	bool disconnectDataCaptureSlot(QObject * receiver, const char * slot);
	bool disconnectDataCaptureErrorSlot(QObject * receiver, const char * slot);
	bool disconnectSensorCloseSlot(QObject * receiver, const char * slot);
	bool disconnectSensorCloseErrorSlot(QObject * receiver, const char * slot);
};

#endif // SENSOR_H

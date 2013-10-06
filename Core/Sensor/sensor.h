#ifndef SENSOR_H
#define SENSOR_H

#include<qobject.h>
#include<qvector.h>
#include<qstring.h>
#include<qlibrary.h>
#include<qmessagebox.h>

struct SensorDescriptor
{
	QString libraryname;
	QString sensorname;
};

class Sensor : public QObject
{
	Q_OBJECT
public:
	Sensor(SensorDescriptor descriptor, int buffersize=10);
	~Sensor();
protected:
	QLibrary _library;
	QString _sensorclass;
	QString _sensorname;
	QString _configfilename;
protected:
	void * _params;
	QVector<void *> _databuffer;
	int _curdataid;
protected:
	typedef bool (*loadParamsFptr)(QString & configfilename, QString & sensorclass, QString & sensorname, void ** params);
	loadParamsFptr loadParams;
	typedef bool (*openSensorFptr)(void * params);
	openSensorFptr openSensor;
	typedef bool (*captureDataFptr)(void * params, void ** data);
	captureDataFptr captureData;
	typedef bool (*closeSensorFptr)(void * params);
	closeSensorFptr closeSensor;
	typedef void (*releaseParamsFptr)(void ** params);
	releaseParamsFptr releaseParams;
	typedef void (*releaseDataFptr)(void ** data);
	releaseDataFptr releaseData;
public slots:
	void loadParamsSlot(QString configfilename);
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
    bool connectLoadParamsSignal(QObject * sender, const char * signal);
	bool connectOpenSensorSignal(QObject * sender, const char * signal);
	bool connectCaptureDataSignal(QObject * sender, const char * signal);
	bool connectCloseSensorSignal(QObject * sender, const char * signal);

    bool disconnectLoadParamsSignal(QObject *sender, const char *signal);
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

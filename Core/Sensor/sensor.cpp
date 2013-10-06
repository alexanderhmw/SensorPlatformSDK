#include "sensor.h"

#define FptrLoadCheck(fptr,fptrtype,library) \
fptr=(fptrtype) library.resolve(#fptr);	\
if(fptr==NULL)	\
{QMessageBox::information(NULL,QString("Sensor Error"),QString("No function %1 in Share Library %2").arg(QString(#fptr)).arg(library.fileName()));exit(0);}

Sensor::Sensor(SensorDescriptor descriptor, int buffersize)
{
	_library.setFileName(descriptor.libraryname);
	if(_library.load())
	{
		FptrLoadCheck(loadParams, loadParamsFptr,_library);
		FptrLoadCheck(openSensor,openSensorFptr,_library);
		FptrLoadCheck(captureData,captureDataFptr,_library);
		FptrLoadCheck(closeSensor,closeSensorFptr,_library);
		FptrLoadCheck(releaseParams,releaseParamsFptr,_library);
		FptrLoadCheck(releaseData,releaseDataFptr,_library);
	}
	else
	{
		QMessageBox::information(NULL,QString("Sensor Error"),QString("Share Library %1 missing").arg(_library.fileName()));
		exit(0);
	}

	_params=NULL;
	_databuffer.resize(buffersize);
	_curdataid=0;
}

Sensor::~Sensor()
{
	releaseParams(&_params);
	int i,n=_databuffer.size();
	for(i=0;i<n;i++)
	{
		releaseData(&(_databuffer[i]));
	}
	_databuffer.clear();
}

void Sensor::loadParamsSlot(QString configfilename)
{
	_configfilename=configfilename;
	if(!loadParams(_configfilename,_sensorclass,_sensorname,&_params))
	{
		QMessageBox::information(NULL,QString("Sensor Error"),QString("Parameters Initialization Error:\n%1_%2_%3").arg(_configfilename).arg(_sensorclass).arg(_sensorname));
		exit(0);
	}
}

void Sensor::openSensorSlot()
{
	if(openSensor(_params))
	{
		emit sensorOpenSignal();
	}
	else
	{
		emit sensorOpenErrorSignal();
	}
}

void Sensor::captureDataSlot()
{
	if(captureData(_params,&(_databuffer[_curdataid])))
	{
		emit dataCaptureSignal(_databuffer[_curdataid]);
		_curdataid=(_curdataid+1)%_databuffer.size();
	}
	else
	{
		emit dataCaptureErrorSignal();
	}
}

void Sensor::closeSensorSlot()
{
	if(closeSensor(_params))
	{
		emit sensorCloseSignal();
	}
	else
	{
		emit sensorCloseErrorSignal();
	}
}

bool Sensor::connectLoadParamsSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(loadParamsSlot(QString)));
}

bool Sensor::connectOpenSensorSignal(QObject * sender, const char * signal)
{
    return connect(sender,signal,this,SLOT(openSensorSlot()));
}

bool Sensor::connectCaptureDataSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(captureDataSlot()));
}

bool Sensor::connectCloseSensorSignal(QObject *sender, const char *signal)
{
    return connect(sender,signal,this,SLOT(closeSensorSlot()));
}

bool Sensor::disconnectLoadParamsSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(loadParamsSlot(QString)));
}

bool Sensor::disconnectOpenSensorSignal(QObject * sender, const char * signal)
{
    return disconnect(sender,signal,this,SLOT(openSensorSlot()));
}

bool Sensor::disconnectCaptureDataSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(captureDataSlot()));
}

bool Sensor::disconnectCloseSensorSignal(QObject *sender, const char *signal)
{
    return disconnect(sender,signal,this,SLOT(closeSensorSlot()));
}

bool Sensor::connectSensorOpenSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(sensorOpenSignal()),receiver,slot);
}

bool Sensor::connectSensorOpenErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(sensorOpenErrorSignal()),receiver,slot);
}

bool Sensor::connectDataCaptureSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(dataCaptureSignal(void*)),receiver,slot);
}

bool Sensor::connectDataCaptureErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(dataCaptureErrorSignal()),receiver,slot);
}

bool Sensor::connectSensorCloseSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(sensorCloseSignal()),receiver,slot);
}

bool Sensor::connectSensorCloseErrorSlot(QObject *receiver, const char *slot)
{
    return connect(this,SIGNAL(sensorCloseErrorSignal()),receiver,slot);
}

bool Sensor::disconnectSensorOpenSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(sensorOpenSignal()),receiver,slot);
}

bool Sensor::disconnectSensorOpenErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(sensorOpenErrorSignal()),receiver,slot);
}

bool Sensor::disconnectDataCaptureSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(dataCaptureSignal()),receiver,slot);
}

bool Sensor::disconnectDataCaptureErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(dataCaptureErrorSignal()),receiver,slot);
}

bool Sensor::disconnectSensorCloseSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(sensorCloseSignal()),receiver,slot);
}

bool Sensor::disconnectSensorCloseErrorSlot(QObject *receiver, const char *slot)
{
    return disconnect(this,SIGNAL(sensorCloseErrorSignal()),receiver,slot);
}

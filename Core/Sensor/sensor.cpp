#include "sensor.h"

#pragma comment(lib,"NodeBase.lib")

Sensor::Sensor(QString libraryname, QString sensorname, int buffersize)
	: NodeBase(libraryname,QString("Sensor"),sensorname)
{
	FptrLoadCheck(openSensorFptr,openSensor,_library);
	FptrLoadCheck(captureDataFptr,captureData,_library);
	FptrLoadCheck(closeSensorFptr,closeSensor,_library);
	FptrLoadCheck(releaseDataFptr,releaseData,_library);

	databuffer.resize(buffersize);
	curdataid=0;
	openflag=0;
}

Sensor::~Sensor()
{
	if(openflag)
	{
		closeSensorSlot();
	}
	int i,n=databuffer.size();
	for(i=0;i<n;i++)
	{
		releaseData(&(databuffer[i]));
	}
	databuffer.clear();
}

void Sensor::openSensorSlot()
{
	if(!openflag&&openSensor(_params))
	{
		openflag=1;
		emit sensorOpenSignal();
	}
	else
	{
		emit sensorOpenErrorSignal();
	}
}

void Sensor::captureDataSlot()
{
	if(openflag&&captureData(_params,&(databuffer[curdataid])))
	{
		emit dataCaptureSignal(databuffer[curdataid]);
		curdataid=(curdataid+1)%databuffer.size();
	}
	else
	{
		emit dataCaptureErrorSignal();
	}
}

void Sensor::closeSensorSlot()
{
	if(openflag&&closeSensor(_params))
	{
		openflag=0;
		emit sensorCloseSignal();
	}
	else
	{
		emit sensorCloseErrorSignal();
	}
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

#ifndef URG_H
#define URG_H

#include "urg_global.h"

#include"Resources\urg\urg_sensor.h"
#include"Resources\urg\urg_utils.h"
#include<qdatetime.h>
#include<qstring.h>
#include<omp.h>
#include<xmlparamsloader.h>

struct URG_EXPORT URGPARAMS
{
	urg_t urg;
	urg_connection_type_t connection_type;
	QString device_or_address;
	long baudreate_or_port;
	urg_measurement_type_t measurement_type;
	int skip_scan;
	int first_step;
	int last_step;
	int skip_step;
};

struct URG_EXPORT URGDATA
{
	long timestamp;
	QTime qtimestamp;
	int datasize;
	short * data;
};

extern "C" URG_EXPORT bool loadParams(QString & configfilename, QString & sensorclass, QString & sensorname, void ** params);
extern "C" URG_EXPORT bool openSensor(void * params);
extern "C" URG_EXPORT bool captureData(void * params, void ** data);
extern "C" URG_EXPORT bool closeSensor(void * params);
extern "C" URG_EXPORT void releaseParams(void ** params);
extern "C" URG_EXPORT void releaseData(void ** data);

#endif // URG_H

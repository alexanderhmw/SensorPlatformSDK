#ifndef SENSOR_FUNC_H
#define SENSOR_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParams(QString & configfilename, QString & sensorclass, QString & sensorname, void ** params);
extern "C" Q_DECL_EXPORT bool openSensor(void * params);
extern "C" Q_DECL_EXPORT bool captureData(void * params, void ** data);
extern "C" Q_DECL_EXPORT bool closeSensor(void * params);
extern "C" Q_DECL_EXPORT void releaseParams(void ** params);
extern "C" Q_DECL_EXPORT void releaseData(void ** data);

#endif
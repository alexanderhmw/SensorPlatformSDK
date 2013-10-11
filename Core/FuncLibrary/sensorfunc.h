#ifndef SENSOR_FUNC_H
#define SENSOR_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from XML
extern "C" Q_DECL_EXPORT void releaseParamsSensor(void ** params);	//release params

extern "C" Q_DECL_EXPORT bool openSensor(void * params);	//open the sensor using params
extern "C" Q_DECL_EXPORT bool captureData(void * params, void ** data);	//capture data using params and store in data
extern "C" Q_DECL_EXPORT bool closeSensor(void * params);	//close the sensor using params
extern "C" Q_DECL_EXPORT void releaseData(void ** data);	//release data

#endif
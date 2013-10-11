#ifndef STORAGE_FUNC_H
#define STORAGE_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from xml
extern "C" Q_DECL_EXPORT void releaseParamsStorage(void ** params);	//release params

extern "C" Q_DECL_EXPORT bool openStorage(void * params, void * sensorparams);	//open for store
extern "C" Q_DECL_EXPORT bool storeData(void * params, void * data);	//store data
extern "C" Q_DECL_EXPORT bool closeStorage(void * params);	//close storage


#endif
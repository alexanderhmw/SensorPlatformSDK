#ifndef STORAGE_FUNC_H
#define STORAGE_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsStorage(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);
extern "C" Q_DECL_EXPORT void releaseParamsStorage(void ** params);

extern "C" Q_DECL_EXPORT bool openStorage(void * params, void * sensorparams);
extern "C" Q_DECL_EXPORT bool storeData(void * params, void * data);
extern "C" Q_DECL_EXPORT bool closeStorage(void * params);


#endif
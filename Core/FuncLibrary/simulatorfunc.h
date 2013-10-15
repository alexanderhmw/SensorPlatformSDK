#ifndef SIMULATOR_FUNC_H
#define SIMULATOR_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from XML
extern "C" Q_DECL_EXPORT void releaseParamsSimulator(void ** params);	//release params

extern "C" Q_DECL_EXPORT bool openSimulator(void * params);
extern "C" Q_DECL_EXPORT long loadData(void * params, void ** data);
extern "C" Q_DECL_EXPORT bool closeSimulator(void * params);
extern "C" Q_DECL_EXPORT void dumpData(void ** data);

#endif
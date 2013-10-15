#ifndef STORAGE_FUNC_H
#define STORAGE_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsTransmitter(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from xml
extern "C" Q_DECL_EXPORT void releaseParamsTransmitter(void ** params);	//release params

extern "C" Q_DECL_EXPORT bool openTransmitter(void * params, void * nodeparams);	//open for transmit
extern "C" Q_DECL_EXPORT bool transmitData(void * params, void * data);	//transmit data
extern "C" Q_DECL_EXPORT bool closeTransmitter(void * params);	//close transmitter


#endif
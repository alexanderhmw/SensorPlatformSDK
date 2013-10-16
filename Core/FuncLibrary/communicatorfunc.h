#ifndef COMMUNICATOR_FUNC_H
#define COMMUNICATOR_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qobject.h>

extern "C" Q_DECL_EXPORT bool loadParamsCommunicator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from XML
extern "C" Q_DECL_EXPORT void releaseParamsCommunicator(void ** params);	//release params

extern "C" Q_DECL_EXPORT bool openCommunicator(void * params, QObject ** trigger, QString & triggersignal);	//open the sensor using params
extern "C" Q_DECL_EXPORT bool receiveData(void * params, void ** receivedata);	//capture data using params and store in data
extern "C" Q_DECL_EXPORT bool sendData(void * params, void * senddata);
extern "C" Q_DECL_EXPORT bool closeCommunicator(void * params, QObject ** trigger, QString & triggersignal);	//close the sensor using params
extern "C" Q_DECL_EXPORT void flushReceiveData(void ** receivedata);	//release data

#endif
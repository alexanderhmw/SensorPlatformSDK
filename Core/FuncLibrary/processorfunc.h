#ifndef PROCESSOR_FUNC_H
#define PROCESSOR_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsProcessor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from XML
extern "C" Q_DECL_EXPORT void releaseParamsProcessor(void ** params);	//release params

extern "C" Q_DECL_EXPORT bool openProcessor(void * params);	//open the processor using params
extern "C" Q_DECL_EXPORT bool inputData(void * params, void * data, void ** inputdata);	//input data and store in inputdata
extern "C" Q_DECL_EXPORT bool processData(void * params, QVector<void *> inputdataset, void **outputdata);	//process inputdataset and store in outputdata
extern "C" Q_DECL_EXPORT bool closeProcessor(void * params);	//close the processor using params
extern "C" Q_DECL_EXPORT void releaseInputData(void ** inputdata);	//release inputdata
extern "C" Q_DECL_EXPORT void releaseOutputData(void ** outputdata);	//release outputdata

#endif
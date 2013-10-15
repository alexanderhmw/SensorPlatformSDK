#ifndef DISTRIBUTION_FUNC_H
#define DISTRIBUTION_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsDistribution(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from XML
extern "C" Q_DECL_EXPORT void releaseParamsDistribution(void ** params);	//release params

extern "C" Q_DECL_EXPORT void getSupportOutputNodes(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename);
extern "C" Q_DECL_EXPORT bool openDistribution(void * params);
extern "C" Q_DECL_EXPORT bool parseDataFptr(void * params, void * data, QVector<QVector<int>> & distids);
extern "C" Q_DECL_EXPORT bool closeDistribution(void * params);

#endif
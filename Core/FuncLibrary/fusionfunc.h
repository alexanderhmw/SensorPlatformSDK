#ifndef FUSION_FUNC_H
#define FUSION_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>

extern "C" Q_DECL_EXPORT bool loadParamsFusion(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params);	//load params from XML
extern "C" Q_DECL_EXPORT void releaseParamsFusion(void ** params);	//release params

extern "C" Q_DECL_EXPORT void getSupportInputNodes(void * params, QVector<QString> & nodetypeclass, QVector<QVector<QString>> & nodename);
extern "C" Q_DECL_EXPORT bool openFusion (void * params);
extern "C" Q_DECL_EXPORT bool inputData (void * params, int typeclassid, int nameid, void * data, void ** inputdata);
extern "C" Q_DECL_EXPORT bool fuseData (void * params, QVector<QVector<QVector<void *>>> inputdataset, void ** outputdata);
extern "C" Q_DECL_EXPORT bool closeFusion (void * params);
extern "C" Q_DECL_EXPORT void releaseInputData (int typeclassid, int nameid, void ** outputdata);
extern "C" Q_DECL_EXPORT void releaseOutputData (void ** inputdata);

#endif
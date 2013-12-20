#ifndef FUSION_WIDGET_FUNC_H
#define FUSION_WIDGET_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qwidget.h>

extern "C" Q_DECL_EXPORT void inputLinkersGenerated(void * widgets, QVector<QString> supporttypeclass, QVector<QVector<QString>> supportname);
extern "C" Q_DECL_EXPORT void inputLinkersGeneratedError(void * widgets);
extern "C" Q_DECL_EXPORT void fusionOpen(void * widgets);
extern "C" Q_DECL_EXPORT void fusionOpenError(void * widgets);
extern "C" Q_DECL_EXPORT void dataInput(void * widgets, int typeclassid, int nameid, void * data);
extern "C" Q_DECL_EXPORT void dataInputError(void * widgets);
extern "C" Q_DECL_EXPORT void dataFused(void * widgets, void * data);
extern "C" Q_DECL_EXPORT void dataFusedError(void * widgets);
extern "C" Q_DECL_EXPORT void fusionClose(void * widgets);
extern "C" Q_DECL_EXPORT void fusionCloseError(void * widgets);

#endif
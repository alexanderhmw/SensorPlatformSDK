#ifndef STORAGE_WIDGET_FUNC_H
#define STORAGE_WIDGET_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qwidget.h>

extern "C" Q_DECL_EXPORT void setWidgetsStorage(QWidget * widget, void ** widgets);
extern "C" Q_DECL_EXPORT void releaseWidgetsStorage(QWidget * widget, void ** widgets);

extern "C" Q_DECL_EXPORT void storageOpen(void * widgets, void * params);
extern "C" Q_DECL_EXPORT void storageOpenError(void * widgets);
extern "C" Q_DECL_EXPORT void dataStore(void * widgets,void * data);
extern "C" Q_DECL_EXPORT void dataStoreError(void * widgets);
extern "C" Q_DECL_EXPORT void storageClose(void * widgets);
extern "C" Q_DECL_EXPORT void storageCloseError(void * widgets);

#endif
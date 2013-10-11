#ifndef STORAGE_WIDGET_FUNC_H
#define STORAGE_WIDGET_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qwidget.h>

extern "C" Q_DECL_EXPORT void setWidgetsStorage(QWidget * widget, void ** widgets);	//initial the widget
extern "C" Q_DECL_EXPORT void releaseWidgetsStorage(QWidget * widget, void ** widgets);	//release the widget

extern "C" Q_DECL_EXPORT void storageOpen(void * widgets, void * params);	//handle openstorage signal
extern "C" Q_DECL_EXPORT void storageOpenError(void * widgets);	//handle openstorageerror signal
extern "C" Q_DECL_EXPORT void dataStore(void * widgets,void * data);	//handle storedata signal
extern "C" Q_DECL_EXPORT void dataStoreError(void * widgets);	//handle storedataerror signal
extern "C" Q_DECL_EXPORT void storageClose(void * widgets);	//handle closestoragesignal
extern "C" Q_DECL_EXPORT void storageCloseError(void * widgets);	//handle closestorageerror signal

#endif
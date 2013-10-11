#ifndef SENSOR_WIDGET_FUNC_H
#define SENSOR_WIDGET_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qwidget.h>

extern "C" Q_DECL_EXPORT void setWidgetsSensor(QWidget * widget, void ** widgets);	//initial the widget
extern "C" Q_DECL_EXPORT void releaseWidgetsSensor(QWidget * widget, void ** widgets);	//release the widget

extern "C" Q_DECL_EXPORT void sensorOpen(void * widgets);	//handle opensensor signal
extern "C" Q_DECL_EXPORT void sensorOpenError(void * widgets);	//handle opensensorerror signal
extern "C" Q_DECL_EXPORT void dataCapture(void * widgets,void * data);	//handle capturedata signal
extern "C" Q_DECL_EXPORT void dataCaptureError(void * widgets);	//handle capturedataerror signal
extern "C" Q_DECL_EXPORT void sensorClose(void * widgets);	//handle closesensor signal
extern "C" Q_DECL_EXPORT void sensorCloseError(void * widgets);	//handle closesensorerror signal

#endif
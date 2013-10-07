#ifndef SENSOR_WIDGET_FUNC_H
#define SENSOR_WIDGET_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qwidget.h>

extern "C" Q_DECL_EXPORT void setWidgetsSensor(QWidget * widget, void ** widgets);
extern "C" Q_DECL_EXPORT void releaseWidgetsSensor(QWidget * widget, void ** widgets);

extern "C" Q_DECL_EXPORT void sensorOpen(void * widgets);
extern "C" Q_DECL_EXPORT void sensorOpenError(void * widgets);
extern "C" Q_DECL_EXPORT void dataCapture(void * widgets,void * data);
extern "C" Q_DECL_EXPORT void dataCaptureError(void * widgets);
extern "C" Q_DECL_EXPORT void sensorClose(void * widgets);
extern "C" Q_DECL_EXPORT void sensorCloseError(void * widgets);

#endif
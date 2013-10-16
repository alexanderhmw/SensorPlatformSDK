#ifndef COMMUNICATOR_WIDGET_FUNC_H
#define COMMUNICATOR_WIDGET_FUNC_H

#include <QtCore/qglobal.h>
#include<qstring.h>
#include<qwidget.h>

extern "C" Q_DECL_EXPORT void setWidgetsCommunicator(QWidget * widget, void ** widgets);	//initial the widget
extern "C" Q_DECL_EXPORT void releaseWidgetsCommunicator(QWidget * widget, void ** widgets);	//release the widget

extern "C" Q_DECL_EXPORT void communicatorOpen(void * widgets);	//handle opencommunicator signal
extern "C" Q_DECL_EXPORT void communicatorOpenError(void * widgets);	//handle opencommunicatorerror signal
extern "C" Q_DECL_EXPORT void dataReceived(void * widgets,void * receivedata);	//handle capturedata signal
extern "C" Q_DECL_EXPORT void dataReceivedError(void * widgets);	//handle capturedataerror signal
extern "C" Q_DECL_EXPORT void dataSent(void * widgets,void * senddata);	//handle capturedata signal
extern "C" Q_DECL_EXPORT void dataSentError(void * widgets);	//handle capturedataerror signal
extern "C" Q_DECL_EXPORT void communicatorClose(void * widgets);	//handle closecommunicator signal
extern "C" Q_DECL_EXPORT void communicatorCloseError(void * widgets);	//handle closecommunicatorerror signal

#endif
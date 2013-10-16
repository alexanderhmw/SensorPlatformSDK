#include "Encoder.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Encoderwidgets=(ENCODERSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Encoderwidgets=(ENCODERSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)widgets;
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)widgets;
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)widgets;
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)widgets;
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)widgets;
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	ENCODERSENSORWIDGETS * Encoderwidgets=(ENCODERSENSORWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

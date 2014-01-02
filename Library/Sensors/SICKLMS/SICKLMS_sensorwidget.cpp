#include "SICKLMS.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)(*widgets);
	if(SICKLMSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)(*widgets);
	if(SICKLMSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)widgets;
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)widgets;
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)widgets;
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)widgets;
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)widgets;
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	SICKLMSSENSORWIDGETS * SICKLMSwidgets=(SICKLMSSENSORWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

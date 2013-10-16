#include "XWGPS.h"
#include<FuncLibrary\sensorwidgetfunc.h>

void setWidgetsSensor(QWidget * widget, void ** widgets)	//initial the widget
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		XWGPSwidgets=(XWGPSSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

void releaseWidgetsSensor(QWidget * widget, void ** widgets)	//release the widget
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		XWGPSwidgets=(XWGPSSENSORWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

void sensorOpen(void * widgets)	//handle opensensor signal
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)widgets;
}

void sensorOpenError(void * widgets)	//handle opensensorerror signal
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)widgets;
}

void dataCapture(void * widgets,void * data)	//handle capturedata signal
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)widgets;
}

void dataCaptureError(void * widgets)	//handle capturedataerror signal
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)widgets;
}

void sensorClose(void * widgets)	//handle closesensor signal
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)widgets;
}

void sensorCloseError(void * widgets)	//handle closesensorerror signal
{
	XWGPSSENSORWIDGETS * XWGPSwidgets=(XWGPSSENSORWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

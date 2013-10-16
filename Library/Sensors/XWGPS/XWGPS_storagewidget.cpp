#include "XWGPS.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

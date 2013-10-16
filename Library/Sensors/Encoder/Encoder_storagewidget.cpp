#include "Encoder.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Encoderwidgets=(ENCODERSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Encoderwidgets=(ENCODERSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

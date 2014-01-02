#include "SICKLMS.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)(*widgets);
	if(SICKLMSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)(*widgets);
	if(SICKLMSwidgets==NULL)
	{//case1: widgets point to a NULL
		
		SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: SICKLMS point to a memory block
		
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)widgets;
	SICKLMSSTORAGEPARAMS * SICKLMSparams=(SICKLMSSTORAGEPARAMS *)params;
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)widgets;
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)widgets;
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)widgets;
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)widgets;
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	SICKLMSSTORAGEWIDGETS * SICKLMSwidgets=(SICKLMSSTORAGEWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

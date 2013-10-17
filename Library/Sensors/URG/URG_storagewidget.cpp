#include "URG.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)(*widgets);
	if(URGwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new URGSTORAGEWIDGETS;
		URGwidgets=(URGSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: URG point to a memory block
		
	}

	URGwidgets->label.setFrameStyle(QFrame::Box);
	URGwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	URGwidgets->label.setText(widget->windowTitle());
	URGwidgets->status.setFrameStyle(QFrame::Box);
	URGwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	URGwidgets->status.setText("Standby");
	URGwidgets->filename.setToolTip("Filename");
	URGwidgets->filename.setText("No File");
	URGwidgets->framenum.setToolTip("Frame count");
	URGwidgets->framenum.setText("0");
	URGwidgets->info.setToolTip("Data Timestamp");
	URGwidgets->info.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(URGwidgets->label));
	hlayout1->addWidget(&(URGwidgets->status));
	vlayout->addWidget(&(URGwidgets->filename));
	hlayout2->addWidget(&(URGwidgets->framenum));
	hlayout2->addWidget(&(URGwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addWidget(&(URGwidgets->filename));
	vlayout->addLayout(hlayout2);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)(*widgets);
	if(URGwidgets==NULL)
	{//case1: widgets point to a NULL
		
		URGwidgets=(URGSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: URG point to a memory block
		delete URGwidgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGSTORAGEPARAMS * URGparams=(URGSTORAGEPARAMS *)params;
	URGwidgets->status.setText(QString("Opened"));
	URGwidgets->filename.setText(URGparams->file.fileName());
	URGwidgets->framenum.setText("0");
	URGwidgets->info.setText("No Data");
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Open Error"));
	URGwidgets->filename.setText("No File");
	URGwidgets->framenum.setText("0");
	URGwidgets->info.setText("No Data");
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGSENSORDATA * URGdata=(URGSENSORDATA *)data;
	URGwidgets->status.setText(QString("Stored"));
	int num=URGwidgets->framenum.text().toInt()+1;
	URGwidgets->framenum.setText(QString("%1").arg(num));
	URGwidgets->info.setText(QString("%1 - %2").arg(URGdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(URGdata->timestamp));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Store Error"));
	URGwidgets->info.setText(QString("No Data"));
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	URGSTORAGEWIDGETS * URGwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGwidgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

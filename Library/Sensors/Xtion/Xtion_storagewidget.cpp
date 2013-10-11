#include "Xtion.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)(*widgets);
	if(Xtionwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new XTIONSTORAGEWIDGETS;
		Xtionwidgets=(XTIONSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Xtion point to a memory block
		
	}
	Xtionwidgets->label.setFrameStyle(QFrame::Box);
	Xtionwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Xtionwidgets->label.setText(widget->windowTitle());
	Xtionwidgets->status.setFrameStyle(QFrame::Box);
	Xtionwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Xtionwidgets->status.setText("Standby");
	Xtionwidgets->depthfilename.setToolTip("Depth Filename");
	Xtionwidgets->depthfilename.setText("No File");
	Xtionwidgets->colorfilename.setToolTip("Color Filename");
	Xtionwidgets->colorfilename.setText("No File");
	Xtionwidgets->framenum.setToolTip("Frame count");
	Xtionwidgets->framenum.setText("0");
	Xtionwidgets->info.setToolTip("Data Timestamp");
	Xtionwidgets->info.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(Xtionwidgets->label));
	hlayout1->addWidget(&(Xtionwidgets->status));
	hlayout2->addWidget(&(Xtionwidgets->framenum));
	hlayout2->addWidget(&(Xtionwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addWidget(&(Xtionwidgets->depthfilename));
	vlayout->addWidget(&(Xtionwidgets->colorfilename));
	vlayout->addLayout(hlayout2);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)(*widgets);
	if(Xtionwidgets==NULL)
	{//case1: widgets point to a NULL
		
		Xtionwidgets=(XTIONSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Xtion point to a memory block
		delete Xtionwidgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)widgets;
	XTIONSTORAGEPARAMS * Xtionparams=(XTIONSTORAGEPARAMS *)params;
	Xtionwidgets->status.setText(QString("Opened"));
	Xtionwidgets->depthfilename.setText(Xtionparams->depthvideofilename);
	Xtionwidgets->colorfilename.setText(Xtionparams->colorvideofilename);
	Xtionwidgets->framenum.setText("0");
	Xtionwidgets->info.setText("No Data");
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Open Error"));
	Xtionwidgets->depthfilename.setText("No File");
	Xtionwidgets->colorfilename.setText("No File");
	Xtionwidgets->framenum.setText("0");
	Xtionwidgets->info.setText("No Data");
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)widgets;
	XTIONSENSORDATA * Xtiondata=(XTIONSENSORDATA *)data;
	Xtionwidgets->status.setText(QString("Stored"));
	int num=Xtionwidgets->framenum.text().toInt()+1;
	Xtionwidgets->framenum.setText(QString("%1").arg(num));
	Xtionwidgets->info.setText(QString("Depth: %1, Color: %2 (%3 x %4)").arg(Xtiondata->depthtimestamp.toString("hh:mm:ss:zzz")).arg(Xtiondata->colortimestamp.toString("hh:mm:ss:zzz")).arg(Xtiondata->depth.cols).arg(Xtiondata->depth.rows));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Store Error"));
	Xtionwidgets->info.setText(QString("No Data"));
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	XTIONSTORAGEWIDGETS * Xtionwidgets=(XTIONSTORAGEWIDGETS *)widgets;
	Xtionwidgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

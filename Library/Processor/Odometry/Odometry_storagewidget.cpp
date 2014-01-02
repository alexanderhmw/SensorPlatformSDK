#include "Odometry.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)(*widgets);
	if(Odometrywidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new ODOMETRYSTORAGEWIDGETS;
		Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Odometry point to a memory block
		
	}

	Odometrywidgets->receivelabel.setFrameStyle(QFrame::Box);
	Odometrywidgets->receivelabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Odometrywidgets->receivelabel.setText(widget->windowTitle()+QString("_Receiver"));
	Odometrywidgets->receivestatus.setFrameStyle(QFrame::Box);
	Odometrywidgets->receivestatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Odometrywidgets->receivestatus.setText("Standby");
	Odometrywidgets->filename.setToolTip("Filename");
	Odometrywidgets->filename.setText("No File");
	Odometrywidgets->receiveframenum.setToolTip("Frame count");
	Odometrywidgets->receiveframenum.setText("0");
	Odometrywidgets->receiveinfo.setToolTip("Data Timestamp");
	Odometrywidgets->receiveinfo.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(Odometrywidgets->receivelabel));
	hlayout1->addWidget(&(Odometrywidgets->receivestatus));
	vlayout->addWidget(&(Odometrywidgets->filename));
	hlayout2->addWidget(&(Odometrywidgets->receiveframenum));
	hlayout2->addWidget(&(Odometrywidgets->receiveinfo));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);

	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)(*widgets);
	if(Odometrywidgets==NULL)
	{//case1: widgets point to a NULL
		
		Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Odometry point to a memory block
		delete Odometrywidgets;
		*widgets=NULL;		

	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)widgets;
	ODOMETRYSTORAGEPARAMS * Odometryparams=(ODOMETRYSTORAGEPARAMS *)params;
	Odometrywidgets->receivestatus.setText(QString("Opened"));
	Odometrywidgets->filename.setText(Odometryparams->file.fileName());
	Odometrywidgets->receiveframenum.setText("0");
	Odometrywidgets->receiveinfo.setText("No Data");
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)widgets;
	Odometrywidgets->receivestatus.setText(QString("Open Error"));
	Odometrywidgets->filename.setText("No File");
	Odometrywidgets->receiveframenum.setText("0");
	Odometrywidgets->receiveinfo.setText("No Data");
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)widgets;
	ODOMETRYPROCESSOROUTPUTDATA * Odometrydata=(ODOMETRYPROCESSOROUTPUTDATA *)data;
	Odometrywidgets->receivestatus.setText(QString("Stored"));
	int num=Odometrywidgets->receiveframenum.text().toInt()+1;
	Odometrywidgets->receiveframenum.setText(QString("%1").arg(num));
	double x = (Odometrydata->x);
	double y = (Odometrydata->y);
	double theta = (Odometrydata->theta);
	Odometrywidgets->receiveinfo.setText(QString("%1 - %2 - %3 - %4").arg(Odometrydata->qtimestamp.toString("hh:mm:ss:zzz")).arg(theta).arg(x).arg(y));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)widgets;
	Odometrywidgets->receivestatus.setText(QString("Store Error"));
	Odometrywidgets->receiveinfo.setText("No Data");
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)widgets;
	Odometrywidgets->receivestatus.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	ODOMETRYSTORAGEWIDGETS * Odometrywidgets=(ODOMETRYSTORAGEWIDGETS *)widgets;
	Odometrywidgets->receivestatus.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

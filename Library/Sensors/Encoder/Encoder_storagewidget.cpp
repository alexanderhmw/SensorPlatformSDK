#include "Encoder.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)(*widgets);
	if(Encoderwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new ENCODERSTORAGEWIDGETS;
		Encoderwidgets=(ENCODERSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: Encoder point to a memory block
		
	}

	Encoderwidgets->receivelabel.setFrameStyle(QFrame::Box);
	Encoderwidgets->receivelabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Encoderwidgets->receivelabel.setText(widget->windowTitle()+QString("_Receiver"));
	Encoderwidgets->receivestatus.setFrameStyle(QFrame::Box);
	Encoderwidgets->receivestatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	Encoderwidgets->receivestatus.setText("Standby");
	Encoderwidgets->filename.setToolTip("Filename");
	Encoderwidgets->filename.setText("No File");
	Encoderwidgets->receiveframenum.setToolTip("Frame count");
	Encoderwidgets->receiveframenum.setText("0");
	Encoderwidgets->receiveinfo.setToolTip("Data Timestamp");
	Encoderwidgets->receiveinfo.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(Encoderwidgets->receivelabel));
	hlayout1->addWidget(&(Encoderwidgets->receivestatus));
	vlayout->addWidget(&(Encoderwidgets->filename));
	hlayout2->addWidget(&(Encoderwidgets->receiveframenum));
	hlayout2->addWidget(&(Encoderwidgets->receiveinfo));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);

	widget->setLayout(vlayout);
	widget->adjustSize();
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
		delete Encoderwidgets;
		*widgets=NULL;		
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	ENCODERSTORAGEPARAMS * Encoderparams=(ENCODERSTORAGEPARAMS *)params;
	Encoderwidgets->receivestatus.setText(QString("Opened"));
	Encoderwidgets->filename.setText(Encoderparams->file.fileName());
	Encoderwidgets->receiveframenum.setText("0");
	Encoderwidgets->receiveinfo.setText("No Data");
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Open Error"));
	Encoderwidgets->filename.setText("No File");
	Encoderwidgets->receiveframenum.setText("0");
	Encoderwidgets->receiveinfo.setText("No Data");
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	ENCODERCOMMUNICATORRECEIVEDATA * Encoderdata=(ENCODERCOMMUNICATORRECEIVEDATA *)data;
	Encoderwidgets->receivestatus.setText(QString("Stored"));
	int num=Encoderwidgets->receiveframenum.text().toInt()+1;
	Encoderwidgets->receiveframenum.setText(QString("%1").arg(num));
	short angle=*((short *)(Encoderdata->datagram.data()));
	short encoder=*((short *)(Encoderdata->datagram.data()+sizeof(angle)));
	Encoderwidgets->receiveinfo.setText(QString("%1 - %2 - %3").arg(Encoderdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(angle).arg(encoder));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Store Error"));
	Encoderwidgets->receiveinfo.setText("No Data");
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	ENCODERSTORAGEWIDGETS * Encoderwidgets=(ENCODERSTORAGEWIDGETS *)widgets;
	Encoderwidgets->receivestatus.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

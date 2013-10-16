#include "UDPReceiver.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)(*widgets);
	if(UDPReceiverwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new UDPRECEIVERSTORAGEWIDGETS;
		UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: UDPReceiver point to a memory block
		
	}

	UDPReceiverwidgets->label.setFrameStyle(QFrame::Box);
	UDPReceiverwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	UDPReceiverwidgets->label.setText(widget->windowTitle());
	UDPReceiverwidgets->status.setFrameStyle(QFrame::Box);
	UDPReceiverwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	UDPReceiverwidgets->status.setText("Standby");
	UDPReceiverwidgets->framenum.setToolTip("Frame count");
	UDPReceiverwidgets->framenum.setText("0");
	UDPReceiverwidgets->info.setToolTip("Data Timestamp");
	UDPReceiverwidgets->info.setText("No Data");
	UDPReceiverwidgets->datagram.setToolTip("Datagram");
	UDPReceiverwidgets->datagram.setText("No Datagram");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(UDPReceiverwidgets->label));
	hlayout1->addWidget(&(UDPReceiverwidgets->status));
	hlayout2->addWidget(&(UDPReceiverwidgets->framenum));
	hlayout2->addWidget(&(UDPReceiverwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addWidget(&(UDPReceiverwidgets->datagram));
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)(*widgets);
	if(UDPReceiverwidgets==NULL)
	{//case1: widgets point to a NULL
		
		UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: UDPReceiver point to a memory block
		delete UDPReceiverwidgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)widgets;
	UDPRECEIVERSTORAGEPARAMS * UDPReceiverparams=(UDPRECEIVERSTORAGEPARAMS *)params;
	UDPReceiverwidgets->status.setText(QString("Opened"));
	UDPReceiverwidgets->filename.setText(UDPReceiverparams->file.fileName());
	UDPReceiverwidgets->framenum.setText("0");
	UDPReceiverwidgets->info.setText("No Data");
	UDPReceiverwidgets->datagram.setText("No Datagram");
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Opened Error"));
	UDPReceiverwidgets->filename.setText("No File");
	UDPReceiverwidgets->framenum.setText("0");
	UDPReceiverwidgets->info.setText("No Data");
	UDPReceiverwidgets->datagram.setText("No Datagram");
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)widgets;
	UDPRECEIVERSTORAGEDATA * UDPReceiverdata=(UDPRECEIVERSTORAGEDATA *)data;
	UDPReceiverwidgets->status.setText(QString("Stored"));
	int num=UDPReceiverwidgets->framenum.text().toInt()+1;
	UDPReceiverwidgets->framenum.setText(QString("%1").arg(num));
	UDPReceiverwidgets->info.setText(QString("%1_%2_%3").arg(UDPReceiverdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(UDPReceiverdata->senderip.toString()).arg(UDPReceiverdata->senderport));
	UDPReceiverwidgets->datagram.setText(QString(UDPReceiverdata->datagram));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Store Error"));
	UDPReceiverwidgets->info.setText(QString("No Data"));
	UDPReceiverwidgets->datagram.setText("No Datagram");
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	UDPRECEIVERSTORAGEWIDGETS * UDPReceiverwidgets=(UDPRECEIVERSTORAGEWIDGETS *)widgets;
	UDPReceiverwidgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

#include "XWGPS.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)(*widgets);
	if(XWGPSwidgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new XWGPSSTORAGEWIDGETS;
		XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: XWGPS point to a memory block
		
	}

	XWGPSwidgets->receivelabel.setFrameStyle(QFrame::Box);
	XWGPSwidgets->receivelabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	XWGPSwidgets->receivelabel.setText(widget->windowTitle()+QString("_Receiver"));
	XWGPSwidgets->receivestatus.setFrameStyle(QFrame::Box);
	XWGPSwidgets->receivestatus.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	XWGPSwidgets->receivestatus.setText("Standby");
	XWGPSwidgets->receiveframenum.setToolTip("Frame count");
	XWGPSwidgets->receiveframenum.setText("0");
	XWGPSwidgets->receiveinfo.setToolTip("Data Timestamp");
	XWGPSwidgets->receiveinfo.setText("No Data");
	XWGPSwidgets->receivedatagram.setToolTip("Datagram");
	XWGPSwidgets->receivedatagram.clear();

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(XWGPSwidgets->receivelabel));
	hlayout1->addWidget(&(XWGPSwidgets->receivestatus));
	hlayout2->addWidget(&(XWGPSwidgets->receiveframenum));
	hlayout2->addWidget(&(XWGPSwidgets->receiveinfo));
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addWidget(&(XWGPSwidgets->receivedatagram));

	widget->setLayout(vlayout);
	widget->adjustSize();
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
		delete XWGPSwidgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSSTORAGEPARAMS * XWGPSparams=(XWGPSSTORAGEPARAMS *)params;
	XWGPSwidgets->receivestatus.setText(QString("Opened"));
	XWGPSwidgets->receiveframenum.setText("0");
	XWGPSwidgets->receiveinfo.setText("No Data");
	XWGPSwidgets->receivedatagram.clear();
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Open Error"));
	XWGPSwidgets->receiveframenum.setText("0");
	XWGPSwidgets->receiveinfo.setText("No Data");
	XWGPSwidgets->receivedatagram.clear();
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSCOMMUNICATORRECEIVEDATA * XWGPSdata=(XWGPSCOMMUNICATORRECEIVEDATA *)data;
	XWGPSwidgets->receivestatus.setText(QString("Stored"));
	int num=XWGPSwidgets->receiveframenum.text().toInt()+1;
	XWGPSwidgets->receiveframenum.setText(QString("%1").arg(num));
	XWGPSwidgets->receiveinfo.setText(QString("%1_Shv<%2,%3,%4>_Rot<%5,%6,%7>").arg(XWGPSdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(XWGPSdata->sx).arg(XWGPSdata->sy).arg(XWGPSdata->sz).arg(XWGPSdata->rx).arg(XWGPSdata->ry).arg(XWGPSdata->rz));
	XWGPSwidgets->receivedatagram.appendPlainText(QString(XWGPSdata->datagram));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Store Error"));
	XWGPSwidgets->receiveinfo.setText("No Data");
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	XWGPSSTORAGEWIDGETS * XWGPSwidgets=(XWGPSSTORAGEWIDGETS *)widgets;
	XWGPSwidgets->receivestatus.setText(QString("Closed"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

#include "PointGreyFlea2.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)	//initial the widget
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)(*widgets);
	if(PointGreyFlea2widgets==NULL)
	{//case1: widgets point to a NULL
		*widgets=(void *)new POINTGREYFLEA2STORAGEWIDGETS;
		PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}

	PointGreyFlea2widgets->label.setFrameStyle(QFrame::Box);
	PointGreyFlea2widgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	PointGreyFlea2widgets->label.setText(widget->windowTitle());
	PointGreyFlea2widgets->status.setFrameStyle(QFrame::Box);
	PointGreyFlea2widgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	PointGreyFlea2widgets->status.setText("Standby");
	PointGreyFlea2widgets->imagefilename.setToolTip("Depth Filename");
	PointGreyFlea2widgets->imagefilename.setText("No File");
	PointGreyFlea2widgets->framenum.setToolTip("Frame count");
	PointGreyFlea2widgets->framenum.setText("0");
	PointGreyFlea2widgets->info.setToolTip("Data Timestamp");
	PointGreyFlea2widgets->info.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(PointGreyFlea2widgets->label));
	hlayout1->addWidget(&(PointGreyFlea2widgets->status));
	hlayout2->addWidget(&(PointGreyFlea2widgets->framenum));
	hlayout2->addWidget(&(PointGreyFlea2widgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addWidget(&(PointGreyFlea2widgets->imagefilename));
	vlayout->addLayout(hlayout2);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)	//release the widget
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)(*widgets);
	if(PointGreyFlea2widgets==NULL)
	{//case1: widgets point to a NULL
		
		PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)(*widgets);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2widgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)	//handle openstorage signal
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)widgets;
	POINTGREYFLEA2STORAGEPARAMS * PointGreyFlea2params=(POINTGREYFLEA2STORAGEPARAMS *)params;
	PointGreyFlea2widgets->status.setText(QString("Opened"));
	PointGreyFlea2widgets->imagefilename.setText(PointGreyFlea2params->videofilename);
	PointGreyFlea2widgets->framenum.setText("0");
	PointGreyFlea2widgets->info.setText("No Data");
}

void storageOpenError(void * widgets)	//handle openstorageerror signal
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Open Error"));
	PointGreyFlea2widgets->imagefilename.setText("No File");
	PointGreyFlea2widgets->framenum.setText("0");
	PointGreyFlea2widgets->info.setText("No Data");
}

void dataStore(void * widgets,void * data)	//handle storedata signal
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)widgets;
	POINTGREYFLEA2SENSORDATA * PointGreyFlea2data=(POINTGREYFLEA2SENSORDATA *)data;
	PointGreyFlea2widgets->status.setText(QString("Stored"));
	int num=PointGreyFlea2widgets->framenum.text().toInt()+1;
	PointGreyFlea2widgets->framenum.setText(QString("%1").arg(num));
	PointGreyFlea2widgets->info.setText(QString("Image: %1, (%2 x %3)").arg(PointGreyFlea2data->timestamp.toString("hh:mm:ss:zzz")).arg(PointGreyFlea2data->image.cols).arg(PointGreyFlea2data->image.rows));
}

void dataStoreError(void * widgets)	//handle storedataerror signal
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Store Error"));
	PointGreyFlea2widgets->info.setText(QString("No Data"));
}

void storageClose(void * widgets)	//handle closestoragesignal
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Closed"));
}

void storageCloseError(void * widgets)	//handle closestorageerror signal
{
	POINTGREYFLEA2STORAGEWIDGETS * PointGreyFlea2widgets=(POINTGREYFLEA2STORAGEWIDGETS *)widgets;
	PointGreyFlea2widgets->status.setText(QString("Close Error"));
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

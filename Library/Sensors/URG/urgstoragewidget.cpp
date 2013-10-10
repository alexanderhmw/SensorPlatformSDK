#include"urg.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)
{
	if(*widgets==NULL)
	{
		*widgets=(void *)new URGSTORAGEWIDGETS;
	}
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)(*widgets);

	tempwidgets->label.setFrameStyle(QFrame::Box);
	tempwidgets->label.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	tempwidgets->label.setText(widget->windowTitle());
	tempwidgets->status.setFrameStyle(QFrame::Box);
	tempwidgets->status.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	tempwidgets->status.setText("Standby");
	tempwidgets->filename.setToolTip("Filename");
	tempwidgets->filename.setText("No File");
	tempwidgets->framenum.setToolTip("Frame count");
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setToolTip("Data Timestamp");
	tempwidgets->info.setText("No Data");

	QVBoxLayout * vlayout=new QVBoxLayout;
	QHBoxLayout * hlayout1=new QHBoxLayout;
	QHBoxLayout * hlayout2=new QHBoxLayout;

	hlayout1->addWidget(&(tempwidgets->label));
	hlayout1->addWidget(&(tempwidgets->status));
	hlayout2->addWidget(&(tempwidgets->framenum));
	hlayout2->addWidget(&(tempwidgets->info));
	vlayout->addLayout(hlayout1);
	vlayout->addWidget(&(tempwidgets->filename));
	vlayout->addLayout(hlayout2);
	widget->setLayout(vlayout);
	widget->adjustSize();
}

void releaseWidgetsStorage(QWidget * widget, void ** widgets)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)(*widgets);
	if(tempwidgets!=NULL)
	{
		delete tempwidgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)widgets;
	URGSTORAGEPARAMS * tempparams=(URGSTORAGEPARAMS *)params;
	tempwidgets->status.setText(QString("Opened"));
	tempwidgets->filename.setText(tempparams->file.fileName());
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
}

void storageOpenError(void * widgets)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Open Error"));
	tempwidgets->filename.setText("No File");
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
}

void dataStore(void * widgets,void * data)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Stored"));
	int num=tempwidgets->framenum.text().toInt()+1;
	tempwidgets->framenum.setText(QString("%1").arg(num));
	URGDATA * tempdata=(URGDATA *)data;
	tempwidgets->info.setText(QString("%1 - %2").arg(tempdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(tempdata->timestamp));
}

void dataStoreError(void * widgets)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Store Error"));
	tempwidgets->info.setText(QString("No Data"));
}

void storageClose(void * widgets)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Closed"));
}

void storageCloseError(void * widgets)
{
	URGSTORAGEWIDGETS * tempwidgets=(URGSTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Close Error"));
}
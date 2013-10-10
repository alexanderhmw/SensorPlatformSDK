#include"usbcamera.h"
#include<FuncLibrary\storagewidgetfunc.h>

void setWidgetsStorage(QWidget * widget, void ** widgets)
{
	if(*widgets==NULL)
	{
		*widgets=(void *)new USBCAMERASTORAGEWIDGETS;
	}
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)(*widgets);

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
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)(*widgets);
	if(tempwidgets!=NULL)
	{
		delete tempwidgets;
		*widgets=NULL;
	}
}

void storageOpen(void * widgets, void * params)
{
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)widgets;
	USBCAMERASTORAGEPARAMS * tempparams=(USBCAMERASTORAGEPARAMS *)params;
	tempwidgets->status.setText(QString("Opened"));
	tempwidgets->filename.setText(tempparams->videofilename);
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
}

void storageOpenError(void * widgets)
{
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Open Error"));
	tempwidgets->filename.setText("No File");
	tempwidgets->framenum.setText("0");
	tempwidgets->info.setText("No Data");
}

void dataStore(void * widgets,void * data)
{
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Stored"));
	int num=tempwidgets->framenum.text().toInt()+1;
	tempwidgets->framenum.setText(QString("%1").arg(num));
	USBCAMERADATA * tempdata=(USBCAMERADATA *)data;
	tempwidgets->info.setText(QString("%1 (%2 x %3)").arg(tempdata->qtimestamp.toString("hh:mm:ss:zzz")).arg(tempdata->image.cols).arg(tempdata->image.rows));
    //tempwidgets->image.resize(tempwidgets->image.pixmap()->size()); 
}

void dataStoreError(void * widgets)
{
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Store Error"));
	tempwidgets->info.setText(QString("No Data"));
}

void storageClose(void * widgets)
{
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Closed"));
}

void storageCloseError(void * widgets)
{
	USBCAMERASTORAGEWIDGETS * tempwidgets=(USBCAMERASTORAGEWIDGETS *)widgets;
	tempwidgets->status.setText(QString("Close Error"));
}
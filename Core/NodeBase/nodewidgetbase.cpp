#include "nodewidgetbase.h"

NodeWidgetBase::NodeWidgetBase(NodeBase * nodebase, QWidget *parent)
	: QWidget(parent)
{
	_nodebase=nodebase;
	_library.setFileName(_nodebase->getLibraryName());
	if(_library.load())
	{
		FptrLoadCheckType(setWidgetsFptr,setWidgets,_library,_nodebase->getNodeType());
		FptrLoadCheckType(releaseWidgetsFptr,releaseWidgets,_library,_nodebase->getNodeType());
	}
	else
	{
		QMessageBox::information(NULL,QString("NodeWidget Error"),QString("Share Library %1 missing").arg(_library.fileName()));
		exit(0);
	}
	QString widgetinfo=QString("%1_%2_%3").arg(nodebase->getNodeType()).arg(nodebase->getNodeClass()).arg(nodebase->getNodeName());
	this->setWindowTitle(widgetinfo);

	_widgets=NULL;
	setWidgets(this,&_widgets);
}

NodeWidgetBase::~NodeWidgetBase()
{
	releaseWidgets(this,&_widgets);
}

QString NodeWidgetBase::getLibraryName()
{
	return _library.fileName();
}

QString NodeWidgetBase::getNodeType()
{
	return _nodebase->getNodeType();
}

QString NodeWidgetBase::getNodeClass()
{
	return _nodebase->getNodeClass();
}

QString NodeWidgetBase::getNodeName()
{
	return _nodebase->getNodeName();
}

QString NodeWidgetBase::getConfigFilename()
{
	return _nodebase->getConfigFilename();
}

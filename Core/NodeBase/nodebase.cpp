#include "nodebase.h"

NodeBase::NodeBase(QString libraryname, QString nodetype, QString nodename)
{
	_library.setFileName(libraryname);
	_nodetype=nodetype;
	_nodename=nodename;
	if(_library.load())
	{
		FptrLoadCheckType(loadParamsFptr,loadParams,_library,_nodetype);
		FptrLoadCheckType(releaseParamsFptr,releaseParams,_library,_nodetype);
	}
	else
	{
		QMessageBox::information(NULL,QString("Node Error"),QString("Share Library %1 missing").arg(_library.fileName()));
		exit(0);
	}
	_params=NULL;
}

NodeBase::~NodeBase()
{
	releaseParams(&_params);
}

QString NodeBase::getLibraryName()
{
	return _library.fileName();
}

QString NodeBase::getNodeType()
{

	return _nodetype;
}

QString NodeBase::getNodeClass()
{
	return _nodeclass;
}

QString NodeBase::getNodeName()
{
	return _nodename;
}

QString NodeBase::getConfigFilename()
{
	return _configfilename;
}

void * NodeBase::getParams()
{
	return _params;
}

void NodeBase::loadParamsSlot(QString configfilename)
{
	_configfilename=configfilename;
	if(!loadParams(_configfilename, _nodetype,_nodeclass,_nodename,&_params))
	{
		QMessageBox::information(NULL,QString("%1 Error").arg(_nodetype),QString("Parameters Initialization Error:%1_%2").arg(_nodeclass).arg(_nodename));
		exit(0);
	}
}

bool NodeBase::connectLoadParamsSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(loadParamsSlot(QString)));
}

bool NodeBase::disconnectLoadParamsSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(loadParamsSlot(QString)));
}
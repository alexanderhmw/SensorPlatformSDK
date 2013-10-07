#ifndef NODEBASE_H
#define NODEBASE_H

#include<qobject.h>
#include<qstring.h>
#include<qlibrary.h>
#include<qmessagebox.h>

#define FptrLoadCheck(fptrtype,fptr,library) \
	fptr=(fptrtype) library.resolve(#fptr);	\
	if(fptr==NULL)	\
{QMessageBox::information(NULL,QString("Node Error"),QString("No function %1 in Share Library %2").arg(QString(#fptr)).arg(library.fileName()));exit(0);}

#define FptrLoadCheckType(fptrtype,fptr,library,nodetype) \
	fptr=(fptrtype) library.resolve(QString("%1%2").arg(#fptr).arg(nodetype).toLocal8Bit().constData());	\
	if(fptr==NULL)	\
{QMessageBox::information(NULL,QString("%1 Error").arg(nodetype),QString("No function %1 in Share Library %2").arg(QString(#fptr)).arg(library.fileName()));exit(0);}

class NodeBase : public QObject
{
	Q_OBJECT
public:
	NodeBase(QString libraryname, QString nodetype, QString nodename);
	~NodeBase();
protected:
	QLibrary _library;
	QString _nodetype;
	QString _nodeclass;
	QString _nodename;
	QString _configfilename;
public:
	QString getLibraryName();
	QString getNodeType();
	QString getNodeClass();
	QString getNodeName();
	QString getConfigFilename();
protected:
	void * _params;
public:
	void * getParams();
protected:
	typedef bool (*loadParamsFptr)(QString configfilename,QString nodetype, QString & nodeclass, QString nodename, void ** params);
	loadParamsFptr loadParams;
	typedef void (*releaseParamsFptr)(void ** params);
	releaseParamsFptr releaseParams;
public slots:
	void loadParamsSlot(QString configfilename);
public:
	bool connectLoadParamsSignal(QObject * sender, const char * signal);
	bool disconnectLoadParamsSignal(QObject *sender, const char *signal);
};

#endif // NODEBASE_H

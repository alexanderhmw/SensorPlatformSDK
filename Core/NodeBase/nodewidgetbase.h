#ifndef NODEWIDGETBASE_H
#define NODEWIDGETBASE_H

#include <qwidget.h>
#include <NodeBase\nodebase.h>

class NodeWidgetBase : public QWidget
{
	Q_OBJECT
public:
	NodeWidgetBase(NodeBase * nodebase, QWidget *parent=NULL);
	~NodeWidgetBase();
protected:
	NodeBase * _nodebase;
	QLibrary _library;
public:
	QString getLibraryName();
	QString getNodeType();
	QString getNodeClass();
	QString getNodeName();
	QString getConfigFilename();
protected:
	void * _widgets;
public:
	void * getWidgets();
protected:
	typedef void (*setWidgetsFptr)(QWidget * widget, void ** widgets);
	setWidgetsFptr setWidgets;
	typedef void (*releaseWidgetsFptr)(QWidget * widget, void ** widgets);
	releaseWidgetsFptr releaseWidgets;
};

#endif // NODEWIDGETBASE_H

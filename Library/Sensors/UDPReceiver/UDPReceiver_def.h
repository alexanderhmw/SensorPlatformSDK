#ifndef UDPRECEIVER_DEF_H
#define UDPRECEIVER_DEF_H

#include <QtCore/qglobal.h>
#include <qudpsocket.h>
#include <qhostaddress.h>
#include <qhostinfo.h>
#include <qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include <qdatetime.h>

struct Q_DECL_EXPORT UDPRECEIVERSENSORPARAMS	//sensor parameters
{
	QUdpSocket udpsocket;
	quint16 port;
};

struct Q_DECL_EXPORT UDPRECEIVERSENSORDATA	//sensor data
{
	QTime qtimestamp; 
	QByteArray datagram;
	QHostAddress senderip;
	quint16 senderport;
};

struct Q_DECL_EXPORT UDPRECEIVERSENSORWIDGETS	//sensor widgets
{
	QLabel label;
	QLabel status;
	QLineEdit framenum;
	QLineEdit info;
	QLineEdit datagram;
};

struct Q_DECL_EXPORT UDPRECEIVERSTORAGEPARAMS	//storage parameters
{
	QFile file;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT UDPRECEIVERSTORAGEDATA	//storage data
{
	QTime qtimestamp; 
	QByteArray datagram;
	QHostAddress senderip;
	quint16 senderport;
};

struct Q_DECL_EXPORT UDPRECEIVERSTORAGEWIDGETS	//storage widgets
{
	QLabel label;
	QLabel status;
	QLineEdit filename;
	QLineEdit framenum;
	QLineEdit info;
	QLineEdit datagram;
};

#endif
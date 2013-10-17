#ifndef ENCODER_DEF_H
#define ENCODER_DEF_H

#include <QtCore/qglobal.h>
#include <QtCore/qglobal.h>
#include <qextserialport.h>
#include <qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include <qdatetime.h>
#include <qplaintextedit.h>

struct Q_DECL_EXPORT ENCODERCOMMUNICATORPARAMS	//communicator parameters
{
	QextSerialPort serialport;
	QString port;
	BaudRateType baudrate;
	DataBitsType databitstype;
	ParityType paritytype;
	StopBitsType stopbitstype;
	FlowType flowtype;
	long timeout;
	QextSerialPort::QueryMode querymode;
	int recvpacksize;
	QByteArray packhead;
	QByteArray packtail;
	QByteArray databuffer;
};

struct Q_DECL_EXPORT ENCODERCOMMUNICATORRECEIVEDATA	//communicator receive data
{
	QTime qtimestamp;
	QByteArray datagram;
};

struct Q_DECL_EXPORT ENCODERCOMMUNICATORSENDDATA	//communicator send data
{
	QByteArray datagram;
};

struct Q_DECL_EXPORT ENCODERCOMMUNICATORWIDGETS	//communicator widgets
{
	QLabel receivelabel;
	QLabel receivestatus;
	QLineEdit receiveframenum;
	QLineEdit receiveinfo;
	QLabel sendlabel;
	QLabel sendstatus;
	QLineEdit sendframenum;
	QLineEdit sendinfo;
};

struct Q_DECL_EXPORT ENCODERSTORAGEPARAMS	//storage parameters
{
	QFile file;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT ENCODERSTORAGEDATA	//storage data
{
	QTime qtimestamp;
	QByteArray datagram;	
};

struct Q_DECL_EXPORT ENCODERSTORAGEWIDGETS	//storage widgets
{
	QLabel receivelabel;
	QLabel receivestatus;
	QLineEdit filename;
	QLineEdit receiveframenum;
	QLineEdit receiveinfo;
};

#endif
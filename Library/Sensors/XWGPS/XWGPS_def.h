#ifndef XWGPS_DEF_H
#define XWGPS_DEF_H

#include <QtCore/qglobal.h>
#include <qextserialport.h>
#include <coordinateconvertion.h>
#include <qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include <qdatetime.h>
#include <qplaintextedit.h>

struct Q_DECL_EXPORT XWGPSCOMMUNICATORPARAMS	//communicator parameters
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

struct Q_DECL_EXPORT XWGPSCOMMUNICATORRECEIVEDATA	//communicator data
{
	QByteArray datagram;
	QTime qtimestamp;
	double gpstime;
	double rx,ry,rz;
	double sx,sy,sz;
	bool valid;
	bool gpsstatus;
};

struct Q_DECL_EXPORT XWGPSCOMMUNICATORSENDDATA
{
	QByteArray datagram;
};

struct Q_DECL_EXPORT XWGPSCOMMUNICATORWIDGETS	//communicator widgets
{
	QLabel receivelabel;
	QLabel receivestatus;
	QLineEdit receiveframenum;
	QLineEdit receiveinfo;
	QPlainTextEdit receivedatagram;
	QLabel sendlabel;
	QLabel sendstatus;
	QLineEdit sendframenum;
	QLineEdit sendinfo;
};

struct Q_DECL_EXPORT XWGPSSTORAGEPARAMS	//storage parameters
{
	QFile file;
	QFile logfile;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT XWGPSSTORAGEDATA	//storage data
{
	QByteArray datagram;
	QTime qtimestamp;
	double gpstime;
	double rx,ry,rz;
	double sx,sy,sz;
	bool valid;
	bool gpsstatus;
};

struct Q_DECL_EXPORT XWGPSSTORAGEWIDGETS	//storage widgets
{
	QLabel receivelabel;
	QLabel receivestatus;
	QLineEdit receiveframenum;
	QLineEdit receiveinfo;
	QPlainTextEdit receivedatagram;
};

#endif
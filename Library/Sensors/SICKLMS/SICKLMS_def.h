#ifndef SICKLMS_DEF_H
#define SICKLMS_DEF_H

#include <QtCore/qglobal.h>
#include <serialportlib\qextserialport.h>
#include <qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include <qdatetime.h>
#include <qplaintextedit.h>

enum BAUDRATEMODE
{
	BAUD_9600=9600,
	BAUD_19200=19200,
	BAUD_38400=38400,
	BAUD_500000=500000
};

enum RESOLUTIONMODE
{
	RES_180_050,
	RES_180_100,
	RES_100_025,
	RES_100_050,
	RES_100_100,
	RES_180_025
};

enum MEASUREMENTMODE
{
	UNIT_CM,
	UNIT_MM
};

struct Q_DECL_EXPORT SICKLMSSENSORPARAMS	//sensor parameters
{
	QextSerialPort serialport;
	QString port;
	
	BAUDRATEMODE baudrate;
	RESOLUTIONMODE resolution;
	MEASUREMENTMODE measurement;
};

struct Q_DECL_EXPORT SICKLMSSENSORDATA	//sensor data
{
	QTime qtimestamp;
	int datasize;
	short * data;
};

struct Q_DECL_EXPORT SICKLMSSENSORWIDGETS	//sensor widgets
{

};

struct Q_DECL_EXPORT SICKLMSSTORAGEPARAMS	//storage parameters
{

};

struct Q_DECL_EXPORT SICKLMSSTORAGEDATA	//storage data
{

};

struct Q_DECL_EXPORT SICKLMSSTORAGEWIDGETS	//storage widgets
{

};

#endif
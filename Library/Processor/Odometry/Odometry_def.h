#ifndef ODOMETRY_DEF_H
#define ODOMETRY_DEF_H

#include <QtCore/qglobal.h>
#include <qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include <qdatetime.h>
#include <qplaintextedit.h>

struct Q_DECL_EXPORT ODOMETRYPROCESSORPARAMS	//processor parameters
{
	double curtheta;
	double curx;
	double cury;

	double stepsize;
};

struct Q_DECL_EXPORT ODOMETRYPROCESSORINPUTDATA	//processor inputdata
{
	QTime qtimestamp;
	QByteArray datagram;
};

struct Q_DECL_EXPORT ODOMETRYPROCESSOROUTPUTDATA	//processor outputdata
{
	QTime qtimestamp;
	double theta;
	double x;
	double y;
};

struct Q_DECL_EXPORT ODOMETRYSTORAGEPARAMS	//storage parameters
{
	QFile file;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT ODOMETRYSTORAGEDATA	//storage data
{
	QTime qtimestamp;
	double theta;
	double x;
	double y;
};

struct Q_DECL_EXPORT ODOMETRYSTORAGEWIDGETS	//storage widgets
{
	QLabel receivelabel;
	QLabel receivestatus;
	QLineEdit filename;
	QLineEdit receiveframenum;
	QLineEdit receiveinfo;
};

#endif
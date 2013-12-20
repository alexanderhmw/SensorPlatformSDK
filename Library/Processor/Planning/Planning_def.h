#ifndef PLANNING_DEF_H
#define PLANNING_DEF_H

#include <QtCore/qglobal.h>
#include <URG\urg_def.h>
#include <UDPReceiver\UDPReceiver_def.h>
#include <GLViewer\glviewer.h>

struct Q_DECL_EXPORT LPPOINT2D
{
	double x;
	double y;
};

struct Q_DECL_EXPORT POSNODE	//UDPReceiver data
{
	long timestamp;
	double rx,ry,rz;
	double sx,sy,sz;
};

struct Q_DECL_EXPORT URGPARAMS
{
	int urgresolution;
	int urgangle;
};

struct Q_DECL_EXPORT GPSPARAMS
{
	double gpsheadang;
	double gpsreaddis;
};

struct Q_DECL_EXPORT PLANNINGFUSIONPARAMS	//fusion parameters
{
	QVector<QString> supportclasstype;
	QVector<QVector<QString>> supportname;

	QString offlinetrajfilename;
	QVector<TRAJNODE> offlinetraj;
	
	QVector<URGPARAMS> urgparams;
	GPSPARAMS gpsparams;
	 
	 double safetyzone;
};

struct Q_DECL_EXPORT TRAJNODE
{
	double x;
	double y;
	double yaw;
};

struct Q_DECL_EXPORT PLANNINGFUSIONOUTPUTDATA	//
{
	QVector<TRAJNODE> trackingtraj;
};

struct Q_DECL_EXPORT PLANNINGFUSIONWIDGETS	//fusion widgets
{
	GLviewer glviewer;
	QVector<LPPOINT2D> lppoints;
	QVector<POSNODE> pos;
};

#endif
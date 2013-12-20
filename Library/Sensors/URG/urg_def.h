#ifndef URG_DEF_H
#define URG_DEF_H

#include <QtCore/qglobal.h>
#include <urglib\urg_sensor.h>
#include <urglib\urg_utils.h>
#include<qdatetime.h>
#include<qstring.h>
#include<qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>

struct Q_DECL_EXPORT URGSENSORPARAMS	//sensor parameters
{
	urg_t urg;
	urg_connection_type_t connection_type;
	QString device_or_address;
	long baudreate_or_port;
	urg_measurement_type_t measurement_type;
	int skip_scan;
	int first_step;
	int last_step;
	int skip_step;
};

struct Q_DECL_EXPORT URGSENSORDATA	//sensor data
{
	long timestamp;
	QTime qtimestamp;
	int datasize;
	short * data;
};

struct Q_DECL_EXPORT URGSENSORWIDGETS	//sensor widgets
{
	QLabel label;
	QLabel status;
	QLineEdit framenum;
	QLineEdit info;
};

struct Q_DECL_EXPORT URGSTORAGEPARAMS	//storage parameters
{
	QFile file;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT URGSTORAGEWIDGETS	//storage widgets
{
	QLabel label;
	QLabel status;
	QLineEdit filename;
	QLineEdit framenum;
	QLineEdit info;
};

#endif
#ifndef URG_DEF_H
#define URG_DEF_H

#include"urg_global.h"
#include".\Resources\urg\urg_sensor.h"
#include".\Resources\urg\urg_utils.h"
#include<qdatetime.h>
#include<qstring.h>
#include<qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>

struct URG_EXPORT URGPARAMS
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

struct URG_EXPORT URGDATA
{
	long timestamp;
	QTime qtimestamp;
	int datasize;
	short * data;
};

struct URG_EXPORT URGSTORAGEPARAMS
{
	QFile file;
	QString storagepath;
	QString extension;
};

struct URG_EXPORT URGWIDGETS
{
	QLabel label;
	QLabel status;
	QLineEdit framenum;
	QLineEdit info;
};

#endif
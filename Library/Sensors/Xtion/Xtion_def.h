#ifndef XTION_DEF_H
#define XTION_DEF_H

#include <QtCore/qglobal.h>
#include<qdatetime.h>
#include<qstring.h>
#include<qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include<OpenNI.h>
#include<opencv2\opencv.hpp>

struct Q_DECL_EXPORT XTIONSENSORPARAMS	//sensor parameters
{
	openni::Device device;
	openni::VideoStream depth;
	openni::VideoStream color;
	int resolutionx;
	int resolutiony;
	int fps;
};

struct Q_DECL_EXPORT XTIONSENSORDATA	//sensor data
{
	QTime depthtimestamp;
	cv::Mat depth;
	QTime colortimestamp;
	cv::Mat color;
};

struct Q_DECL_EXPORT XTIONSENSORWIDGETS	//sensor widgets
{
	QLabel label;
	QLabel status;
	QLineEdit framenum;
	QLineEdit info;
	QCheckBox showdepth;
	QCheckBox showcolor;
	QLabel depthimage;
	QLabel colorimage;
};

struct Q_DECL_EXPORT XTIONSTORAGEPARAMS	//storage parameters
{
	QFile timestampwriter;
	cv::VideoWriter depthwriter;
	QString depthvideofilename;
	cv::VideoWriter colorwriter;
	QString colorvideofilename;
	double fps;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT XTIONSTORAGEWIDGETS	//storage widgets
{
	QLabel label;
	QLabel status;
	QLineEdit depthfilename;
	QLineEdit colorfilename;
	QLineEdit framenum;
	QLineEdit info;
};

#endif
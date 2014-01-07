#ifndef POINTGREYFLEA2_DEF_H
#define POINTGREYFLEA2_DEF_H

#include <QtCore/qglobal.h>
#include<qdatetime.h>
#include<qstring.h>
#include<qfile.h>
#include<qtextstream.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>
#include <FlyCapture2.h>
#include <opencv2\opencv.hpp>

struct Q_DECL_EXPORT POINTGREYFLEA2SENSORPARAMS	//sensor parameters
{
	FlyCapture2::Camera * camera;
	FlyCapture2::VideoMode videomode;
	FlyCapture2::FrameRate framerate;
	FlyCapture2::PixelFormat pixelformat;
	int resolutionx;
	int resolutiony;
};

struct Q_DECL_EXPORT POINTGREYFLEA2SENSORDATA	//sensor data
{
	QTime timestamp;
	cv::Mat image;
};

struct Q_DECL_EXPORT POINTGREYFLEA2SENSORWIDGETS	//sensor widgets
{
	QLabel label;
	QLabel status;
	QLineEdit framenum;
	QLineEdit info;
	QCheckBox showimage;
	QLabel image;
};

struct Q_DECL_EXPORT POINTGREYFLEA2STORAGEPARAMS	//storage parameters
{
	QFile timestampwriter;
	cv::VideoWriter imagewriter;
	QString videofilename;
	double fps;
	QString storagepath;
	QString extension;
};

struct Q_DECL_EXPORT POINTGREYFLEA2STORAGEWIDGETS	//storage widgets
{
	QLabel label;
	QLabel status;
	QLineEdit imagefilename;
	QLineEdit framenum;
	QLineEdit info;
};

struct Q_DECL_EXPORT POINTGREYFLEA2SIMULATORPARAMS	//processor parameters
{
	cv::VideoCapture videoCap;
	QFile logFile;
	QString datafile;
	QTextStream textstream;
};

struct Q_DECL_EXPORT POINTGREYFLEA2SIMULATORDATA	//processor data
{
	QTime timestamp;
	cv::Mat image;
};

#endif
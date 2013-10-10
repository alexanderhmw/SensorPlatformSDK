#ifndef USBCAMERA_DEF_H
#define USBCAMERA_DEF_H

#include "usbcamera_global.h"
#include <opencv2\opencv.hpp>
#include <qdatetime.h>
#include <qfile.h>
#include <qboxlayout.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qcheckbox.h>

struct USBCAMERA_EXPORT USBCAMERAPARAMS
{
	cv::VideoCapture cap;
	int deviceid;
	int width;
	int height;
};

struct USBCAMERA_EXPORT USBCAMERADATA
{
	QTime qtimestamp;
	cv::Mat image;
};

struct USBCAMERA_EXPORT USBCAMERASTORAGEPARAMS
{
	QFile timestampwriter;
	cv::VideoWriter writer;
	QString videofilename;
	double fps;
	QString storagepath;
	QString extension;
};

struct USBCAMERA_EXPORT USBCAMERAWIDGETS
{
	QLabel label;
	QLabel status;
	QLineEdit framenum;
	QLineEdit info;
	QCheckBox showimage;
	QLabel image;
};

struct USBCAMERA_EXPORT USBCAMERASTORAGEWIDGETS
{
	QLabel label;
	QLabel status;
	QLineEdit filename;
	QLineEdit framenum;
	QLineEdit info;
};

#endif
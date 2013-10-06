#ifndef USBCAMERA_DEF_H
#define USBCAMERA_DEF_H

#include "usbcamera_global.h"
#include <opencv2\opencv.hpp>
#include <qdatetime.h>

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

#endif
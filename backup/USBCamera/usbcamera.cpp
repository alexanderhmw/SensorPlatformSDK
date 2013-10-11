#include "usbcamera.h"
#include<FuncLibrary\nodebasefunc.h>

#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

void setNodeClass(QString & nodeclass)
{
	nodeclass=QString("USBCamera");
}
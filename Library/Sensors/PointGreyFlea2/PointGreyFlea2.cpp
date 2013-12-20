#include "PointGreyFlea2.h"
#include<FuncLibrary\nodebasefunc.h>

//Add static library below (#pragma comment(lib,"XXX.lib")
#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")
#pragma comment(lib, "FlyCapture2.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

void setNodeClass(QString & nodeclass)	//Set the node class
{
	nodeclass=QString("PointGreyFlea2");
}


#include "urg.h"
#include<FuncLibrary\nodebasefunc.h>

#pragma comment(lib, "urgd.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

void setNodeClass(QString & nodeclass)
{
	nodeclass=QString("URG");
}
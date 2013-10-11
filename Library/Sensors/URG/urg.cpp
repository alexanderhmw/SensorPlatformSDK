#include "URG.h"
#include<FuncLibrary\nodebasefunc.h>

//Add static library below (#pragma comment(lib,"XXX.lib")

#pragma comment(lib, "urglib.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "XMLParamsLoader.lib")

void setNodeClass(QString & nodeclass)	//Set the node class
{
	nodeclass=QString("URG");
}
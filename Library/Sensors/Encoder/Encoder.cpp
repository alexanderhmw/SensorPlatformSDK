#include "Encoder.h"
#include<FuncLibrary\nodebasefunc.h>

//Add static library below (#pragma comment(lib,"XXX.lib")
#pragma comment(lib, "XMLParamsLoader.lib")
#pragma comment(lib, "serialportlib.lib")

void setNodeClass(QString & nodeclass)	//Set the node class
{
	nodeclass=QString("Encoder");
}


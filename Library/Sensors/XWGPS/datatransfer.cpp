#include "datatransfer.h"

#define PI 3.1415926535897932384626433832795

void dataTransfer(int startid, int endid, XWGPSCOMMUNICATORRECEIVEDATA * XWGPSreceivedata)
{
	char N,E,Valid;
	int dumy;
	bool gpsOn=1;
	double	gpstime,heading,pitch,roll;
	double	lat=0, lon=0,altitude=0;
	double	lbh[3], xyz[3], dat[4];

	XWGPSreceivedata->qtimestamp=QTime::currentTime();
	QByteArray datagram=XWGPSreceivedata->datagram.mid(startid+sizeof(HeaderGLL)-1,endid-(startid+sizeof(HeaderGLL))-5);
	sscanf(datagram.data(),"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&dumy,&gpstime,&heading,&pitch,&roll,&lat,&lon,&altitude);
	lbh[0]=lat;
	lbh[1]=lon;
	lbh[2]=altitude;
	CCoordinateConvertion	ctest;
	SetCoordinateParameters(_BEIJINGLOCAL);
	ctest.GPS84LBH_LocalXYZ (lbh, xyz);
	XWGPSreceivedata->gpstime=gpstime;
	XWGPSreceivedata->rx=pitch*PI/180.0;
	XWGPSreceivedata->ry=roll*PI/180.0;
	XWGPSreceivedata->rz=-heading*PI/180.0;
	XWGPSreceivedata->sy=xyz[0];
	XWGPSreceivedata->sx=xyz[1];
	XWGPSreceivedata->sz=xyz[2];
	XWGPSreceivedata->gpsstatus=gpsOn?1:0;
}
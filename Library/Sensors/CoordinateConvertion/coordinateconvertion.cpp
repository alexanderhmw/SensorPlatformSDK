// CoordinateConvertion.cpp: implementation of the CCoordinateConvertion class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "stb_Time_cut.h"
#include "CoordinateConvertion.h"
#include <math.h>
#include <stdio.h>
#define  PI 3.1415926535897932
#define  ArcDegree (PI / 180.0)
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//typedef enum {
//	_BEJING54, _BEIJINGLOCAL, _TOKYO9K, _NAGOYA7K
//} COORDINATESYSTEMS;

double	DEF_A1=6378137.0;
double	DEF_B1=6356752.3;

double	DEF_A2=6377397.155;
double	DEF_B2=6356078.963;
double	DEF_DX=-147.54;
double	DEF_DY=507.26;
double	DEF_DZ=680.47;
double	DEF_B0=40.0;
double	DEF_L0=116.0;

void SetCoordinateParameters (COORDINATESYSTEMS coordsys)
{
	switch (coordsys) {
	case _BEIJING54:
		DEF_A2=6378245.0;
		DEF_B2=6356863.0187730473;
		DEF_DX=-16.492;
		DEF_DY=156.410;
		DEF_DZ=80.118;
		DEF_B0=40.0;
		DEF_L0=116.0;
		break;
	case _BEIJINGLOCAL:
		DEF_A2=6377397.155;
		DEF_B2=6356078.963;
		DEF_DX=-147.54;
		DEF_DY=507.26;
		DEF_DZ=680.47;
		DEF_B0=40.0;
		DEF_L0=116.0;
		break;
	case _TOKYO9K:
		DEF_A2=6377397.155;
		DEF_B2=6356078.963;
		DEF_DX=-147.54;				//WGS84-->Tokyo-146.414
		DEF_DY=507.26;				//WGS84-->Tokyo 507.337
		DEF_DZ=680.47;				//WGS84-->Tokyo 680.507
		DEF_B0=36.0;				//true
		DEF_L0=(139.0+50.0/60.0);	//true
		break;
	case _NAGOYA7K:
		DEF_A2=6377397.155;
		DEF_B2=6356078.963;
		DEF_DX=-147.54;				//WGS84-->Tokyo-146.414
		DEF_DY=507.26;				//WGS84-->Tokyo 507.337
		DEF_DZ=680.47;				//WGS84-->Tokyo 680.507
		DEF_B0=36.0;				//true
		DEF_L0=(137.0+10.0/60.0);	//true
		break;
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoordinateConvertion::CCoordinateConvertion()
{

}

CCoordinateConvertion::~CCoordinateConvertion()
{

}

int CCoordinateConvertion::LocalLBH_XYZ(double *lbh, double *xyz)
{
	double a, b, e, e1, B;
	double B0, L0; //(緯度=36-0-0.00,  経度=139-50-0.00)
	double N, t, l, r, m, n, V;
	double X0;
	double East, North, L, X, f;
	double a0, a2, a4, a6, a8;

	B0  = DEF_B0;  L0 = DEF_L0; //原点
	a = DEF_A2; 	b = DEF_B2; 
	e = sqrt((a*a - b*b) / (a*a));  e1 = sqrt((a*a - b*b) / (b*b));
	B0 *= PI/180.0; 
	B = lbh[0] * PI/180.0;         //緯度
	L = lbh[1];                    //経度
	l = L - L0;	l *= PI/180.0;
	t = tan(B);
	r = e*cos(B)/sqrt(1-e*e); 
	m = l * cos(B);
	n = e * sin(B);
	V = sqrt(1.0 + r*r);
	N = a / sqrt(1.0 - n*n);
	East = N*m*(1.0 + m*m*(1.0 - t*t + r*r*r + 
		              m*m*(5.0 + 14.0*r*r - t*t*(18.0 - t*t + 58.0*r*r))/20.0)/6.0
				);
	North = N*t*m*m*(1.0 + m*m*(5.0 - t*t + r*r*(9.0 + 4.0*r*r) + 
		                   m*m*(61.0 - t*t * (58.0 - t*t + 330.0*r*r) + 270.0*r*r)/30.0)/12.0)/2.0;
	
	f = (a - b) / a;	n = f / (2.0 - f);
	a0 = 1.0 + n*n * (1.0 + n*n / 16.0) / 4.0;  a2 = 1.5 * n * (1.0 - n*n/8);
	a4 = 15.0 * n*n * (1.0 - n*n / 4.0) / 16.0;
	a6 = 35.0 * n*n*n / 48.0;   a8 = 315.0 * n*n*n*n / 512.0;
	X = a * (a0*B - a2*sin(2.0*B) + a4*sin(4.0*B) - a6*sin(6.0*B) + a8*sin(8.0*B)) / (1 + n);
	B = B0;
	X0 = a * (a0*B - a2*sin(2.0*B) + a4*sin(4.0*B) - a6*sin(6.0*B) + a8*sin(8.0*B)) / (1 + n);
	
	North += X - X0;

	xyz[0] = 0.9999 * North; 
	xyz[1] = 0.9999 * East;
	xyz[2] = lbh[2];
	
	return(0);
}

int CCoordinateConvertion::LocalXYZ_LBH(double *xyz, double *lbh)
{
	double a, b, e, e1, Bf, B, V;
	double X0, Y;
	double N, t, l, r;
	double B0, L0;
	double f, n, a0;

	B0  = DEF_B0;  L0 = DEF_L0;
	B0 *= PI/180.0;  L0 *= PI/180.0;
	a = DEF_A2; b = DEF_B2; 
	e = sqrt((a*a - b*b) / (a*a));  e1 = sqrt((a*a - b*b) / (b*b));
	
	X0 = xyz[0] / 0.9999;	//North
	Y = xyz[1] / 0.9999;     //East
	
	B = B0;	f = (a - b) / a; n = f / (2.0 - f);
	a0 = 1.0 + n*n * (1.0 + n*n / 16.0) / 4.0;  

	Bf = X0 * (1.0 + n) / a / a0;
	while (fabs(B - Bf) > 0.00000000000005) { B = Bf;
		//if (X0 < 0.0) Bf = B0 - Bf;
		//else Bf = B0 + Bf;
	    Bf = B0 + Bf;
		t = tan(Bf);	r = e1 * cos(Bf);		V = sqrt(1.0 + r*r);
		N = a / sqrt(1.0 - e*e * sin(Bf) * sin(Bf));
		Bf = V*V*X0*(1.0 - r*r*X0*(3.0*t + X0*(t - 1.0 - r*r + 5.0 * r * t*t)/N)/N/2.0) / N;
	}
	//if (X0 < 0.0) Bf = B0 - Bf;
	//else Bf = B0 + Bf;
	
	Bf = B0 + Bf;
	t = tan(Bf);
	r = e1 * cos(Bf);
	V = sqrt(1.0 + r*r);
	N = a / sqrt(1.0 - e*e * sin(Bf) * sin(Bf));
	Y /= N;	
	l = Y*(1.0 - Y*Y*(1.0+2*t*t+r*r - Y*Y*(5.0+4.0*t*t*(7.0+6.0*t*t+2.0*r*r)+6.0*r*r)/20.0)/6.0)/cos(Bf);
	B = - V*V*t*Y*Y*(1.0 - Y*Y*(5.0+3.0*t*t+6.0*r*r-6.0*r*r*t*t - 3.0*r*r*r*r - 9.0 *t*t*r*r*r*r -
		                   Y*Y*(61.0+45.0*t*t*(2.0+t*t))/30.0)/12.0) / 2.0;
	
	B = Bf + B;
	lbh[0] = B*180.0/PI;
//	if (X0 < 0.0) lbh[0] += 0.00001929046153;
//	else lbh[0] += 0.00000170046153;

	lbh[1] = (l+L0) * 180.0/PI;
	lbh[2] = xyz[2];

	return(0);
}

int CCoordinateConvertion::LBH_XYZ(double *lbh, double *xyz, double a, double b)
{
	double e, N;

	e = (a*a - b*b) / (a*a);
	N = a / sqrt(1.0 - e * sin(lbh[0])*sin(lbh[0]));

	xyz[0] = (N + lbh[2]) * cos(lbh[0]) * cos(lbh[1]);
	xyz[1] = (N + lbh[2]) * cos(lbh[0]) * sin(lbh[1]);
	xyz[2] = (N * (1.0 - e) + lbh[2]) * sin(lbh[0]);
	return(0);
}

int CCoordinateConvertion::XYZ_LBH(double *xyz, double *lbh, double a, double b)
{
	double e, N, B0, s, r;

	e = (a*a - b*b) / (a*a);
	B0 = DEF_B0 * PI / 180.0;
	r = sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1]);
	s = xyz[2] / r;
	//lbh[0] = atan(s / (1.0 - e*e)); 
	lbh[0] = atan(s / (1.0 - e));
	while (fabs(lbh[0] - B0) > 0.000000001) {
		B0 = lbh[0];   N = a / sqrt(1.0 - e * sin(lbh[0])*sin(lbh[0]));
		lbh[0] = atan(s * (1.0 + e * N * sin(lbh[0]) / xyz[2]));
	}	
	lbh[1] = atan2(xyz[1], xyz[0]);
	N = a / sqrt(1.0 - e * sin(lbh[0]) * sin(lbh[0]));
	lbh[2] = r / cos(lbh[0]) - N;
	return(0);
}

int CCoordinateConvertion::WGS84_Local(double *WGS84)
{
	double a1 = 6378137.0, b1 = 6356752.3;  //For WGS84 (m)
	double a2 = 6377397.155, b2 = 6356078.963; //For 日本測地座標系
	double dx =  147.54; //WGS84-->Tokyo-146.414
	double dy = -507.26; //WGS84-->Tokyo 507.337
	double dz = -680.47; //WGS84-->Tokyo 680.507
	double xyz[3];
//	xyz = new double[3];

	LBH_XYZ(WGS84, xyz, a1, b1);
	xyz[0] += dx;   xyz[1] += dy;  xyz[2] += dz;
	XYZ_LBH(xyz, WGS84, a2, b2);
//	delete []xyz;
	return(0);
}

int CCoordinateConvertion::Local_WGS84(double *Tokyo)
{
	double a1 = 6377397.155, b1 = 6356078.963; //For 日本測地座標系
	double a2 = 6378137.0, b2 = 6356752.3;     //For WGS84 (m)
	double dx = -147.54;  //Tokyo-->WGS84 (-146.414)
	double dy =  507.26;  //Tokyo-->WGS84 ( 507.337)
	double dz =  680.47;  //Tokyo-->WGS84 ( 680.507)
	double xyz[3];
//	xyz = new double[3];

	LBH_XYZ(Tokyo, xyz, a1, b1);
	xyz[0] += dx;   xyz[1] += dy;  xyz[2] += dz;
	XYZ_LBH(xyz, Tokyo, a2, b2);
//	delete []xyz;
	return(0);
}

int CCoordinateConvertion::CenterXYZ_TangentPlaneXYZ(double *lbh0, double *xyz0, double *xyz)
{
	//地球中心直角座標 ----> 切平面直角座標
	//lbh0[0]	//地上基準点０の緯度
	//lbh0[1]	//地上基準点０の経度
	//lbh0[2]	//地上基準点０の標高
	//xyz0[0]	//地上基準点０の地球中心直角座標X
	//xyz0[1]	//地上基準点０の地球中心直角座標Y
	//xyz0[2]	//地上基準点０の地球中心直角座標Z
	//xyz[0]	//地上点の地球中心直角座標X
	//xyz[1]	//地上点の地球中心直角座標Y
	//xyz[2]	//地上点の地球中心直角座標Z
	double	a1, a2, a3, b1, b2, b3, c1, c2, c3;
	double	dx, dy, dz;
	dx = xyz[0] - xyz0[0]; dy = xyz[1] - xyz0[1]; dz = xyz[2] - xyz0[2]; 
	a1 = -sin(lbh0[1]); a2 = -cos(lbh0[1]) * sin(lbh0[0]); a3 = cos(lbh0[1]) * cos(lbh0[0]);
	b1 = cos(lbh0[1]); b2 = -sin(lbh0[1]) * sin(lbh0[0]); b3 = sin(lbh0[1]) * cos(lbh0[0]);
	c1 = 0.0; c2 = cos(lbh0[0]); c3 = sin(lbh0[0]);
	xyz[0] = a1 * dx + b1 * dy + c1 * dz;
	xyz[1] = a2 * dx + b2 * dy + c2 * dz;
	xyz[2] = a3 * dx + b3 * dy + c3 * dz;
	return (0);
}

int CCoordinateConvertion::TangentPlaneXYZ_CenterXYZ(double *lbh0, double *xyz0, double *xyz)
{
	//切平面直角座標 ----> 地球中心直角座標
	//lbh0[0]	//地上基準点０の緯度
	//lbh0[1]	//地上基準点０の経度
	//lbh0[2]	//地上基準点０の標高
	//xyz0[0]	//地上基準点０の地球中心直角座標X
	//xyz0[1]	//地上基準点０の地球中心直角座標Y
	//xyz0[2]	//地上基準点０の地球中心直角座標Z
	//xyz[0]	//地上点の切平面直角座標X
	//xyz[1]	//地上点の切平面直角座標Y
	//xyz[2]	//地上点の切平面直角座標Z
	double	a1, a2, a3, b1, b2, b3, c1, c2, c3;
	double	dx, dy, dz;
	
	a1 = -sin(lbh0[1]); a2 = -cos(lbh0[1]) * sin(lbh0[0]); a3 = cos(lbh0[1]) * cos(lbh0[0]);
	b1 = cos(lbh0[1]); b2 = -sin(lbh0[1]) * sin(lbh0[0]); b3 = sin(lbh0[1]) * cos(lbh0[0]);
	c1 = 0.0; c2 = cos(lbh0[0]); c3 = sin(lbh0[0]);
	dx = a1 * xyz[0] + a2 * xyz[1] + a3 * xyz[2] + xyz0[0];
	dy = b1 * xyz[0] + b2 * xyz[1] + b3 * xyz[2] + xyz0[1];
	dz = c1 * xyz[0] + c2 * xyz[1] + c3 * xyz[2] + xyz0[2];

	xyz[0] = dx; xyz[1] = dy; xyz[2] = dz;
	return (0);
}

void CCoordinateConvertion::GPS84LBH_LocalXYZ(double *lbh, double *XYZ)
{
	//#############################
	//Input: GPS 計測データ
	//①lbh[0] (緯度、単位：度)
	//②lbh[1] (経度、単位：度)
	//③lbh[2] (標高、単位：米)
	//#############################

	//#############################
	//Output: Tokyo 直角座標
	//①XYZ[0] (East、単位：米)
	//②XYZ[1] (North、単位：米)
	//③XYZ[2] (標高、単位：米)
	//#############################
	lbh[0] *= ArcDegree;
	lbh[1] *= ArcDegree;
	WGS84_Local(lbh);

	lbh[0] /= ArcDegree; lbh[1] /= ArcDegree;
	LocalLBH_XYZ(lbh, XYZ);
}

void CCoordinateConvertion::LocalXYZ_GPS84LBH(double *XYZ, double *lbh)
{
	//#############################
	//Input: GPS 計測データ
	//①lbh[0] (緯度、単位：度)
	//②lbh[1] (経度、単位：度)
	//③lbh[2] (標高、単位：米)
	//#############################

	//#############################
	//Output: Tokyo 直角座標
	//①XYZ[0] (East、単位：米)
	//②XYZ[1] (North、単位：米)
	//③XYZ[2] (標高、単位：米)
	//#############################
	LocalXYZ_LBH(XYZ, lbh);
	lbh[0] *= ArcDegree; lbh[1] *= ArcDegree;

	Local_WGS84(lbh);
	lbh[0] /= ArcDegree;
	lbh[1] /= ArcDegree;

#ifdef _BEJING54
	lbh[0] -= 0.00059;
#endif

}


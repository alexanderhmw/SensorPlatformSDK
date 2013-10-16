// CoordinateConvertion.h: interface for the CCoordinateConvertion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COORDINATECONVERTION_H__E4FD82EB_782B_474C_A802_5BE18D7E973A__INCLUDED_)
#define AFX_COORDINATECONVERTION_H__E4FD82EB_782B_474C_A802_5BE18D7E973A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {
	_BEIJING54, _BEIJINGLOCAL, _TOKYO9K, _NAGOYA7K
} COORDINATESYSTEMS;

void SetCoordinateParameters (COORDINATESYSTEMS coordsys);

class CCoordinateConvertion  
{
public:
	CCoordinateConvertion();
	virtual ~CCoordinateConvertion();

public:
	int		Local_WGS84(double *Local);
	int		WGS84_Local(double *WGS84);
	int		XYZ_LBH(double *xyz, double *lbh, double a, double b);
	int		LBH_XYZ(double *lbh, double *xyz, double a, double b);
	int		LocalXYZ_LBH(double *xyz, double *lbh);
	int		LocalLBH_XYZ(double *lbh, double *xyz);
	int		CenterXYZ_TangentPlaneXYZ(double *lbh0, double *xyz0, double *xyz);
	int		TangentPlaneXYZ_CenterXYZ(double *lbh0, double *xyz0, double *xyz);
	void	GPS84LBH_LocalXYZ(double *lbh, double *XYZ);
	void	LocalXYZ_GPS84LBH(double *XYZ, double *lbh);
};

#endif // !defined(AFX_COORDINATECONVERTION_H__E4FD82EB_782B_474C_A802_5BE18D7E973A__INCLUDED_)

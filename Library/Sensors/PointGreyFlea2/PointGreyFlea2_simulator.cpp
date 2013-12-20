//#include "PointGreyFlea2.h"
//#include<FuncLibrary\simulatorfunc.h>
//
//bool loadParamsSimulator(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
//{
//	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
//	if(PointGreyFlea2params==NULL)
//	{//case1: params point to a NULL
//		
//		PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
//	}
//	else
//	{//case2: PointGreyFlea2 point to a memory block
//		
//	}
//}
//
//void releaseParamsSimulator(void ** params)	//release params
//{
//	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
//	if(PointGreyFlea2params==NULL)
//	{//case1: params point to a NULL
//		
//		PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)(*params);
//	}
//	else
//	{//case2: PointGreyFlea2 point to a memory block
//		
//	}
//}
//
//bool openSimulator(void * params)
//{
//	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)params;
//}
//
//long loadData(void * params, void ** data)
//{
//	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)params;
//	POINTGREYFLEA2SIMULATORDATA * PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
//	if(PointGreyFlea2data==NULL)
//	{//case1: data point to a NULL
//		
//		PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
//	}
//	else
//	{//case2: PointGreyFlea2 point to a memory block
//		
//	}
//}
//
//bool closeSimulator(void * params)
//{
//	POINTGREYFLEA2SIMULATORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SIMULATORPARAMS *)params;
//}
//
//void dumpData(void ** data)
//{
//	POINTGREYFLEA2SIMULATORDATA * PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
//	if(PointGreyFlea2data==NULL)
//	{//case1: data point to a NULL
//		
//		PointGreyFlea2data=(POINTGREYFLEA2SIMULATORDATA *)(*data);
//	}
//	else
//	{//case2: PointGreyFlea2 point to a memory block
//		
//	}
//}
//
////==========================================================
////Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

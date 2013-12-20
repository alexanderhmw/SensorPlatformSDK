#include "CollisionDetect.h"

bool cordProjection(PLANNINGFUSIONPARAMS * params, POSNODE * posnode, URGSENSORDATA * urgdata, POSNODE & rearpos, QVector<LPPOINT2D> & lppoints)
{
	rearpos=*posnode;
	rearpos.sx+=(params->gpsreaddis)*cos(rearpos.rz+params->gpsheadang*PI/180.0);
	rearpos.sy+=(params->gpsreaddis)*sin(rearpos.rz+params->gpsheadang*PI/180.0);
	
	int range=params->urgresolution*params->urgangle+1;

	if(urgdata->datasize==range)
	{
		lppoints.resize(range);
		double theta=posnode.rz;
		double X=posnode.sx;
		double Y=posnode.sy;
		double step=resolution*0.25/PI;
		for(int i=0;i<range;i++)
		{
			if(urgdata->data[i]<10)
			{
				lppoints[i]
			}
			else
			{

			}
			TMP_POINT.x=X+cos(theta+i*step)*laserdata[i]/100.0;
			TMP_POINT.y=Y+sin(theta+i*step)*laserdata[i]/100.0;
			LP_Cord.push_back(TMP_POINT);
		}
		return 1;
	}
	else
	return 0;
}

//2 point dist
inline double dist(double x1, double y1, double x2, double y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1-y2);
}
bool  COLLISION_DETECT::Collision_detection(TRAJEC_SETS * Tmptrajectory)
{
	//now    deal with  point from LP_Cord  and tmptrajectory
	//the first 10-20points in the car itself   no need to calculate

	for(int j=0;j<LP_Cord.size();j++)
	{	
		for(int i=TRAJEC_POINTS/10;i<TRAJEC_POINTS;i++)
		{
			double distance=dist(Tmptrajectory->states[i].x,
				Tmptrajectory->states[i].y,LP_Cord.at(j).x,LP_Cord.at(j).y);
			if(distance<SafetyZone)	//collide exist
			{
				Tmptrajectory->feasible=false;
				Tmptrajectory->collide_num=i;
				return false;
			}
		}
	}
	return true;
}

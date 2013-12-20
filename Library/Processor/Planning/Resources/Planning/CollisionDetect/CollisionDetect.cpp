#include "CollisionDetect.h"
COLLISION_DETECT::COLLISION_DETECT()
{}
COLLISION_DETECT::~COLLISION_DETECT()
{}

bool COLLISION_DETECT::Cord_Projection(SLAM_DATA tmpPOS)
{
	double heading_x=cos(tmpPOS.ang.z+PI/2);
	double heading_y=sin(tmpPOS.ang.z+PI/2);
	tmpPOS.shv.x+=0.3*heading_x;
	tmpPOS.shv.y+=0.3*heading_y;
	
	if(laserdata.size()==Range)
	{
		LP_Cord.clear();
		double theta=tmpPOS.ang.z;
		double X=tmpPOS.shv.x;
		double Y=tmpPOS.shv.y;
		for(int i=0;i<Range;i++)
		{
			_POSS TMP_POINT;
			if(laserdata.at(i)<10)
				laserdata[i]=3000;
			TMP_POINT.x=X+cos(theta+double(i)*PI/(Range-1))*(double)(laserdata.at(i))/100;
			TMP_POINT.y=Y+sin(theta+double(i)*PI/(Range-1))*(double)(laserdata.at(i))/100;
			LP_Cord.push_back(TMP_POINT);
		}
		if(LP_Cord.size()==Range)  //almost 361 points
		return true;
		else
		return false;
	}
	else
	return false;
}

//2 point dist
inline double dist(double x1, double y1, double x2, double y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1-y2);
}
bool  COLLISION_DETECT::Collision_detection(trajectory_sets * Tmptrajectory)
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

#include "Planning.h"

/*********************************************
PLANNING and so-on...
Output: slamdata to _DATA_ALL
*********************************************/
#define forward_distance 3.0

//2 point dist
inline double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1-y2));
}
//find the nearest point
uint MINI_PLANNING::find_neibour_point(SLAM_DATA SlamData)
{	
	//QVector <int> Candidatepoints;
	//QVector <double> dist_buf;
	uint neibour_index;//=aim_point>1?aim_point-1:aim_point;
	double min_num=10000;
	double *buf;
	if(this->OFFLINE_Trajectory.size())
	{
		buf=(double *)malloc(OFFLINE_Trajectory.size()*sizeof(double));
		for(int i=loc_point>1?loc_point-1:loc_point;
			i<(loc_point+3000>=OFFLINE_Trajectory.size()?OFFLINE_Trajectory.size()-1:loc_point+3000);
			i+=3)
		//2013 10/10 修改  将求距离限制到loc点以及以后的200个点  与后面的判断对应
		{
			buf[i]=dist(OFFLINE_Trajectory.at(i).x,OFFLINE_Trajectory.at(i).y,
				SlamData.shv.x,SlamData.shv.y);
			buf[i+1]=buf[i];
			buf[i+2]=buf[i];
		}
		double min_d=buf[loc_point];
		double max_d=buf[loc_point];
		int kk=loc_point;
		for(int i=loc_point;
			i<(loc_point+3000>=OFFLINE_Trajectory.size()?OFFLINE_Trajectory.size()-1:loc_point+3000);
			i+=3)
		{	
			if(buf[i]<=min_d)
			{
				min_d=buf[i];
				kk=i;
			}
			else
				max_d=buf[i];
		}
			loc_point=kk;
	for(int i=loc_point+1;i<OFFLINE_Trajectory.size()-1;i+=3)
	{
		if(buf[i]>=forward_distance&&i>(loc_point+30))  //这里加入判断，必须是当前10个点以后 考虑到
		{
			neibour_index=i;
			break;
		}
	}
			//reseverd to find out the best point but not the closest point
			//because we may encouter the close loop situation
		free(buf);
	}
	//Candidatepoints.clear();
	return neibour_index;	//then we need to check which point to look at
}


//get output duty
#define WB 0.36		//0.36m wheel base		
//max duty 500 correspond to the angle 0.4049  
//likewise  tan(x)=0.36/0.84    which are the WB and turn Radius
#define COHER	1234.87	//	(500/0.4049)  500 max duty 
int MINI_PLANNING::get_angle(double sx, double sy,  // start rear axle point
				 double hx, double hy,           // heading vector
				 double tx, double ty) {         // target point

		 double len_heading_vector ;
		 double lx, ly ;
		 double len_lookahead_vector ;
		 double curvature ;
		 double cos_angle, sin_angle ;
		 double angle, steeringOutput ;
		 double a ;
		 double C ;
		 // normalize heading vector
		 len_heading_vector = dist(0, 0, hx, hy);
		 if (len_heading_vector == 0)
			 len_heading_vector += 1e-8;
		 hx /= len_heading_vector;
		 hy /= len_heading_vector;
		 // get look-ahead vector and normalize it
		 lx = tx - sx, ly = ty - sy;
		 len_lookahead_vector = dist(0, 0, lx, ly);
		 if (len_lookahead_vector == 0)
			 len_lookahead_vector += 1e-8;
		 lx /= len_lookahead_vector;
		 ly /= len_lookahead_vector;
		 // get sine of the angle between 2 vectors
		 cos_angle = lx * hx + ly * hy;
		 sin_angle = sqrt(1 - cos_angle*cos_angle);  // I am not sure about here
		 //left or right: left:-, right:+		
		 if ( hx <1E-8 && hx > -1E-8 ) {
			 if ( ( hy > 0 && lx < 0 ) || ( hy < 0  && lx > 0 ) )
				 sin_angle = -1*sin_angle ;
		 }
		 else {
			 a = hy / hx ;
			 if ( ( hx > 0 && (a*lx - ly) < 0 ) || ( hx < 0 && (a*lx - ly) > 0 ) )
				 sin_angle = -1*sin_angle ;
		 }
		 // get steering angle
		 curvature = 2 * sin_angle / len_lookahead_vector;
		 angle = atan(curvature * WB );
		//curvature>0  turn right
		//out put -500~500
		  steeringOutput= angle*COHER;
		 return (int)steeringOutput;
}

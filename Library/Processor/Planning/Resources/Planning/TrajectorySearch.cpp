#include "Planning.h"
#include<QtCore/qmath.h>
#define Trajectory_Interval	0.2
bool MINI_PLANNING::TrajectorySetsGenerate(trajec_state Pos1,trajec_state Pos2)
{
	//因为已经是朝向了，加pi/2变成左边，后面有一个-1的i次方
	//i从1开始的话轨迹第一条是从右边
	trajec_state AIM_POS[TRAJECTORY_SET_NUM-1];
	double D_x=cos(Pos2.theta+PI/2);
	double D_y=sin(Pos2.theta+PI/2);
	for(int i=1;i<TRAJECTORY_SET_NUM;i++)
	{
		AIM_POS[i-1].x=Pos2.x+qPow(-1,i)*qCeil((i+1)/2)*Trajectory_Interval*D_x;
		AIM_POS[i-1].y=Pos2.y+qPow(-1,i)*qCeil((i+1)/2)*Trajectory_Interval*D_y;
		AIM_POS[i-1].theta=Pos2.theta;
		bool flag=Path_Generate.Path_saving(Pos1,AIM_POS[i-1],i);
		if(flag==true)
		{//collision detect  
			NO_COLLISION.Collision_detection(&Path_Generate.traj_sets[i]);
			Path_Generate.traj_sets[i].dist_to_init_trajectory=i; 
			//find one ,then get it 
			if(Path_Generate.traj_sets[i].feasible==true)
				return true;
		}
	}
	return false;
}
#include "Planning.h"
#define After_point 100    //
static uint waitcounter; // 突然当前轨迹发生碰撞的时候 不需立即规划，等待一段时间再规划

MINI_PLANNING::MINI_PLANNING()
{
	aim_point=0;
	loc_point=0;
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
	timer->start(200);
}
MINI_PLANNING::~MINI_PLANNING()
{
	timer->stop();
	delete timer;
}

/*********************************************
PLANNING and so-on...
Output: slamdata to _DATA_ALL
*********************************************/
#define MIN_DIST  0.500
#define max_steer 500   //1000-2000  mid unknown
#define forward_distance 2.00
/*********************************************
DePack Object
Output:
*********************************************/
bool MINI_PLANNING::DepackLaser()
{
	if(LaserVector.size()>0){
			URGDATA  *tmpdata =(URGDATA *)LaserVector[0];
			uint tempn=tmpdata->datasize;
			NO_COLLISION.laserdata.clear(); //clear laser buf
			NO_COLLISION.laserdata.resize(tempn);
		  for(int i=0;i<tempn;i++)
			{	
				NO_COLLISION.laserdata[i]=tmpdata->data[i];
			}
			return true;
	}
	else
	return false;
}

/*********************************************
DePack POSDATA
Output:
*********************************************/
bool MINI_PLANNING::DepackPos()
{
	if(PosVector.size()>0){
			UDPDATA * tmpdata=(UDPDATA *)PosVector[0];
			uint tempn=tmpdata->datagram.size();
			char *data_rec= (char*)malloc(tempn);
			memcpy(data_rec,tmpdata->datagram.data(),tempn);
			if (data_rec[0]=='G'){	//gps data type
				SLAM_DATA PosData;
				memcpy(&PosData,&data_rec[2],sizeof(SLAM_DATA));
				double heading_x=cos(PosData.ang.z+PI/2);
				double heading_y=sin(PosData.ang.z+PI/2);
				PosData.shv.x-=0.3*heading_x;
				PosData.shv.y-=0.3*heading_y;
				//20131009yyf_start
				//	PosData.shv.x-=26372;
				//	PosData.shv.y-=-1414;
				//20131009yyf_end
				Realbuf.append(PosData);
				free(data_rec);
				return true;
			}
			else{
				free(data_rec);
			return false;
			}
		}
	else
		return false;
}

/*********************************************
Final Tracking_trajectory generation
Output:
*********************************************/
void MINI_PLANNING::FinalTrackingTrajectory(uint num)
{
	trajec_state	real_Pos;
	trajec_state  aim_Pos;
	uint new_num=num+After_point>OFFLINE_Trajectory.size()?
	OFFLINE_Trajectory.size():num+After_point;
	Tracking_lock.lockForWrite();
	Tracking_Trajectory.clear();
	if(Path_Generate.traj_sets[0].feasible==false)
	{
		for(int i=1;i<TRAJECTORY_SET_NUM;i++)
		{
			if(Path_Generate.traj_sets[i].feasible==true)
			{
				Path_Generate.traj_sets[i].feasible=false;// release it
				for(int j=0;j<TRAJEC_POINTS;j++)
				{
					_POSS TMP_P;
					TMP_P.x=Path_Generate.traj_sets[i].states[j].x;
					TMP_P.y=Path_Generate.traj_sets[i].states[j].y;
					TMP_P.yaw=Path_Generate.traj_sets[i].states[j].theta;
					Tracking_Trajectory.push_back(TMP_P);
				}
							//从终点再规划一次
				aim_Pos.x=OFFLINE_Trajectory.at(new_num-1).x;
				aim_Pos.y=OFFLINE_Trajectory.at(new_num-1).y;
				aim_Pos.theta=OFFLINE_Trajectory.at(new_num-1).yaw;
				real_Pos.x=Path_Generate.traj_sets[i].states[TRAJEC_POINTS-1].x;
				real_Pos.y=Path_Generate.traj_sets[i].states[TRAJEC_POINTS-1].y;
				real_Pos.theta=Path_Generate.traj_sets[i].states[TRAJEC_POINTS-1].theta;
				real_Pos.curvature=Path_Generate.traj_sets[i].states[TRAJEC_POINTS-1].curvature;
				bool flag=Path_Generate.Path_Generating(real_Pos,aim_Pos);
				if(flag)
				{
					for(int j=0;j<TRAJEC_POINTS;j++)
					{
						_POSS TMP_P;
						TMP_P.x=Path_Generate.state_data[j].x;
						TMP_P.y=Path_Generate.state_data[j].y;
						TMP_P.yaw=Path_Generate.state_data[j].theta;
						Tracking_Trajectory.push_back(TMP_P);
					}
				}
				else
				{  //生成一条直线的点
					for(int j=0;j<TRAJEC_POINTS;j++)
					{
						_POSS TMP_P;
						TMP_P.x=real_Pos.x+(aim_Pos.x-real_Pos.x)*j/TRAJEC_POINTS;
						TMP_P.y=real_Pos.y+(aim_Pos.y-real_Pos.y)*j/TRAJEC_POINTS;
						TMP_P.yaw=aim_Pos.theta;
						Tracking_Trajectory.push_back(TMP_P);
					}
				}
				break;
			}
		}
	}
		//第一条可行
	else
	{
		//只用第一条无障碍的轨迹进行tracking
		for(int j=0;j<TRAJEC_POINTS;j++)
		{
			_POSS TMP_P;
			TMP_P.x=Path_Generate.traj_sets[0].states[j].x;
			TMP_P.y=Path_Generate.traj_sets[0].states[j].y;
			TMP_P.yaw=Path_Generate.traj_sets[0].states[j].theta;
			Tracking_Trajectory.push_back(TMP_P);
		}
				//直接添加目标点以后的newnum个点
		for(int i=num+1;i<new_num;i++)
		{
			Tracking_Trajectory.push_back(OFFLINE_Trajectory.at(i));
			if(i>=OFFLINE_Trajectory.size()-1)
				break;
		}
	}
	//因为有新的tracking轨迹了，因此原来的那个轨迹需要修改，
	//因此需要将前面到aimnum+newnum的轨迹都替换掉， 用OFFLINE_Trajectory来替换
	if(Tracking_Trajectory.size())
	{
		OFFLINE_Trajectory.remove(0,new_num);//前面的所有数据丢掉
		for(int i=Tracking_Trajectory.size()-1;i>=0;i--)
		{
			OFFLINE_Trajectory.push_front(Tracking_Trajectory.at(i));
		}
	
	}
	//aim_point=0;
	loc_point=0;

	Tracking_lock.unlock();
	emit PlanOver((void *)&Tracking_Trajectory, &Tracking_lock);


}
/*********************************************
receive a SLAM data and begin to plan
Output:
*********************************************/
bool MINI_PLANNING::Planning()
{
	//first grab useful data
	//include SLAM data, Object data, 
	PosVector=PLANNINGDATA.grabDataRef(0, 1);    //get udp SLAM  only one
	LaserVector=PLANNINGDATA.grabDataRef(1, 1); 
	//get Pos data and objectdata
	DepackLaser();
	DepackPos();
	// get the recent gps data
	//at the same time make sure that there are data from laser

	if(Realbuf.size()&&NO_COLLISION.laserdata.size())
	{
		//emit VoiceSignal(0);
		//timer->stop();
		SLAM_DATA Pos_now=Realbuf.last();
		NO_COLLISION.Cord_Projection(Pos_now); //first project laser point
		double heading_x=cos(Pos_now.ang.z+PI/2);
		double heading_y=sin(Pos_now.ang.z+PI/2);
		trajec_state Real_Pos;
		Real_Pos.x=Pos_now.shv.x;
		Real_Pos.y=Pos_now.shv.y;
		Real_Pos.theta=Pos_now.ang.z+PI/2;
		Real_Pos.curvature=0;
		//now the Pos_now data become the real location 
		//of the back axle
		//find the coorespond point in the aim trajectory
		if(OFFLINE_Trajectory.size())
		{
			uint aim_num =	find_neibour_point(Pos_now);
			aim_point = aim_num;
			trajec_state Aim_Pos;
			Aim_Pos.x=OFFLINE_Trajectory.at(aim_num).x;
			Aim_Pos.y=OFFLINE_Trajectory.at(aim_num).y;
			Aim_Pos.theta=OFFLINE_Trajectory.at(aim_num).yaw;
			bool flag=Path_Generate.Path_saving(Real_Pos,Aim_Pos,0);
			//generate trajectory 0  if no collision ,use it
			if(flag)  //规划成功
			{//collision detect  
				NO_COLLISION.Collision_detection(&Path_Generate.traj_sets[0]);
				Path_Generate.traj_sets[0].dist_to_init_trajectory=0; //least dist
				
			}
			if(Path_Generate.traj_sets[0].feasible==false)
			{
				//timer->stop();
				// need to stop every time that there are collision
				emit StopSignal();
				
				//then begin to calculate or search.....
				//first try 6 trajectory
				if(waitcounter++>3)
				{
					waitcounter=0;
					timer->stop();
					emit StopSignal();
					if(TrajectorySetsGenerate(Real_Pos,Aim_Pos)==false)
					{	//not even one trajectory that satisfied
						//emit stop signal.
						//emit StopSignal();
						emit VoiceSignal(6);
						timer->start();
						return false;
					}
					else   //at last one in 6 can be used
					{
						emit VoiceSignal(1);
						FinalTrackingTrajectory(aim_num);
					}
					timer->start();
				}
			}
			//第一条可用  Path_Generate.traj_sets[0].feasible==true
			else
			{
				FinalTrackingTrajectory(aim_num);
				waitcounter=0;
			}
		}
	}

}

/*********************************************
Update timer
Output:
*********************************************/
static uint counter;
#define COUT 5
void MINI_PLANNING::Update()
{	
	Planning();
	//if(counter++>COUT)
	//{
		//counter=0;
		update_displaylist();
	//}
}


void MINI_PLANNING::planstart()
{
	aim_point=0;
	loc_point=0;
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
	timer->start(200);
}
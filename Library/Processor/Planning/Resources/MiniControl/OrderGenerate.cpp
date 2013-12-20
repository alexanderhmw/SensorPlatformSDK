#include "MiniControl.h"
                                                                                                                                                                                                                                                                                                              
/*********************************************                                                                                                                                                                                                                                                                                                                                                                                                                                                      bnbhjmmmmm
control and so-on...
Output: slamdata to _DATA_ALL
*********************************************/
static int output_steer=0;
#define MIN_DIST  0.500
#define max_steer 500   //1000-2000  mid unknown
#define forward_distance 1.50
static uint s_count=0;

//2 point dist
inline double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1-y2));
}
//find the nearest point
uint MINI_CONTROL::find_neibour_point(SLAM_DATA SlamData)
{	
	//QVector <int> Candidatepoints;
	//QVector <double> dist_buf;
	uint neibour_index=aim_point>1?aim_point-1:aim_point;
	double min_num=10000;
	double *buf;
	if(this->Tracking_trajectory.size())
	{
		buf=(double *)malloc(Tracking_trajectory.size()*sizeof(double));
		for(int i=loc_point>1?loc_point-1:loc_point;i<Tracking_trajectory.size()-1;i++)
		{
			buf[i]=dist(Tracking_trajectory.at(i).x,Tracking_trajectory.at(i).y,
				SlamData.shv.x,SlamData.shv.y);
		}
		double min_d=buf[loc_point];
		double max_d=buf[loc_point];
		int kk=loc_point;
		for(int i=loc_point;
			i<(loc_point+50>=Tracking_trajectory.size()?Tracking_trajectory.size()-1:loc_point+50);
			i++)
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
	for(int i=loc_point+1;i<Tracking_trajectory.size()-1;i++)
	{
		if(buf[i]>=forward_distance)
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
static int get_angle(double sx, double sy,  // start rear axle point
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

/*********************************************
receive a SLAM data and begin to track  a given
trajectory
Output:
*********************************************/
void MINI_CONTROL::Traj_Tracking()
{
	//tmpvector=test_course.grabDataRef(1, 1);    //get udp SLAM  only one
	if(tmpvector.size()>0&&Tracking_trajectory.size()){
			UDPDATA * slamdata=(UDPDATA *)tmpvector[0];
			int tempn=slamdata->datagram.size();
			char *data_rec= (char*)malloc(tempn);
			memcpy(data_rec,slamdata->datagram.data(),tempn);
			if (data_rec[0]=='G'){	//gps data type
				SLAM_DATA TmpData;
				memcpy(&TmpData,&data_rec[2],sizeof(SLAM_DATA));
				Realbuf.append(TmpData);
				double heading_x=cos(TmpData.ang.z+PI/2);
				double heading_y=sin(TmpData.ang.z+PI/2);
				TmpData.shv.x-=0.3*heading_x;
				TmpData.shv.y-=0.3*heading_y;
				//20131009yyf_start
				//	TmpData.shv.x-=26372;
				//	TmpData.shv.y-=-1414;
				//20131009yyf_end
				double car_locx=TmpData.shv.x;
				double car_locy=TmpData.shv.y;
				aim_point=find_neibour_point(TmpData);	
				double aim_x=Tracking_trajectory.at(aim_point).x;
				double aim_y=Tracking_trajectory.at(aim_point).y;
				output_steer=get_angle(car_locx,car_locy,heading_x,heading_y,aim_x,aim_y);
				_Default_VOLC.Steer=output_steer>max_steer?max_steer:output_steer;
				_Default_VOLC.Steer=output_steer<(0-max_steer)?(0-max_steer):output_steer;	
				emit send2s(_Default_VOLC.Steer,_Default_VOLC.Velocity);
			}
				this->Send_Order(steer);
			
		}
}

void MINI_CONTROL::receivelocalization(void *dataptr, QReadWriteLock *lockptr)
{
	if(Tracking_trajectory.size()){
	 UDPDATA * slamdata=(UDPDATA *)dataptr;
	 int tempn=slamdata->datagram.size();
			char *data_rec= (char*)malloc(tempn);
			memcpy(data_rec,slamdata->datagram.data(),tempn);
			if (data_rec[0]=='G'){	//gps data type
				SLAM_DATA TmpData;
				memcpy(&TmpData,&data_rec[2],sizeof(SLAM_DATA));
				Realbuf.append(TmpData);
				double heading_x=cos(TmpData.ang.z+PI/2);
				double heading_y=sin(TmpData.ang.z+PI/2);
				TmpData.shv.x-=0.3*heading_x;
				TmpData.shv.y-=0.3*heading_y;
				//20131009yyf_start
				//	TmpData.shv.x-=26372;
				//	TmpData.shv.y-=-1414;
				//20131009yyf_end
				double car_locx=TmpData.shv.x;
				double car_locy=TmpData.shv.y;
				aim_point=find_neibour_point(TmpData);	
				double aim_x=Tracking_trajectory.at(aim_point).x;
				double aim_y=Tracking_trajectory.at(aim_point).y;
				output_steer=get_angle(car_locx,car_locy,heading_x,heading_y,aim_x,aim_y);
				_Default_VOLC.Steer=output_steer>max_steer?max_steer:output_steer;
				_Default_VOLC.Steer=output_steer<(0-max_steer)?(0-max_steer):output_steer;	
				emit send2s(_Default_VOLC.Steer,_Default_VOLC.Velocity);
			}
			if(s_count++>1){
				s_count=0;
				this->Send_Order(steer);
			}
			else
			{
				if(aim_point>170)
				{
					_Default_VOLC.Velocity=10;
					Tracking_trajectory.clear();
					this->Send_Order(speed);
				}
			}
	}
}


/*********************************************
receive a single line..
Output:
*********************************************/
void MINI_CONTROL::Rec_Single_Line()
{
			double car_locx=0;
		double car_locy=0;
		double heading_x=cos(PI/2);
		double heading_y=sin(PI/2);
		
		//这里加几个条件  比如太偏左或者太偏右
	//	tmpvector=test_course.grabDataRef(2, 1);    //get udp order  only one
		if(tmpvector.size()>0){
			UDPDATA * orderdata=(UDPDATA *)tmpvector[0];
			char *data_rec= (char*)malloc(orderdata->datagram.size());
			memcpy(data_rec,orderdata->datagram.data(),orderdata->datagram.size());
			if (data_rec[0]=='C'&&data_rec[1]=='L'){
				memcpy(&aaa,&data_rec[2],sizeof(aaa));
				memcpy(&bbb,&data_rec[2+sizeof(aaa)],sizeof(bbb));
				memcpy(&ccc,&data_rec[2+sizeof(aaa)*2],sizeof(ccc));	
				free(data_rec);
				
				double aim_x=(ccc-forward_distance*bbb)/aaa;
				double aim_y=forward_distance;
				//get output	   //2m forward
				output_steer=3*get_angle(car_locx,car_locy,heading_x,heading_y,aim_x,aim_y);
				_Default_VOLC.Steer=output_steer>max_steer?max_steer:output_steer;
				_Default_VOLC.Steer=output_steer<(0-max_steer)?(0-max_steer):output_steer;		
			}
			else if(data_rec[0]=='O'&&data_rec[1]=='L'){
				int kkk;
				memcpy(&kkk,&data_rec[2],sizeof(kkk));
				output_steer=kkk;
				_Default_VOLC.Steer=output_steer>max_steer?max_steer:output_steer;
				_Default_VOLC.Steer=output_steer<(0-max_steer)?(0-max_steer):output_steer;		
			
			}
		}
}
/*********************************************
update displaylist
Output:
*********************************************/
void MINI_CONTROL::update_displaylist()
{
	glNewList(SLAM_LIST.listid,GL_COMPILE);
	glColor3f(1.0,1.0,1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	for(int i=1;i<Tracking_trajectory.size()-1;i++)
	{	if(i<loc_point)
		glColor3f(1.0,1.0,1.0);
		else
		glColor3f(0.0,0.0,1.0);
		glVertex3f(Tracking_trajectory.at(i-1).x,Tracking_trajectory.at(i-1).y,0);	
		glVertex3f(Tracking_trajectory.at(i).x,Tracking_trajectory.at(i).y,0);	
	}	
	if(Tracking_trajectory.size()&&Realbuf.size()){
		glColor3f(1.0,0.0,0.0);
		glVertex3f(Tracking_trajectory.at(aim_point).x,Tracking_trajectory.at(aim_point).y,0);	
		//glVertex3f(Tracking_trajectory.at(loc_point).x,Tracking_trajectory.at(loc_point).y,0);	
		glVertex3f(Realbuf.last().shv.x,Realbuf.last().shv.y,0);	
	}
	glColor3f(1.0,1.0,0.0);
	for(int i=1;i<Realbuf.size()-1;i++)
	{
		glVertex3f(Realbuf.at(i-1).shv.x,Realbuf.at(i-1).shv.y,0);	
		glVertex3f(Realbuf.at(i).shv.x,Realbuf.at(i).shv.y,0);	
	}
		glEnd();
	glEndList();
}
/*********************************************
Update timer
Output:
*********************************************/
static int counter;
#define COUT 5
void MINI_CONTROL::Update()
{	
//this is used in control course
	 //	Rec_Single_Line();
// this is used for tracking
	Traj_Tracking();
	//if(counter++>COUT)
	//{
		//counter=0;
	//	update_displaylist();
	//}
}
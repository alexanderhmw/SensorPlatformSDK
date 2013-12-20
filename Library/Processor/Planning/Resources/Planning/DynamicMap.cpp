#include "Planning.h"

/*********************************************
update displaylist 
and with the movement of the urgent, move the camera
Output:
*********************************************/
void MINI_PLANNING::update_displaylist()
{
	glNewList(SLAM_LIST.listid,GL_COMPILE);
	glColor3f(1.0,1.0,1.0);

	//show laser point
	
	glColor3f(0.1,0.7,0.1);
		//glPointSize(2);
		//glBegin(GL_POINTS);
	glLineWidth(2);
	glBegin(GL_LINES);
	for(int i=1;i<NO_COLLISION.LP_Cord.size();i++)
	{
		glColor3f(0.1,0.7,0.1);
		glVertex3f(NO_COLLISION.LP_Cord.at(i-1).x,NO_COLLISION.LP_Cord.at(i-1).y,0);	
		glVertex3f(NO_COLLISION.LP_Cord.at(i).x,NO_COLLISION.LP_Cord.at(i).y,0);	
		}
	glEnd();

		glPointSize(10);
		glBegin(GL_POINTS);
		if(OFFLINE_Trajectory.size()&&Realbuf.size()){
		glColor3f(1.0,0.0,0.0);
		glVertex3f(OFFLINE_Trajectory.at(aim_point).x,OFFLINE_Trajectory.at(aim_point).y,0);	
		glColor3f(0.0,1.0,0.0);
		glVertex3f(OFFLINE_Trajectory.at(loc_point).x,OFFLINE_Trajectory.at(loc_point).y,0);	
		glColor3f(0.0,1.0,1.0);
		glVertex3f(Realbuf.last().shv.x,Realbuf.last().shv.y,0);	
		}
		glEnd();


	/*
	for(int i=1;i<OFFLINE_Trajectory.size()-1;i++)
	{	//if(i<loc_point)
		//glColor3f(1.0,1.0,1.0);
		//else
		glColor3f(0.0,0.0,1.0);
		glVertex3f(OFFLINE_Trajectory.at(i-1).x,OFFLINE_Trajectory.at(i-1).y,0);	
		glVertex3f(OFFLINE_Trajectory.at(i).x,OFFLINE_Trajectory.at(i).y,0);	
	}	
	*/
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1.0,1.0,0.0);
	for(int i=1;i<Realbuf.size()-1;i++)
	{
		glVertex3f(Realbuf.at(i-1).shv.x,Realbuf.at(i-1).shv.y,0);	
		glVertex3f(Realbuf.at(i).shv.x,Realbuf.at(i).shv.y,0);	
	}
		glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	for(int i=0;i<TRAJECTORY_SET_NUM;i++)
	{
		if(Path_Generate.traj_sets[i].feasible==true)
		{
			glColor3f(1.0,1.0,1.0);
				for(int j=1;j<TRAJEC_POINTS-1;j++)
			{
			glVertex3f(Path_Generate.traj_sets[i].states[j-1].x,Path_Generate.traj_sets[i].states[j-1].y,0);	
			glVertex3f(Path_Generate.traj_sets[i].states[j].x,Path_Generate.traj_sets[i].states[j].y,0);	
			}
		}
		else
			glColor3f(1.0,0.0,0.0);
		if(Realbuf.size())
		if(Realbuf.last().shv.x==Path_Generate.traj_sets[i].states[0].x&&
			Realbuf.last().shv.y==Path_Generate.traj_sets[i].states[0].y)
		for(int j=1;j<TRAJEC_POINTS-1;j++)
		{
		glVertex3f(Path_Generate.traj_sets[i].states[j-1].x,Path_Generate.traj_sets[i].states[j-1].y,0);	
		glVertex3f(Path_Generate.traj_sets[i].states[j].x,Path_Generate.traj_sets[i].states[j].y,0);	
		}
			
	}
	glEnd();

	glEndList();
}

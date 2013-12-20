#include "Kelly_PG.h"
/**************************
Path Generation Method  4parameter clothoid 
**************************/

/***************************
Jacobi matrix 4*4
Input: temp state space
Return: 4*4 matrix
***************************/
MAT_44 PG_kelly::Jacobi_matrix_4p(PARA_STATE state)
{
	double k=0,a,b,c,d,s,w,f,g;
	double x1=0,x2=0,x3=0,x4=0,y1=0,y2=0,y3=0,y4=0,N=100;
	k=state.k0;a=state.a;b=state.b;c=state.c;d=state.d;s=state.s;
	for(int i=0;i<=N;i++)
	{
		if(i==0||i==N)
			w=1;
		else if(i%2==1)
			w=4;
		else
			w=2;	

		s=state.s*i/N;
		f=cos(k*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5);
		g=sin(k*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5);
		x1=x1+s*s*w*g;
		x2=x2+s*s*s*w*g;
		x3=x3+s*s*s*s*w*g;
		x4=x4+s*s*s*s*s*w*g;
		y1=y1+s*s*w*f;
		y2=y2+s*s*s*w*f;
		y3=y3+s*s*s*s*w*f;
		y4=y4+s*s*s*s*s*w*f;
	}
	s=state.s;
	f=cos(k*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5);
	g=sin(k*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5);
	s=s/N/3;
	x1=x1*s;x2=x2*s;x3=x3*s,x4=x4*s;
	y1=y1*s;y2=y2*s;y3=y3*s,y4=y4*s;
	s=state.s;
	MAT_44 jaco_matrix;

	jaco_matrix.matrix[0][0]=-x2/3;jaco_matrix.matrix[0][1]=-x3/4;	jaco_matrix.matrix[0][2]=-x4/5;	
	jaco_matrix.matrix[0][3]=f;jaco_matrix.matrix[1][0]=y2/3;jaco_matrix.matrix[1][1]=y3/4;
	jaco_matrix.matrix[1][2]=y4/5;	jaco_matrix.matrix[1][3]=g;jaco_matrix.matrix[2][0]=s*s*s/3;
	jaco_matrix.matrix[2][1]=s*s*s*s/4;jaco_matrix.matrix[2][2]=s*s*s*s*s/5;jaco_matrix.matrix[2][3]=k+a*s+b*s*s+c*s*s*s+d*s*s*s*s;
	jaco_matrix.matrix[3][0]=s*s;jaco_matrix.matrix[3][1]=s*s*s;jaco_matrix.matrix[3][2]=s*s*s*s;
	jaco_matrix.matrix[3][3]=a+2*b*s+3*c*s*s+4*d*s*s*s;
	return jaco_matrix;
}

/***************************
Parameter Initial
Input: start and end space
Return: state
***************************/
para_state PG_kelly::state_initial_4p()
{
	double k0=0,a=0.01;
	k0=start_state.curvature;
	trajec_state tem;
	tem.x=end_state.x;tem.y=end_state.y;
	end_state.x=cos(start_state.theta)*(tem.x-start_state.x)+sin(start_state.theta)*(tem.y-start_state.y);
	end_state.y=cos(start_state.theta)*(tem.y-start_state.y)-sin(start_state.theta)*(tem.x-start_state.x);//because the Y vector =0
	//-pi~pi
	if(end_state.theta-start_state.theta>PI)
		end_state.theta=(end_state.theta-start_state.theta)-PI-PI;
	else if(end_state.theta-start_state.theta<-PI)
		end_state.theta=PI+PI+(end_state.theta-start_state.theta);
	else
		end_state.theta=end_state.theta-start_state.theta;


	double dist=sqrt(end_state.x*end_state.x+end_state.y*end_state.y);
	double theta=abs(end_state.theta);
	temp_state.s=dist*(theta*theta/5+1)+2*theta/5;
	double s=temp_state.s;
	temp_state.d=0;
	temp_state.a=a;

	temp_state.b=(-9*k0)/(s*s)-(3*end_state.curvature)/(s*s) -  (3*a)/s  +  (12*end_state.theta)/(s*s*s);
	temp_state.c=(8*k0)/(s*s*s)+(4*end_state.curvature)/(s*s*s) + (2*a)/(s*s)  -  (12*end_state.theta)/(s*s*s*s);
		

	return temp_state;
}
/***************************
trajectory state calculation
Input: temp parameter space
Return: trajectory state
***************************/

TRAJEC_STATE PG_kelly::calcu_trac_state_4p(PARA_STATE state)
{
	double k0,a,b,c,d,s,w,f,g;
	double N=100,x=0,y=0;
	k0=state.k0;a=state.a;b=state.b;c=state.c;d=state.d;s=state.s;
	double k=k0+a*s+b*s*s+c*s*s*s+d*s*s*s*s;
	double theta=0+k0*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5;
	for(int i=0;i<=N;i++)
	{
		if(i==0||i==N)
			w=1;
		else if(i%2==1)
			w=4;
		else
			w=2;	

		s=state.s*i/N;
		f=cos(k0*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5);
		g=sin(k0*s+a*s*s/2+b*s*s*s/3+c*s*s*s*s/4+d*s*s*s*s*s/5);
		x+=w*f;
		y+=w*g;
	}
	x=x*state.s/N/3;
	y=y*state.s/N/3;

	TRAJEC_STATE tr_state;
	tr_state.x=x;tr_state.y=y;
	tr_state.theta=theta;tr_state.curvature=k;
	return tr_state;

}

/***************************
convergence judgment 
Input: dest_state and temp_state
Return: 0 or 1
***************************/
bool PG_kelly::Conver_judge_4p(trajec_state state, trajec_state endstate)
{
	if(abs(state.x-endstate.x)<=0.001&&abs(state.y-endstate.y)<=0.001&&
		abs(state.theta-endstate.theta)<=0.1&&abs(state.curvature-endstate.curvature)<=0.05)
		return true;
	else
		return false;
}

/***************************
Jacobi/trajec_state
Input: Jacobi matrix and trajec vector
Return:  trajec vector
***************************/
PARA_STATE PG_kelly::Matrix_divide_4p(MAT_44 jac,trajec_state qq)
{
	PARA_STATE   delta_return;                                          	
	//	invers_matri(&jac.matrix[0][0], 4);
	qq.curvature=qq.curvature-end_state.curvature;
	qq.theta=qq.theta-end_state.theta;
	qq.x=qq.x-end_state.x;
	qq.y=qq.y-end_state.y;
	CvMat* k1=cvCreateMat(4,4,CV_64FC1);
	CvMat* k2=cvCreateMat(4,4,CV_64FC1);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cvmSet(k1,i,j,jac.matrix[i][j]);




	cvInvert(k1,k2,CV_SVD);


	/**************delta_return=jac^(-1)*qq******/
	/*
	delta_return.a=qq.x*jac.matrix[0][0]+qq.y*jac.matrix[0][1]+
	qq.theta*jac.matrix[0][2]+qq.curveture*jac.matrix[0][3];
	delta_return.b=qq.x*jac.matrix[1][0]+qq.y*jac.matrix[1][1]+
	qq.theta*jac.matrix[1][2]+qq.curveture*jac.matrix[1][3];
	delta_return.c=qq.x*jac.matrix[2][0]+qq.y*jac.matrix[2][1]+
	qq.theta*jac.matrix[2][2]+qq.curveture*jac.matrix[2][3];
	delta_return.s=qq.x*jac.matrix[3][0]+qq.y*jac.matrix[3][1]+
	qq.theta*jac.matrix[3][2]+qq.curveture*jac.matrix[3][3];
	*/	
	delta_return.b=qq.x*cvmGet(k2,0,0)+qq.y*cvmGet(k2,0,1)+
		qq.theta*cvmGet(k2,0,2)+qq.curvature*cvmGet(k2,0,3);
	delta_return.c=qq.x*cvmGet(k2,1,0)+qq.y*cvmGet(k2,1,1)+
		qq.theta*cvmGet(k2,1,2)+qq.curvature*cvmGet(k2,1,3);
	delta_return.d=qq.x*cvmGet(k2,2,0)+qq.y*cvmGet(k2,2,1)+
		qq.theta*cvmGet(k2,2,2)+qq.curvature*cvmGet(k2,2,3);
	delta_return.s=qq.x*cvmGet(k2,3,0)+qq.y*cvmGet(k2,3,1)+
		qq.theta*cvmGet(k2,3,2)+qq.curvature*cvmGet(k2,3,3);

	cvReleaseMat(&k1);cvReleaseMat(&k2);


	return delta_return;
}

/***************************
Path generating main function
Input: begin and end state
Return:  
***************************/
void PG_kelly::Path_Generating_4p(trajec_state start,trajec_state end)
{
	MAT_44 JAC_M;
	PARA_STATE delta_p;
	start_state=start;end_state=end;
	PARA_STATE p=state_initial_4p();//initial
	TRAJEC_STATE q=calcu_trac_state_4p(p);
	state_data.clear();
	for(int i=0;i<ITERA_TIME;i++)
	{
		if(Conver_judge_4p(q,end_state)==true)
		{
			TRAJEC_STATE temp_trajec;
			PARA_STATE temp_para;
			temp_para=p;
			for(int i=0;i<TRAJEC_POINTS;i++)
			{
				temp_para.s=i*p.s/TRAJEC_POINTS;
				q=calcu_trac_state_4p(temp_para);
				temp_trajec.x=cos(start_state.theta)*q.x-sin(start_state.theta)*q.y+start_state.x;
				temp_trajec.y=cos(start_state.theta)*q.y+sin(start_state.theta)*q.x+start_state.y;
				temp_trajec.theta=q.theta+start_state.theta;
				temp_trajec.curvature=q.curvature;
				/*************here we may have some conditions of the trajectory*******************/
				if(1)
				{
					state_data.push_back(temp_trajec);
				}
			}
			break;
		}
		JAC_M=Jacobi_matrix_4p(p);
		delta_p=Matrix_divide_4p(JAC_M,q);
		//p.a=p.a-delta_p.a;
		p.b=p.b-delta_p.b;
		p.c=p.c-delta_p.c;
		p.d=p.d-delta_p.d;
		p.s=p.s-delta_p.s;
		q=calcu_trac_state_4p(p);
	}
	//then p is the parameter space
	



}
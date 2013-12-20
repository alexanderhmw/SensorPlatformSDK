#ifndef KELLY_PG_H
#define KELLY_PG_H
//for the use of opencv lib
#include<SensingPlatformSDK\Device\Sensor\XTion\SENSOR_XTION.h>
#include<vector>
using namespace std;
#define TRAJECTORY_SET_NUM  7
#define ITERA_TIME 100
#define TRAJEC_POINTS 100
#define Delta_Curvature
#define PI 3.141592653589

typedef struct mat_44
{
	double matrix[4][4];
}MAT_44;


typedef struct para_state
{	
	double k0;
	double a;
	double b;
	double c;
	double d;
	double s;
}PARA_STATE;

typedef struct trajec_state
{
	double x;
	double y;
	double theta;
	double curvature;
}TRAJEC_STATE;

typedef struct 
{
	int num;
	bool feasible;
	int collide_num;
	double dist_to_init_trajectory;
	TRAJEC_STATE states[TRAJEC_POINTS];
}trajectory_sets;

class PG_kelly
{
	public:	
	PG_kelly();
	~PG_kelly();
	trajec_state start_state;//
	trajec_state end_state;
	trajectory_sets traj_sets[TRAJECTORY_SET_NUM];
	int best_index;
	trajec_state R_T;//简单的运用这个
	//结构来表示   x y为平移  theta为旋转

	PARA_STATE temp_state;

	para_state state_initial();
	MAT_44 Jacobi_matrix(PARA_STATE state);
	TRAJEC_STATE calcu_trac_state(PARA_STATE state);
	bool Conver_judge(trajec_state state, trajec_state endstate);
	void invers_matri(double mat[], int T);
	PARA_STATE Matrix_divide(MAT_44 jac,trajec_state q);
	bool Path_Generating(trajec_state start,trajec_state end);
	bool Path_saving(trajec_state start,trajec_state end,int num);

	//4 parameter trajectory generating
	void PG_kelly::Path_Generating_4p(trajec_state start,trajec_state end);
	PARA_STATE PG_kelly::Matrix_divide_4p(MAT_44 jac,trajec_state qq);
	bool PG_kelly::Conver_judge_4p(trajec_state state, trajec_state endstate);
	TRAJEC_STATE PG_kelly::calcu_trac_state_4p(PARA_STATE state);
	para_state PG_kelly::state_initial_4p();
	MAT_44 PG_kelly::Jacobi_matrix_4p(PARA_STATE state);

	QVector<TRAJEC_STATE> state_data;
};

#endif
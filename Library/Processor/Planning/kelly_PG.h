#ifndef KELLY_PG_H
#define KELLY_PG_H

#include "Planning_def.h"
#include <opencv2\opencv.hpp>

#define TRAJECTORY_SET_NUM  7
#define ITERA_TIME 100
#define TRAJEC_POINTS 100
#define Delta_Curvature
#define PI 3.141592653589

struct Q_DECL_EXPORT MAT_44
{
	double matrix[4][4];
};

struct Q_DECL_EXPORT PARA_STATE
{	
	double k0;
	double a;
	double b;
	double c;
	double d;
	double s;
};

struct Q_DECL_EXPORT TRAJEC_STATE
{
	double x;
	double y;
	double theta;
	double curvature;
};

struct Q_DECL_EXPORT TRAJEC_SETS
{
	int num;
	bool feasible;
	int collide_num;
	double dist_to_init_trajectory;
	TRAJEC_STATE states[TRAJEC_POINTS];
};

class Q_DECL_EXPORT PG_kelly
{
	public:	
	PG_kelly();
	~PG_kelly();
	TRAJEC_STATE start_state;//
	TRAJEC_STATE end_state;
	TRAJEC_SETS traj_sets[TRAJECTORY_SET_NUM];
	int best_index;
	TRAJEC_STATE R_T;//简单的运用这个
	//结构来表示   x y为平移  theta为旋转

	PARA_STATE temp_state;

	PARA_STATE state_initial();
	MAT_44 Jacobi_matrix(PARA_STATE state);
	TRAJEC_STATE calcu_trac_state(PARA_STATE state);
	bool Conver_judge(TRAJEC_STATE state, TRAJEC_STATE endstate);
	void invers_matri(double mat[], int T);
	PARA_STATE Matrix_divide(MAT_44 jac,TRAJEC_STATE q);
	bool Path_Generating(TRAJEC_STATE start,TRAJEC_STATE end);
	bool Path_saving(TRAJEC_STATE start,TRAJEC_STATE end,int num);

	//4 parameter trajectory generating
	void PG_kelly::Path_Generating_4p(TRAJEC_STATE start,TRAJEC_STATE end);
	PARA_STATE PG_kelly::Matrix_divide_4p(MAT_44 jac,TRAJEC_STATE qq);
	bool PG_kelly::Conver_judge_4p(TRAJEC_STATE state, TRAJEC_STATE endstate);
	TRAJEC_STATE PG_kelly::calcu_trac_state_4p(PARA_STATE state);
	PARA_STATE PG_kelly::state_initial_4p();
	MAT_44 PG_kelly::Jacobi_matrix_4p(PARA_STATE state);

	QVector<TRAJEC_STATE> state_data;
};

#endif
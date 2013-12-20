#ifndef COLLISION_DETECT_H
#define COLLISION_DETECT_H

#include<Modules\SensorDataStorage\UDP\UDP_DATASTORAGE.h>
#include<qvector.h>
#include<ProcessModule\Planning\PathGeneration\Kelly_PG.h>
typedef struct _POSS_DATA
{
	double x;
	double y;
	double z;
	double yaw;
}_POSS;

#define RESOLUTION 2
#define Angle 180
#define Range	RESOLUTION*Angle+1


#define SafetyZone 0.5*0.5

class COLLISION_DETECT
{
public:
	COLLISION_DETECT();
	~COLLISION_DETECT();
	//laser point data cache
	QVector<short> laserdata;
	QVector<_POSS_DATA> LP_Cord;
	//project laser point to local coordinate
	bool Cord_Projection(SLAM_DATA tmpPOS);
	bool  Collision_detection(trajectory_sets * Tmptrajectory);
};

#endif
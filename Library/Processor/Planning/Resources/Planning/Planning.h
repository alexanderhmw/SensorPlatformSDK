#ifndef PLANNING_H
#define PLANNING_H

#include<Device\Sensor\UDP\SENSOR_UDP.h>
#include<Device\Sensor\URG\SENSOR_URG.h>
#include<Modules\SensorDataStorage\UDP\UDP_DATASTORAGE.h>
#include<Core\DataProcessor\DataContainer\MULTIDATACONTAINERREF.h>
#include <QTimer>
#include<Modules\SensorDataConverter\TrackOrder\TRACKORDER_DATACONVERTER_COMPORT.h>
#include<Core\OpenGL\GLviewer.h>
#include"PathGeneration\Kelly_PG.h"
#include"CollisionDetect\CollisionDetect.h"

#define PI 3.141592653589


class MINI_PLANNING : public QObject
{
	Q_OBJECT
public:
	MINI_PLANNING();
	~MINI_PLANNING();
	//Path Generation
	PG_kelly	Path_Generate;
	// SLAM displaylist
	DISPLAYLIST SLAM_LIST;
	//qtimer
	QTimer *timer;
	//data
	MULTIDATACONTAINERREF PLANNINGDATA;
		//dataconverter
	TRACKORDERDATACONVERTERCOMPORT track_com_dataconverter;
	// read write lock
	QReadWriteLock  Tracking_lock;
	//POSITION Data    from SLAM
	QVector<void *> PosVector;
	//OBJECT Data from SLAM too
	QVector<void *> LaserVector;
	//trajectory vector
	QVector <_POSS>  OFFLINE_Trajectory;
	//trajectory vector
	QVector <_POSS>  Tracking_Trajectory;
private: 
	uint aim_point;
	uint loc_point;  //the location in the trajectory vector
	void FinalTrackingTrajectory(uint num);
	bool TrajectorySetsGenerate(trajec_state Pos1,trajec_state Pos2);
	int get_angle(double sx, double sy,  double hx, double hy,          double tx, double ty);
	bool Planning();
	uint find_neibour_point(SLAM_DATA SlamData);
	void update_displaylist();
	QVector<SLAM_DATA> Realbuf;
	bool DepackPos();
	bool DepackLaser();
	//Collision detection module
	COLLISION_DETECT NO_COLLISION;
	//generate signal
signals:
	void StopSignal();
	void PlanOver(void * dataptr, QReadWriteLock * lockptr);
	void VoiceSignal(int num);
private slots:
	void Update();
	void planstart();
};


#endif
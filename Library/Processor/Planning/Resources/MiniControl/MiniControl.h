#ifndef MINI_CONTROL_H
#define MINI_CONTROL_H

#include<Device\Sensor\UDP\SENSOR_UDP.h>
#include<Modules\SensorDataStorage\UDP\UDP_DATASTORAGE.h>
#include<Core\DataProcessor\DataContainer\MULTIDATACONTAINERREF.h>
#include <QTimer>
#include<Modules\SensorDataConverter\TrackOrder\TRACKORDER_DATACONVERTER_COMPORT.h>
#include<Core\OpenGL\GLviewer.h>
#include<ProcessModule\Planning\CollisionDetect\CollisionDetect.h>


typedef struct _VOLC_CONTROL
{
	short Kp;
	short Ki;
	short Kd;
	short Steer;
	short Velocity;
}_VOLC;

#define PI 3.141592653589
typedef enum{steer,speed,speedPID,both}order_type;

class MINI_CONTROL : public QObject
{
	Q_OBJECT
public:
	MINI_CONTROL();
	~MINI_CONTROL();
	// SLAM displaylist
	DISPLAYLIST SLAM_LIST;
	//qtimer
	QTimer timer;
	double aaa,bbb,ccc;
	//data
	//MULTIDATACONTAINERREF test_course;
		//dataconverter
	TRACKORDERDATACONVERTERCOMPORT track_com_dataconverter;
	//vector
	QVector<void *> tmpvector;
	//
	void Send_Order(order_type Type);
	// default orders
		_VOLC _Default_VOLC;
	//
		char sendorderflag;   //”√”⁄≈–∂œsendorder”√
		QByteArray *send_orders;
	// read write lock
		QReadWriteLock  order_lock;
		QReadWriteLock  Trajectory_lock;
	//trajectory vector
		QVector <_POSS> Tracking_trajectory;
private: 
	uint aim_point;
	uint loc_point;
	void Rec_Single_Line();
	void Traj_Tracking();
	uint find_neibour_point(SLAM_DATA SlamData);
	void update_displaylist();
	QVector<SLAM_DATA> Realbuf;
	//generate signal
signals:
	void dataUpdate(void * dataptr, QReadWriteLock * lockptr);
	void send2s(int steer, int speed);
private slots:
	void Update();
	void PlanResult(void * dataptr, QReadWriteLock * lockptr);
	void Stop();
	void controlstart();
	void receivelocalization(void *dataptr, QReadWriteLock *lockptr);
};


#endif
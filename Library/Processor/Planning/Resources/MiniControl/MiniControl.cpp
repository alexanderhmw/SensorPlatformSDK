#include "MiniControl.h"
#define max_speed 40
MINI_CONTROL::MINI_CONTROL()
{  	
	timer.setParent(this);
	timer.setInterval(200);
	//send_orders=new QByteArray;
	////inital output
	//_Default_VOLC.Kp=3;
	//_Default_VOLC.Ki=0;
	//_Default_VOLC.Kd=5;
	//_Default_VOLC.Steer=-1;
	//_Default_VOLC.Velocity=10;

	//aaa=1000;
	//bbb=1;
	//ccc=0; 
	//sendorderflag=0;
	////timer
	////timer = QTimer(this);
	//connect(&timer,SIGNAL(timeout()),this,SLOT(Update()));
	//timer.start(100);
}
MINI_CONTROL::~MINI_CONTROL()
{
	timer.stop();
}

/*********************************************
send orders to comport				PACK and WRITE
four kind of indications
//write orders
//steer F8+03+01+short+8F
//velocity F8+03+02+short+8F
//both F8+04+short+short+8F
//PID F8+08+short*4+8F
*********************************************/

#define pack_header (char)0xf8
#define pack_tail (char)0x8f
void MINI_CONTROL::Send_Order(order_type Type)
{
	char data_size;
	char * dataput;
	switch (Type)
	{
	case(steer):
		data_size=sizeof(short)+1;
		dataput=(char*)malloc(data_size+3);
		dataput[0]=pack_header;
		dataput[1]=data_size;
		dataput[2]=0x01;
		*(short*)&dataput[3]=-_Default_VOLC.Steer;
		break;
	case(speed):
		data_size=sizeof(short)+1;
		dataput=(char*)malloc(data_size+3);
		dataput[0]=pack_header;
		dataput[1]=data_size;
		dataput[2]=0x02;
		*(short*)&dataput[3]=_Default_VOLC.Velocity;
		break;
	case(speedPID):
		data_size=sizeof(short)*4;
		dataput=(char*)malloc(data_size+3);
		dataput[0]=pack_header;
		dataput[1]=data_size;
		*(short*)&dataput[2]=_Default_VOLC.Kp;
		*(short*)&dataput[4]=_Default_VOLC.Ki;
		*(short*)&dataput[6]=_Default_VOLC.Kd;
		*(short*)&dataput[8]=_Default_VOLC.Velocity;
		break;
	case(both):
		data_size=sizeof(short)*2;
		dataput=(char*)malloc(data_size+3);
		dataput[0]=pack_header;
		dataput[1]=data_size;
		*(short*)&dataput[2]=_Default_VOLC.Steer;
		*(short*)&dataput[4]=_Default_VOLC.Velocity;
		break;
	default:
		return;
		break;
	}
	if(dataput[0]==pack_header){
		order_lock.lockForWrite();
		send_orders->clear();
		send_orders->append(dataput,data_size+2);
		send_orders->append(pack_tail);
		free(dataput);
		emit dataUpdate((void *)send_orders,&order_lock);
		order_lock.unlock();
		//Serial_Com->write(send_orders->data(),send_orders->size());
	}
}
static int accler_count=0;
void MINI_CONTROL::Stop()
{
	timer.stop();
	accler_count=10;
	_Default_VOLC.Velocity=accler_count;
	this->Send_Order(speed);
	//timer.start();
}

void MINI_CONTROL::PlanResult(void * dataptr, QReadWriteLock * lockptr)
{
	//plan over   so that we could renew some parameters
	timer.stop();
	lockptr->lockForRead();
	QVector <_POSS> * tmpvec=(QVector <_POSS> *)dataptr;
	Tracking_trajectory.clear();
	Tracking_trajectory.resize(tmpvec->size());
	for(int i=0;i<tmpvec->size();i++)
	{
		Tracking_trajectory[i]=tmpvec->at(i);
	}
	lockptr->unlock();
	aim_point=0;
	loc_point=0;
	//剩下需要每次更新轨迹的时候更新当前位置在目标点中的对应点，预瞄点等等
	accler_count=accler_count<20?20:accler_count;
	accler_count=accler_count>max_speed?max_speed:accler_count+5;
	_Default_VOLC.Velocity=accler_count;
	this->Send_Order(speed);
	//timer.start();
}

void MINI_CONTROL::controlstart()
{
	send_orders=new QByteArray;
	//inital output
	_Default_VOLC.Kp=3;
	_Default_VOLC.Ki=0;
	_Default_VOLC.Kd=5;
	_Default_VOLC.Steer=-1;
	_Default_VOLC.Velocity=10;

	aaa=1000;
	bbb=1;
	ccc=0; 
	sendorderflag=0;
	//timer
	//timer = QTimer(this);
	bool flag=connect(&timer,SIGNAL(timeout()),this,SLOT(Update()));
	//timer.start();
}

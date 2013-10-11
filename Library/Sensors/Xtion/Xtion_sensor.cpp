#include "Xtion.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	XTIONSENSORPARAMS * Xtionparams=(XTIONSENSORPARAMS *)(*params);
	if(Xtionparams==NULL)
	{//case1: params point to a NULL
		*params=(void *)(new XTIONSENSORPARAMS);
		Xtionparams=(XTIONSENSORPARAMS *)(*params);
	}
	else
	{//case2: Xtion point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getParam("resolutionx",Xtionparams->resolutionx);
	flag&=loader.getParam("resolutiony",Xtionparams->resolutiony);
	flag&=loader.getParam("fps",Xtionparams->fps);
	return flag;
}

void releaseParamsSensor(void ** params)	//release params
{
	XTIONSENSORPARAMS * Xtionparams=(XTIONSENSORPARAMS *)(*params);
	if(Xtionparams==NULL)
	{//case1: params point to a NULL
		
		Xtionparams=(XTIONSENSORPARAMS *)(*params);
	}
	else
	{//case2: Xtion point to a memory block
		delete Xtionparams;
		*params=NULL;
	}
}

bool openSensor(void * params)	//open the sensor using params
{
	XTIONSENSORPARAMS * Xtionparams=(XTIONSENSORPARAMS *)params;
	openni::Status rc;

	rc = openni::OpenNI::initialize();

	rc=Xtionparams->device.open(NULL);
	if(rc!=openni::STATUS_OK)
	{
		return 0;
	}
	openni::VideoMode vediomode;
	vediomode.setResolution(Xtionparams->resolutionx,Xtionparams->resolutiony);
	vediomode.setFps(Xtionparams->fps);

	rc=Xtionparams->depth.create(Xtionparams->device,openni::SENSOR_DEPTH);
	if(rc==openni::STATUS_OK)
	{	
		vediomode.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
		rc=Xtionparams->depth.setVideoMode(vediomode);
		if(rc!=openni::STATUS_OK)
		{
			Xtionparams->depth.destroy();
		}
		rc=Xtionparams->depth.start();
		if(rc!=openni::STATUS_OK)
		{
			Xtionparams->depth.destroy();
		}
	}
	rc=Xtionparams->color.create(Xtionparams->device,openni::SENSOR_COLOR);
	if(rc==openni::STATUS_OK)
	{
		vediomode.setPixelFormat(openni::PIXEL_FORMAT_RGB888);
		rc=Xtionparams->color.setVideoMode(vediomode);
		if(rc!=openni::STATUS_OK)
		{
			Xtionparams->color.destroy();
		}
		rc=Xtionparams->color.start();
		if(rc!=openni::STATUS_OK)
		{
			Xtionparams->color.destroy();
		}
	}
	
	if (!Xtionparams->depth.isValid() || !Xtionparams->color.isValid())
	{
		openni::OpenNI::shutdown();
		return 0;
	}

	openni::VideoMode depthmode;
	openni::VideoMode colormode;

	depthmode=Xtionparams->depth.getVideoMode();
	colormode=Xtionparams->color.getVideoMode();


	int depthwidth=depthmode.getResolutionX();
	int depthheight=depthmode.getResolutionY();
	int colorwidth=colormode.getResolutionX();
	int colorheight=colormode.getResolutionY();

	if(depthwidth!=colorwidth || depthheight!=colorheight)
	{
		Xtionparams->depth.destroy();
		Xtionparams->color.destroy();
		openni::OpenNI::shutdown();
		return 0;
	}
	return 1;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	XTIONSENSORPARAMS * Xtionparams=(XTIONSENSORPARAMS *)params;
	openni::Status rc1,rc2;
	openni::VideoFrameRef depthframe;
	openni::VideoFrameRef colorframe;

	rc1=Xtionparams->depth.readFrame(&depthframe);
	QTime depthtimestamp=QTime::currentTime();
	rc2=Xtionparams->color.readFrame(&colorframe);
	QTime colortimestamp=QTime::currentTime();
	if(rc1!=openni::STATUS_OK||rc2!=openni::STATUS_OK)
	{
		depthframe.release();
		colorframe.release();
		return 0;
	}

	XTIONSENSORDATA * Xtiondata=(XTIONSENSORDATA *)(*data);
	if(Xtiondata==NULL)
	{//case1: data point to a NULL
		*data=(void *)new XTIONSENSORDATA;
		Xtiondata=(XTIONSENSORDATA *)(*data);
	}
	else
	{//case2: Xtion point to a memory block
		
	}
	cv::Mat tempdepth(depthframe.getHeight(), depthframe.getWidth(),CV_16UC1,(void*)depthframe.getData());
	tempdepth.convertTo(Xtiondata->depth,CV_8U,255.0/Xtionparams->depth.getMaxPixelValue());
	cv::flip(Xtiondata->depth,Xtiondata->depth,1);
	Xtiondata->depthtimestamp=depthtimestamp;

	Xtiondata->color.create(cv::Size(colorframe.getWidth(),colorframe.getHeight()),CV_8UC3);
	memcpy(Xtiondata->color.data,colorframe.getData(),colorframe.getDataSize());
	cv::flip(Xtiondata->color,Xtiondata->color,1);
	//cv::cvtColor(Xtiondata->color,Xtiondata->color,CV_RGB2BGR);
	Xtiondata->colortimestamp=colortimestamp;

	depthframe.release();	
	colorframe.release();
	return 1;
}

bool closeSensor(void * params)	//close the sensor using params
{
	XTIONSENSORPARAMS * Xtionparams=(XTIONSENSORPARAMS *)params;
	Xtionparams->depth.destroy();
	Xtionparams->color.destroy();
	openni::OpenNI::shutdown();
	return 1;
}

void releaseData(void ** data)	//release data
{
	XTIONSENSORDATA * Xtiondata=(XTIONSENSORDATA *)(*data);
	if(Xtiondata==NULL)
	{//case1: data point to a NULL
		
		Xtiondata=(XTIONSENSORDATA *)(*data);
	}
	else
	{//case2: Xtion point to a memory block
		delete Xtiondata;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function

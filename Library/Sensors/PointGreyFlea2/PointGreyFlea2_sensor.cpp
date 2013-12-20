#include "PointGreyFlea2.h"
#include<FuncLibrary\sensorfunc.h>

bool loadParamsSensor(QString configfilename,QString nodetype, QString nodeclass, QString nodename, void ** params)	//load params from XML
{
	XMLParamsLoader loader;
	if(!loader.loadParams(configfilename,nodetype,nodeclass,nodename))
	{
		return 0;
	}
	POINTGREYFLEA2SENSORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)(*params);
	if(PointGreyFlea2params==NULL)
	{//case1: params point to a NULL
		*params=(void *)(new POINTGREYFLEA2SENSORPARAMS);
		PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)(*params);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}
	bool flag=1;
	flag&=loader.getEnumParam("videomode",PointGreyFlea2params->videomode);
	flag&=loader.getEnumParam("framerate",PointGreyFlea2params->framerate);
	flag&=loader.getEnumParam("pixelformat",PointGreyFlea2params->pixelformat);
	return flag;
}

void releaseParamsSensor(void ** params)	//release params
{
	POINTGREYFLEA2SENSORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)(*params);
	if(PointGreyFlea2params==NULL)
	{//case1: params point to a NULL
		
		PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)(*params);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2params;
		*params=NULL;
	}
}

bool openSensor(void * params, QObject ** trigger, QString & triggersignal)	//open the sensor using params
{
	POINTGREYFLEA2SENSORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)params;

	FlyCapture2::Error error;
	FlyCapture2::BusManager busmgr;

	PointGreyFlea2params->camera=new FlyCapture2::Camera();

	FlyCapture2::PGRGuid guid;
	error = busmgr.GetCameraFromIndex( 0, &guid );
	if (error != FlyCapture2::PGRERROR_OK)
	{		
		delete PointGreyFlea2params->camera;
		PointGreyFlea2params->camera=NULL;
		//QMessageBox::information(NULL,QString("Flea2 Open Error"),QString("GetCameraFromIndex() Error"));
		return 0;
	}

	error = PointGreyFlea2params->camera->Connect( &guid );
	if (error != FlyCapture2::PGRERROR_OK)
	{
		delete PointGreyFlea2params->camera;
		PointGreyFlea2params->camera=NULL;
		return 0;
	}

	error = PointGreyFlea2params->camera->SetVideoModeAndFrameRate( 
		PointGreyFlea2params->videomode, 
		PointGreyFlea2params->framerate);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		delete PointGreyFlea2params->camera;
		PointGreyFlea2params->camera=NULL;
		return 0;
	}

	error = PointGreyFlea2params->camera->StartCapture();
	if (error != FlyCapture2::PGRERROR_OK)
	{
		delete PointGreyFlea2params->camera;
		PointGreyFlea2params->camera=NULL;
		return 0;
	}

	FlyCapture2::Image image;
	FlyCapture2::Image convertor;

	error = PointGreyFlea2params->camera->RetrieveBuffer( &image );
	if (error != FlyCapture2::PGRERROR_OK)
	{
		return 0;
	}
	error = image.Convert(PointGreyFlea2params->pixelformat,&convertor);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		return 0;
	}
	PointGreyFlea2params->resolutionx=convertor.GetCols();
	PointGreyFlea2params->resolutiony=convertor.GetRows();
	return 1;
}

bool captureData(void * params, void ** data)	//capture data using params and store in data
{
	POINTGREYFLEA2SENSORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)params;
	POINTGREYFLEA2SENSORDATA * PointGreyFlea2data=(POINTGREYFLEA2SENSORDATA *)(*data);
	if(PointGreyFlea2data==NULL)
	{//case1: data point to a NULL
		*data=(void *)new POINTGREYFLEA2SENSORDATA;
		PointGreyFlea2data=(POINTGREYFLEA2SENSORDATA *)(*data);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		
	}

	FlyCapture2::Error error;

	FlyCapture2::Image image;
	FlyCapture2::Image convertor;

	error = PointGreyFlea2params->camera->RetrieveBuffer( &image );
	PointGreyFlea2data->timestamp=QTime::currentTime();
	if (error != FlyCapture2::PGRERROR_OK)
	{
		return 0;
	}
	error = image.Convert(PointGreyFlea2params->pixelformat,&convertor);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		return 0;
	}

	PointGreyFlea2data->image.create(cv::Size(convertor.GetCols(),convertor.GetRows()),CV_8UC3);	//!!!!!!
	memcpy(PointGreyFlea2data->image.data,convertor.GetData(),convertor.GetDataSize());
}

bool closeSensor(void * params, QObject ** trigger, QString & triggersignal)	//close the sensor using params
{
	POINTGREYFLEA2SENSORPARAMS * PointGreyFlea2params=(POINTGREYFLEA2SENSORPARAMS *)params;
	if(PointGreyFlea2params->camera!=NULL)
	{
		PointGreyFlea2params->camera->Disconnect();
		delete PointGreyFlea2params->camera;
		PointGreyFlea2params->camera=NULL;
	}
	return 1;
}

void releaseData(void ** data)	//release data
{
	POINTGREYFLEA2SENSORDATA * PointGreyFlea2data=(POINTGREYFLEA2SENSORDATA *)(*data);
	if(PointGreyFlea2data==NULL)
	{//case1: data point to a NULL
		
		PointGreyFlea2data=(POINTGREYFLEA2SENSORDATA *)(*data);
	}
	else
	{//case2: PointGreyFlea2 point to a memory block
		delete PointGreyFlea2data;
		*data=NULL;
	}
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function in the header

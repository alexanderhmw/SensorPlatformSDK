#include "fusion.h"

#pragma comment(lib,"NodeBase.lib")

InputLinker::InputLinker(int typeclassid,int nameid)
{
	_typeclassid=typeclassid;
	_nameid=nameid;
}

InputLinker::~InputLinker()
{
}

void InputLinker::inputLinkerSlot(void * data)
{
	emit inputLinkerSignal(_typeclassid,_nameid,data);
}

Fusion::Fusion(QString libraryname, QString fusionname, int inputbuffersize, int outputbuffersize)
	: NodeBase(libraryname, QString("Fusion"),fusionname) 
{
	FptrLoadCheck(getSupportInputNodesFptr,getSupportInputNodes,_library);
	FptrLoadCheck(openFusionFptr,openFusion,_library);
	FptrLoadCheck(inputDataFptr,inputData,_library);
	FptrLoadCheck(fuseDataFptr,fuseData,_library);
	FptrLoadCheck(closeFusionFptr,closeFusion,_library);
	FptrLoadCheck(releaseInputDataFptr,releaseInputData,_library);
	FptrLoadCheck(releaseOutputDataFptr,releaseOutputData,_library);

	_inputbuffersize=inputbuffersize;
	outputdatabuffer.resize(outputbuffersize);
	curoutputdataid=0;
	openflag=0;
}

Fusion::~Fusion()
{
	if(openflag)
	{
		closeFusionSlot();
	}
	int i,n;
	n=inputdatabuffer.size();
	for(i=0;i<n;i++)
	{
		int j,m=inputdatabuffer[i].size();
		for(j=0;j<m;j++)
		{
			int k,l=inputdatabuffer[i][j].size();
			for(k=0;k<l;k++)
			{
				releaseInputData(i,j,&(inputdatabuffer[i][j][k]));
			}
		}
	}
	inputdatabuffer.clear();
	n=outputdatabuffer.size();
	for(i=0;i<n;i++)
	{
		releaseOutputData(&(outputdatabuffer[i]));
	}
	outputdatabuffer.clear();
}

void Fusion::generateInputLinkersSlot()
{
	if(_params!=NULL)
	{
		getSupportInputNodes(_params,supportnodetypeclass,supportnodename);
		int i,n;
		n=inputdatabuffer.size();
		for(i=0;i<n;i++)
		{
			int j,m=inputdatabuffer[i].size();
			for(j=0;j<m;j++)
			{
				if(inputlinkers[i][j]!=NULL)
				{
					delete inputlinkers[i][j];
					inputlinkers[i][j]=NULL;
				}
				int k,l=inputdatabuffer[i][j].size();
				for(k=0;k<l;k++)
				{
					releaseInputData(i,j,&(inputdatabuffer[i][j][k]));
				}
			}
		}
		inputdatabuffer.clear();
		inputlinkers.clear();

		n=supportnodetypeclass.size();
		inputdatabuffer.resize(n);
		inputlinkers.resize(n);
		bool flag=1;
		for(i=0;i<n;i++)
		{
			int j,m=supportnodename[i].size();
			inputdatabuffer[i].resize(m);
			inputlinkers[i].resize(m);
			for(j=0;j<m;j++)
			{
				int l=supportnodename[i][j].size();
				inputdatabuffer[i][j].resize(l);
				inputlinkers[i][j]=new InputLinker(i,j);
				flag&=connect(inputlinkers[i][j],SIGNAL(inputLinkerSignal(int,int,void *)),this,SLOT(inputDataSlot(int,int,void *)));
			}
		}
		if(flag)
		{
			emit inputLinkersGeneratedSignal();
		}
		else
		{
			emit inputLinkersGeneratedErrorSignal();
		}
	}
	else
	{
		emit inputLinkersGeneratedErrorSignal();
	}
}

void Fusion::openFusionSlot()
{
	if(!openflag&&openFusion(_params))
	{
		openflag=1;
		emit fusionOpenSignal();
	}
	else
	{
		emit fusionOpenErrorSignal();
	}
}

void Fusion::inputDataSlot(int typeclassid, int nameid, void * data)
{
	if(openflag&&inputData(_params,typeclassid,nameid,data,&(inputdatabuffer[typeclassid][nameid][curinputdataid[typeclassid][nameid]])))
	{
		emit dataInputSignal(typeclassid,nameid);
		curinputdataid[typeclassid][nameid]=(curinputdataid[typeclassid][nameid]+1)%inputdatabuffer[typeclassid][nameid].size();
	}
	else
	{
		emit dataInputErrorSignal();
	}
}

void Fusion::fuseDataSlot()
{
	if(openflag)
	{
		QVector<QVector<QVector<void *>>> inputdataset;
		int i,n=inputdatabuffer.size();
		inputdataset.resize(n);
		for(i=0;i<n;i++)
		{
			int j,m=inputdatabuffer[i].size();
			for(j=0;j<m;j++)
			{
				if(inputdatabuffer[i][j][curinputdataid[i][j]]==NULL)
				{
					inputdataset[i][j]=inputdatabuffer[i][j].mid(0,curinputdataid[i][j]);
				}
				else
				{
					inputdataset[i][j]=inputdatabuffer[i][j].mid(curinputdataid[i][j]);
					inputdataset[i][j]+=inputdatabuffer[i][j].mid(0,curinputdataid[i][j]);
				}
			}
		}
		if(fuseData(_params,inputdataset,&(outputdatabuffer[curoutputdataid])))
		{
			emit dataFusedSignal(outputdatabuffer[curoutputdataid]);
			curoutputdataid=(curoutputdataid+1)%outputdatabuffer.size();
		}
		else
		{
			emit dataFusedErrorSignal();
		}
	}
	else
	{
		emit dataFusedErrorSignal();
	}
}

void Fusion::closeFusionSlot()
{
	if(openflag&&closeFusion(_params))
	{
		openflag=0;
		emit fusionCloseSignal();
	}
	else
	{
		emit fusionCloseErrorSignal();
	}
}

bool Fusion::connectGenerateInputLinkersSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(generateInputLinkersSlot()));
}

bool Fusion::connectOpenFusionSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(openFusionSlot()));
}

bool Fusion::connectInputDataSignal(NodeBase * sender, const char * signal)
{
	int typeclassid=supportnodetypeclass.indexOf(QString("%1_%2").arg(sender->getNodeType()).arg(sender->getNodeClass()));
	if(typeclassid<0)
	{
		return 0;
	}
	int nameid=supportnodename[typeclassid].indexOf(sender->getNodeName());
	if(nameid<0)
	{
		return 0;
	}
	return connect(sender,signal,inputlinkers[typeclassid][nameid],SLOT(inputLinkerSlot(void *)));
}

bool Fusion::connectFuseDataSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(fuseDataSlot()));
}

bool Fusion::connectCloseFusionSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(closeFusionSlot()));
}

bool Fusion::disconnectGenerateInputLinkersSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(generateInputLinkersSlot()));
}

bool Fusion::disconnectOpenFusionSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(openFusionSlot()));
}

bool Fusion::disconnectInputDataSignal(NodeBase * sender, const char * signal)
{
	int typeclassid=supportnodetypeclass.indexOf(QString("%1_%2").arg(sender->getNodeType()).arg(sender->getNodeClass()));
	if(typeclassid<0)
	{
		return 0;
	}
	int nameid=supportnodename[typeclassid].indexOf(sender->getNodeName());
	if(nameid<0)
	{
		return 0;
	}
	return disconnect(sender,signal,inputlinkers[typeclassid][nameid],SLOT(inputLinkerSLot(void *)));
}

bool Fusion::disconnectFuseDataSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(fuseDataSlot()));
}

bool Fusion::disconnectCloseFusionSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(closeFusionSlot()));
}

bool Fusion::connectInputLinkersGeneratedSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(inputLinkersGeneratedSignal()),receiver,slot);
}

bool Fusion::connectInputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(inputLinkersGeneratedErrorSignal()),receiver,slot);
}

bool Fusion::connectFusionOpenSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(fusionOpenSignal()),receiver,slot);
}

bool Fusion::connectFusionOpenErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(fusionOpenErrorSignal()),receiver,slot);
}

bool Fusion::connectDataInputSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataInputSignal(int,int)),receiver,slot);
}

bool Fusion::connectDataInputErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataInputErrorSignal()),receiver,slot);
}

bool Fusion::connectDataFusedSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataFusedSignal(void *)),receiver,slot);
}

bool Fusion::connectDataFusedErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataFusedErrorSignal()),receiver,slot);
}

bool Fusion::connectFusionCloseSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(fusionCloseSignal()),receiver,slot);
}

bool Fusion::connectFusionCloseErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(fusionCloseErrorSignal()),receiver,slot);
}

bool Fusion::disconnectInputLinkersGeneratedSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(inputLinkersGeneratedSignal()),receiver,slot);
}

bool Fusion::disconnectInputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(inputLinkersGeneratedErrorSignal()),receiver,slot);
}

bool Fusion::disconnectFusionOpenSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(fusionOpenSignal()),receiver,slot);
}

bool Fusion::disconnectFusionOpenErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(fusionOpenErrorSignal()),receiver,slot);
}

bool Fusion::disconnectDataInputSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataInputSignal(int,int)),receiver,slot);
}

bool Fusion::disconnectDataInputErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataInputErrorSignal()),receiver,slot);
}

bool Fusion::disconnectDataFusedSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataFusedSignal(void *)),receiver,slot);
}

bool Fusion::disconnectDataFusedErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataFusedErrorSignal()),receiver,slot);
}

bool Fusion::disconnectFusionCloseSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(fusionCloseSignal()),receiver,slot);
}

bool Fusion::disconnectFusionCloseErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(fusionCloseErrorSignal()),receiver,slot);
}


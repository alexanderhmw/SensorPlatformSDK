#include "fusion.h"

Fusion::Fusion(QString libraryname, QString fusionname, int inputbuffersize, int outputbuffersize)
	: NodeBase(libraryname, QString("Fusion"),fusionname) 
{
	FptrLoadCheck(getSupportNodesFptr,getSupportNodes,_library);
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
		getSupportNodes(_params,supportnodetypeclass,supportnodename);
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
		inputlinkers.clear();

		n=supportnodetypeclass.size();
		inputdatabuffer.resize(n);
		inputlinkers.resize(n);
		for(i=0;i<n;i++)
		{
			int j,m=supportnodename[i].size();
			inputdatabuffer[i].resize(m);
			inputlinkers.resize(m);
			for(j=0;j<m;j++)
			{
				int k,l=supportnodename[i][j].size();
				inputdatabuffer[i][j].resize(l);
				inputlinkers[i][j]._typeclassid=i;
				inputlinkers[i][j]._nameid=j;
			}
		}
		emit inputLinkersGeneratedSignal();
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

	}
}
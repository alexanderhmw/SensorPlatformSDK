#include "distribution.h"

#pragma comment(lib,"NodeBase.lib")

OutputLinker::OutputLinker()
{
}

OutputLinker::~OutputLinker()
{
}

void OutputLinker::sendOutputLinkerSignal(void * data)
{
	emit outputLinkerSignal(data);
}

Distribution::Distribution(NodeBase * nodebase)
	: NodeBase(nodebase->getLibraryName(),QString("Distribution"),nodebase->getNodeName())
{
	FptrLoadCheck(getSupportOutputNodesFptr,getSupportOutputNodes,_library);
	FptrLoadCheck(openDistributionFptr,openDistribution,_library);
	FptrLoadCheck(parseDataFptr,parseData,_library);
	FptrLoadCheck(closeDistributionFptr,closeDistribution,_library);

	openflag=0;
}

Distribution::~Distribution()
{
	if(openflag)
	{
		closeDistributionSlot();
	}
}

void Distribution::generateOutputLinkersSlot()
{
	if(_params!=NULL)
	{
		getSupportOutputNodes(_params,supportnodetypeclass,supportnodename);
		int i,n;
		n=outputlinkers.size();
		for(i=0;i<n;i++)
		{
			int j,m=outputlinkers[i].size();
			for(j=0;j<m;j++)
			{
				if(outputlinkers[i][j]!=NULL)
				{
					delete outputlinkers[i][j];
					outputlinkers[i][j]=NULL;
				}
			}
		}
		outputlinkers.clear();

		n=supportnodetypeclass.size();
		outputlinkers.resize(n);
		for(i=0;i<n;i++)
		{
			int j,m=supportnodename[i].size();
			outputlinkers[i].resize(m);
			for(j=0;j<m;j++)
			{
				outputlinkers[i][j]=new OutputLinker();
			}
		}
		emit outputLinkersGeneratedSignal();
	}
	else
	{
		emit outputLinkersGeneratedErrorSignal();
	}
}

void Distribution::openDistributionSlot()
{
	if(!openflag&&openDistribution(_params))
	{
		openflag=1;
		emit distributionOpenSignal();
	}
	else
	{
		emit distributionOpenErrorSignal();
	}
}

void Distribution::parseDataSlot(void * data)
{
	QVector<QVector<int>> distids;
	if(openflag&&parseData(_params,data,distids))
	{
		emit dataParsedSignal();
		int i,n=distids.size();
		for(i=0;i<n;i++)
		{
			int j,m=distids[i].size();
			for(j=0;j<m;j++)
			{
				outputlinkers[i][distids[i][j]]->sendOutputLinkerSignal(data);
			}
		}		
	}
	else
	{
		emit dataParsedErrorSignal();
	}
}

void Distribution::closeDistributionSlot()
{
	if(openflag&&closeDistribution(_params))
	{
		openflag=0;
		emit distributionCloseSignal();
	}
	else
	{
		emit distributionCloseErrorSignal();
	}
}

bool Distribution::connectGenerateOutputLinkerSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(generateOutputLinkersSlot()));
}

bool Distribution::connectOpenDistributionSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(openDistributionSlot()));
}

bool Distribution::connectParseDataSignal(NodeBase * sender, const char * signal)
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
	return connect(sender,signal,outputlinkers[typeclassid][nameid],SLOT(outputLinkerSlot(void *)));
}

bool Distribution::connectCloseDistributionSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(closeDistributionSlot()));
}

bool Distribution::disconnectGenerateOutputLinkerSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(generateOutputLinkersSlot()));
}

bool Distribution::disconnectOpenDistributionSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(openDistributionSlot()));
}

bool Distribution::disconnectParseDataSignal(NodeBase * sender, const char * signal)
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
	return disconnect(sender,signal,outputlinkers[typeclassid][nameid],SLOT(outputLinkerSlot(void *)));
}

bool Distribution::disconnectCloseDistributionSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(closeDistributionSlot()));
}

bool Distribution::connectOutputLinkersGeneratedSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(outputLinkersGeneratedSignal()),receiver,slot);
}

bool Distribution::connectOutputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(outputLinkersGeneratedErrorSignal()),receiver,slot);
}

bool Distribution::connectDistributionOpenSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(distributionOpenSignal()),receiver,slot);
}

bool Distribution::connectDistributionOpenErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(distributionOpenErrorSignal()),receiver,slot);
}

bool Distribution::connectDataParsedSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataParsedSignal()),receiver,slot);
}

bool Distribution::connectDataParsedErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataParsedErrorSignal()),receiver,slot);
}

bool Distribution::connectDistributionCloseSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(distributionCloseSignal()),receiver,slot);
}

bool Distribution::connectDistributionCloseErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(distributionCloseErrorSignal()),receiver,slot);
}

bool Distribution::disconnectOutputLinkersGeneratedSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(outputLinkersGeneratedSignal()),receiver,slot);
}

bool Distribution::disconnectOutputLinkersGeneratedErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(outputLinkersGeneratedErrorSignal()),receiver,slot);
}

bool Distribution::disconnectDistributionOpenSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(distributionOpenSignal()),receiver,slot);
}

bool Distribution::disconnectDistributionOpenErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(distributionOpenErrorSignal()),receiver,slot);
}

bool Distribution::disconnectDataParsedSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataParsedSignal()),receiver,slot);
}

bool Distribution::disconnectDataParsedErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataParsedErrorSignal()),receiver,slot);
}

bool Distribution::disconnectDistributionCloseSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(distributionCloseSignal()),receiver,slot);
}

bool Distribution::disconnectDistributionCloseErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(distributionCloseErrorSignal()),receiver,slot);
}
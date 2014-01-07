#include "simulator.h"

Simulator::Simulator(QString libraryname, QString simulatorname, int buffersize)
	: NodeBase(libraryname,QString("Simulator"),simulatorname)
{
	FptrLoadCheck(openSimulatorFptr,openSimulator,_library);
	FptrLoadCheck(loadDataFptr,loadData,_library);
	FptrLoadCheck(closeSimulatorFptr,closeSimulator,_library);
	FptrLoadCheck(dumpDataFptr,dumpData,_library);

	databuffer.resize(buffersize);
	curdataid=0;
	openflag=0;
	curtimestamp=0;
	emitdataid=-1;
	startflag=0;
}

Simulator::~Simulator()
{
	if(startflag)
	{
		stopSimulatorSlot();
	}
	if(openflag)
	{
		closeSimulatorSlot();
	}
	int i,n=databuffer.size();
	for(i=0;i<n;i++)
	{
		dumpData(&(databuffer[i]));
	}
	databuffer.clear();
}

void Simulator::emitDataSlot()
{
	int interval=int((nexttimestamp-curtimestamp)*simrate+0.5);
	if(interval>0&&startflag)
	{
		QTimer::singleShot(interval, this, SLOT(emitDataSlot()));;
		emit dataEmitSignal(databuffer[emitdataid]);
		emitdataid=(emitdataid+1)%databuffer.size();
		curtimestamp=nexttimestamp;
		nexttimestamp=loadData(_params,&(databuffer[curdataid]));
		curdataid=(curdataid+1)%databuffer.size();
	}
	else if(interval==0&&startflag)
	{
		while(interval==0)
		{
			emit dataEmitSignal(databuffer[emitdataid]);
			emitdataid=(emitdataid+1)%databuffer.size();
			nexttimestamp=loadData(_params,&(databuffer[curdataid]));
			curdataid=(curdataid+1)%databuffer.size();
			interval=nexttimestamp-curtimestamp;
		}
		if(interval>0)
		{
			QTimer::singleShot(interval, this, SLOT(emitDataSlot()));;
			emit dataEmitSignal(databuffer[emitdataid]);
			emitdataid=(emitdataid+1)%databuffer.size();
			curtimestamp=nexttimestamp;
			nexttimestamp=loadData(_params,&(databuffer[curdataid]));
			curdataid=(curdataid+1)%databuffer.size();
		}
		else
		{
			emit dataEmitErrorSignal();
		}
	}
	else
	{
		emit dataEmitErrorSignal();
	}
}

void Simulator::openSimulatorSlot()
{
	if(!openflag&&!startflag&&openSimulator(_params))
	{
		openflag=1;
		emit simulatorOpenSignal();
	}
	else
	{
		emit simulatorOpenErrorSignal();
	}
}

void Simulator::initialSimulatorSlot(long starttime, double rate)
{
	if(openflag&&!startflag)
	{
		curtimestamp=starttime;
		simrate=rate;
		while(1)
		{
			nexttimestamp=loadData(_params,&(databuffer[curdataid]));
			if(nexttimestamp<0)
			{
				emit simulatorInitialErrorSignal();
				break;
			}
			else if(nexttimestamp>curtimestamp)
			{
				emitdataid=curdataid;
				curdataid=(curdataid+1)%databuffer.size();
				curtimestamp=nexttimestamp;
				nexttimestamp=loadData(_params,&(databuffer[curdataid]));
				if(nexttimestamp<0)
				{
					emit simulatorInitialErrorSignal();
					break;
				}
				else
				{
					curdataid=(curdataid+1)%databuffer.size();
					emit simulatorInitialSignal(starttime);
					break;
				}
			}
		}
	}
	else
	{
		emit simulatorInitialErrorSignal();
	}
}

void Simulator::startSimulatorSlot()
{
	if(openflag&&!startflag)
	{
		startflag=1;
		int interval=int((nexttimestamp-curtimestamp)*simrate+0.5);
		QTimer::singleShot(interval, this, SLOT(emitDataSlot()));;
		emit simulatorStartSignal();
	}
	else
	{
		emit simulatorStartErrorSignal();
	}
}

void Simulator::stopSimulatorSlot()
{
	if(openflag&&startflag)
	{
		startflag=0;
		emit simulatorStopSignal();
	}
	else
	{
		emit simulatorStopErrorSignal();
	}
}

void Simulator::closeSimulatorSlot()
{
	if(openflag&&!startflag&&closeSimulator(_params))
	{
		openflag=0;
		emit simulatorCloseSignal();
	}
	else
	{
		emit simulatorCloseErrorSignal();
	}
}

bool Simulator::connectOpenSimulatorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(openSimulatorSlot()));
}

bool Simulator::connectInitialSimulatorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(initialSimulatorSlot(long)));
}

bool Simulator::connectStartSimulationSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(startSimulatorSlot()));
}

bool Simulator::connectStopSimulatorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(stopSimulatorSlot()));
}

bool Simulator::connectCloseSimulatorSignal(QObject * sender, const char * signal)
{
	return connect(sender,signal,this,SLOT(closeSimulatorSlot()));
}

bool Simulator::disconnectOpenSimulatorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(openSimulatorSlot()));
}

bool Simulator::disconnectInitialSimulatorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(initialSimulatorSlot(long)));
}

bool Simulator::disconnectStartSimulationSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(startSimulatorSlot()));
}

bool Simulator::disconnectStopSimulatorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(stopSimulatorSlot()));
}

bool Simulator::disconnectCloseSimulatorSignal(QObject * sender, const char * signal)
{
	return disconnect(sender,signal,this,SLOT(closeSimulatorSlot()));
}

bool Simulator::connectSimulatorOpenSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorOpenSignal()),receiver,slot);
}

bool Simulator::connectSimulatorOpenErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorOpenErrorSignal()),receiver,slot);
}

bool Simulator::connectSimulatorInitialSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorInitialSignal(long)),receiver,slot);
}

bool Simulator::connectSimulatorInitialErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorInitialErrorSignal()),receiver,slot);
}

bool Simulator::connectSimulatorStartSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorStartSignal()),receiver,slot);
}

bool Simulator::connectSimulatorStartErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorStartErrorSignal()),receiver,slot);
}

bool Simulator::connectDataEmitSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataEmitSignal(void *)),receiver,slot);
}

bool Simulator::connectDataEmitErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(dataEmitErrorSignal()),receiver,slot);
}

bool Simulator::connectSimulatorStopSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorStopSignal()),receiver,slot);
}

bool Simulator::connectSimulatorStopErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorStopErrorSignal()),receiver,slot);
}

bool Simulator::connectSimulatorCloseSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorCloseSignal()),receiver,slot);
}

bool Simulator::connectSimulatorCloseErrorSlot(QObject * receiver, const char * slot)
{
	return connect(this,SIGNAL(simulatorCloseErrorSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorOpenSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorOpenSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorOpenErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorOpenErrorSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorInitialSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorInitialSignal(long)),receiver,slot);
}

bool Simulator::disconnectSimulatorInitialErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorInitialErrorSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorStartSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorStartSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorStartErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorStartErrorSignal()),receiver,slot);
}

bool Simulator::disconnectDataEmitSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataEmitSignal(void *)),receiver,slot);
}

bool Simulator::disconnectDataEmitErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(dataEmitErrorSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorStopSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorStopSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorStopErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorStopErrorSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorCloseSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorCloseSignal()),receiver,slot);
}

bool Simulator::disconnectSimulatorCloseErrorSlot(QObject * receiver, const char * slot)
{
	return disconnect(this,SIGNAL(simulatorCloseErrorSignal()),receiver,slot);
}
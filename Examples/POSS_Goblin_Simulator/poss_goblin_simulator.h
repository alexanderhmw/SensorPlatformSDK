#ifndef POSS_GOBLIN_SIMULATOR_H
#define POSS_GOBLIN_SIMULATOR_H

#include <QtGui/QMainWindow>
#include "ui_poss_goblin_simulator.h"

#include<Simulator\simulator.h>
#include<Processor\processor.h>
#include<Storage\storage.h>
#include<Storage\storagewidget.h>

#include<qthread.h>
#include<qstring.h>

class POSS_Goblin_Simulator : public QMainWindow
{
	Q_OBJECT

public:
	POSS_Goblin_Simulator(QWidget *parent = 0, Qt::WFlags flags = 0);
	~POSS_Goblin_Simulator();

private:
	Ui::POSS_Goblin_SimulatorClass ui;
public:
	Simulator * simulator;
	QThread simulatorthread;

	Processor * processor;
	QThread processorthread;

	Storage * processorstorage;
	StorageWidget * processorstoragewidget;
signals:
	void initialSimulatorSignal(long starttime);
public slots:
	void initialSimulatorSlot();
};

#endif // POSS_GOBLIN_SIMULATOR_H

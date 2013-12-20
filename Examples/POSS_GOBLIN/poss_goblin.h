#ifndef POSS_GOBLIN_H
#define POSS_GOBLIN_H

#include <QtGui/QMainWindow>
#include "ui_poss_goblin.h"

#include<Sensor\sensor.h>
#include<Sensor\sensorwidget.h>
#include<Storage\storage.h>
#include<Storage\storagewidget.h>

class POSS_GOBLIN : public QMainWindow
{
	Q_OBJECT

public:
	POSS_GOBLIN(QWidget *parent = 0, Qt::WFlags flags = 0);
	~POSS_GOBLIN();

private:
	Ui::POSS_GOBLINClass ui;

public:
	Q
};

#endif // POSS_GOBLIN_H

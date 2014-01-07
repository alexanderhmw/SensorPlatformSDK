#include "poss_goblin_simulator.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	POSS_Goblin_Simulator w;
	w.show();
	return a.exec();
}

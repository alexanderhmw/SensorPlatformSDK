#include "poss_goblin_collector.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	POSS_Goblin_Collector w;
	w.show();
	return a.exec();
}

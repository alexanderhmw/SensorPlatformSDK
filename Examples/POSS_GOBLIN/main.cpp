#include "poss_goblin.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	POSS_GOBLIN w;
	w.show();
	return a.exec();
}

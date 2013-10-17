#include "tsukuba.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Tsukuba w;
	w.show();
	return a.exec();
}

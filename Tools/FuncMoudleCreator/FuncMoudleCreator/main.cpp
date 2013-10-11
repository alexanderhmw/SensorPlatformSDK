#include "funcmoudlecreator.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FuncMoudleCreator w;
	w.show();
	return a.exec();
}

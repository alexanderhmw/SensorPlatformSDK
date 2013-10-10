#include "sensor_storage.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Sensor_Storage w;
	w.show();
	return a.exec();
}

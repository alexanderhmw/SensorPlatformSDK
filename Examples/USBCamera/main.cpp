#include "usbcamera.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	USBCamera w;
	w.show();
	return a.exec();
}

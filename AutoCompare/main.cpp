#include "autocompare.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoCompare w;
	w.show();
	return a.exec();
}

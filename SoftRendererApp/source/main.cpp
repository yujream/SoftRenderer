#include <QApplication>
#include "QuiSoftRendererMainWindow.h"

int main(int argc, char** argv)
{
	QApplication a(argc, argv);
	QuiSoftRendererMainWindow w;
	w.show();
	return a.exec();
}
#include <QApplication>
#include <iostream>

#include <editor/MainWindow.h>
#include <QString>

int main(int argc, char *argv[])
{
	//~ 	Q_INIT_RESOURCE(application);
	QApplication app(argc, argv);
	MainWindow mainWin;
	mainWin.show();
	return app.exec();
}

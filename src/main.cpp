#include <QApplication>
#include "../include/mainWindow.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	MainWindow * window = new MainWindow();
	
	window->setWindowTitle("TiffAnalyzer");
	window->resize(720, window->height());
	window->resize(1080, window->width());
	window->show();
	
	return app.exec();
}
#include <QApplication>
#include "../include/mainWindow.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	MainWindow * window = new MainWindow();
	
	window->setWindowTitle("TiffAnalyzer");
	window->resize(1920, 1080);
	window->showMaximized();
	
	return app.exec();
}
#include <QApplication>

#include <QNetworkAccessManager>

#include "../include/mainWindow.h"
#include "../include/logger.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	
	QNetworkAccessManager * httpManager = new QNetworkAccessManager();
	HttpClient * httpClient = new HttpClient(httpManager);
	
	QMainWindow * window = new MainWindow(httpClient);
	
	window->setWindowTitle("TiffAnalyzer");
	window->resize(1920, 1080);
	window->showMaximized();
	
	qInstallMessageHandler(Logger::loggingMesssageHandler);

	qInfo().noquote() << "Программа запущена";
	
	QObject::connect(&app, &QApplication::aboutToQuit, []() 
	{
		qInfo().noquote() << "Программа завершила работу\n";
    });
	
	return app.exec();
}
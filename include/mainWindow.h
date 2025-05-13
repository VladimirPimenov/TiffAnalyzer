#pragma once

#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>

#include <string>

class MainWindow: public QMainWindow
{
public:
	MainWindow();
	
private:
	QMenuBar * optionsMenu;
	QMenu * fileMenu;
	QAction * openImageAction; 
	QAction * saveImageAction;
	QAction * closeImageAction;
	QAction * exitAction;
	
	QString openImagePath;
	QString saveImagePath;
	
	void openImage();
	void saveImage();
	void closeImage();
	
	void createMenuBar();
	
	void callError(std::string errorText);
};
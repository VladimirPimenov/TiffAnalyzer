#pragma once

#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>

#include <string>

#include "../include/imageLabel.h"

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
	
	QScrollArea * scrollArea;
	
	ImageLabel * imageViewer;
	
	QString openImagePath;
	QString saveImagePath;
	
	void openImage();
	void saveImage();
	void closeImage();
	
	void createMenuBar();
	void createImagePanel();
	
	void callError(std::string errorText);
};
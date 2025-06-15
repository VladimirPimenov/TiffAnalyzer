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

#include "imageLabel.h"
#include "pixelStatusBar.h"

class MainWindow: public QMainWindow
{
public:
	MainWindow();
	
	PixelStatusBar * statusBar;
	
private:
	QMenuBar * optionsMenu;
	QMenu * fileMenu;
	QAction * openImageAction; 
	QAction * closeImageAction;
	QAction * exitAction;
	
	QMenu * displayModeMenu;
	QAction * grayscaleModeAction;
	QAction * rgbModeAction;
	
	QScrollArea * scrollArea;
	
	ImageLabel * imageViewer;
	
	QString openImagePath;
	
	void openImage();
	void openGrayscale();
	void openRgb();
	void closeImage();
	
	void createMenuBar();
	void createImagePanel();
	
	void callError(std::string errorText);
};
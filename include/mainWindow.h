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
#include <QHBoxLayout>

#include <string>

#include "imageLabel.h"
#include "histogramPanel.h"
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
	QAction * standartContrastingAction;
	QAction * histogramContrastingAction;
	
	QMenu * viewMenu;
	QAction * showHistogramAction;
	
	QWidget * centralWidget;
	QHBoxLayout * centralBox;
	
	QScrollArea * scrollArea;
	ImageLabel * imageViewer;
	
	HistogramPanel * histogramPanel;
	
	QString openImagePath;
	
	void openImage();
	void openGrayscale();
	void openRgb();
	void closeImage();
	
	void standartContrasting();
	void histogramContrasting();
	
	void showHistogram();
	
	void createCentralPanel();
	void createMenuBar();
	void createImagePanel();
	void createHistogramPanel();
	
	void callError(std::string errorText);
};
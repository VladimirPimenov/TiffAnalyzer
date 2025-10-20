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
#include <QVBoxLayout>
#include <QPushButton>

#include <string>

#include "imageLabel.h"
#include "pixelStatisticsPanel.h"
#include "contrastingPanel.h"

#include "pixelStatusBar.h"

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
	
	QMenu * viewModeMenu;
	QAction * grayscaleModeAction;
	QAction * rgbModeAction;
	
	QMenu * showMenu;
	QAction * showContrastingAction;
	QAction * showPixelStatAction;
	
	QWidget * centralWidget;
	QHBoxLayout * centralBox;
	
	QScrollArea * scrollArea;
	
	ImageLabel * imageViewer;	
	ContrastingPanel * contrastingPanel;
	PixelStatisticsPanel * pixelPanel;
	
	PixelStatusBar * statusBar;
	
	void openImage();
	void saveImage();
	void openGrayscale();
	void openRgb();
	void closeImage();
	
	void createCentralPanel();
	void createMenuBar();
	void createImagePanel();
	void createContrastingPanel();
	void createPixelPanel();
	
	void switchContrastingPanelVisible();
	void switchPixelPanelVisible();
};
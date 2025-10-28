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
#include "instrumentsPanel.h"

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
	
	QMenu * showMenu;
	QAction * showSpectralAction;
	
	QWidget * centralWidget;
	QHBoxLayout * centralBox;
	
	QScrollArea * scrollArea;
	
	ImageLabel * imageViewer;	
	InstrumentsPanel * instrumentsPanel;
	
	PixelStatusBar * statusBar;
	
	void openImage();
	void saveImage();
	void closeImage();
	
	void createCentralPanel();
	void createMenuBar();
	void createImagePanel();
	void createInstrumentsPanel();
	
	void switchSpectralPanelVisible();
};
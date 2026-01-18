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
#include <QMessageBox>

#include <string>
#include <QString>

#include "imageLabel.h"
#include "calibrationWindow.h"
#include "instrumentsPanel.h"
#include "snapshotLoadWindow.h"

#include "pixelStatusBar.h"

#include "spp.h"
#include "wavescaleTable.h"

#include "httpClient.h"

class MainWindow: public QMainWindow
{
public:
	MainWindow(HttpClient * httpClient);
	
	private:
	QMenuBar * optionsMenu;
	
	QMenu * fileMenu;
	QAction * openImageAction; 
	QAction * saveImageAction;
	QAction * closeImageAction;
	QAction * exitAction;
	
	QMenu * showMenu;
	QAction * showSpectralAction;
	
	QMenu * imageProcessingMenu;
	QAction * calibrationAction;
	QAction * loadSnapshotAction;
	
	QWidget * centralWidget;
	QHBoxLayout * centralBox;
	
	QScrollArea * scrollArea;
	
	ImageLabel * imageViewer;	
	CalibrationWindow * calibrationWindow;
	InstrumentsPanel * instrumentsPanel;
	SnapshotLoadWindow * snapshotLoadWindow;
	
	PixelStatusBar * statusBar;
	
	void openImage();
	void saveImage();
	void closeImage();
	void loadImagePassport(QString loadPath);
	void requestPassportPath();
	
	void openCalibrationWindow();
	void openShapshotLoadWindow();
	
	void createCentralPanel();
	void createMenuBar();
	void createImagePanel();
	void createInstrumentsPanel();
	
	void switchSpectralPanelVisible();
};
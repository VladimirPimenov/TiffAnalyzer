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
	
	QMenu * viewModeMenu;
	QAction * grayscaleModeAction;
	QAction * rgbModeAction;
	
	QVBoxLayout * instrumentsBox;
	QVBoxLayout * histogramBox;
	QVBoxLayout * contrastingBox;
	
	QPushButton * standartContrastingButton;
	QPushButton * histogramContrastingButton;
	QPushButton * resetContrastingButton;
	
	QMenu * showMenu;
	QAction * showInstrumentsAction;
	
	QWidget * centralWidget;
	QHBoxLayout * centralBox;
	
	QScrollArea * scrollArea;
	ImageLabel * imageViewer;
	
	HistogramPanel * histogramPanel;
	
	std::string openImagePath;
	
	void openImage();
	void openGrayscale();
	void openRgb();
	void closeImage();
	
	void standartContrasting();
	void histogramContrasting();
	void resetContrasting();
	
	void switchInstrumentsPanelVisible();
	
	void createCentralPanel();
	void createMenuBar();
	void createImagePanel();
	void createInstrumentsPanel();
	void createHistogramPanel();
	void createContrastingPanel();
	
	void callError(std::string errorText);
};
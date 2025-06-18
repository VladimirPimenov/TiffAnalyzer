#include <iostream>

#include "../../include/mainWindow.h"

MainWindow::MainWindow():QMainWindow()
{
	createMenuBar();
	
	statusBar = new PixelStatusBar();
	this->setStatusBar(statusBar);
	
	createCentralPanel();
	
	createHistogramPanel();
	createImagePanel();
}

void MainWindow::createMenuBar()
{
	fileMenu = new QMenu("Файл");
	openImageAction = fileMenu->addAction("Открыть");
	closeImageAction = fileMenu->addAction("Закрыть");
	exitAction = fileMenu->addAction("Выход",this, SLOT(close()));
	
	displayModeMenu = new QMenu("Режим отображения");
	grayscaleModeAction = displayModeMenu->addAction("Grayscale");
	rgbModeAction = displayModeMenu->addAction("RGB");
	
	displayModeMenu->setEnabled(false);
	
	viewMenu = new QMenu("Вид");
	showHistogramAction = viewMenu->addAction("Гистограмма");
	showHistogramAction->setCheckable(true);
	showHistogramAction->setChecked(true);
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	connect(grayscaleModeAction, &QAction::triggered, this, &MainWindow::openGrayscale);
	connect(rgbModeAction, &QAction::triggered, this, &MainWindow::openRgb);
	
	connect(showHistogramAction, &QAction::triggered, this, &MainWindow::showHistogram);
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(displayModeMenu);
	menuBar()->addMenu(viewMenu);
}

void MainWindow::createCentralPanel()
{
    centralWidget = new QWidget();
	this->setCentralWidget(centralWidget);
	centralBox = new QHBoxLayout(centralWidget);
}

void MainWindow::createImagePanel()
{
	imageViewer = new ImageLabel();
	scrollArea = new QScrollArea();
	
	imageViewer->setAlignment(Qt::AlignCenter);
	
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(imageViewer);
	
	imageViewer->statusBar = statusBar;
	imageViewer->histrogram = histogramPanel;
	
	centralBox->insertWidget(0, scrollArea);
}

void MainWindow::createHistogramPanel()
{
    histogramPanel = new HistogramPanel();
    
    centralBox->insertWidget(1, histogramPanel);
}

void MainWindow::callError(std::string errorText)
{
	QMessageBox errorWindow;
	
	errorWindow.setText(QString::fromStdString(errorText));
	errorWindow.setWindowTitle("TiffAnalyzer - ERROR");
	errorWindow.exec();
}

void MainWindow::openImage()
{
	openImagePath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "TIFF (*.tif *.tiff)");

	imageViewer->loadGrayscaleTIFF(openImagePath.toStdString());

    displayModeMenu->setEnabled(true);
}

void MainWindow::openGrayscale()
{
	imageViewer->loadGrayscaleTIFF(openImagePath.toStdString());
}

void MainWindow::openRgb()
{
	imageViewer->loadRgbTIFF(openImagePath.toStdString());
}

void MainWindow::showHistogram()
{
    if(showHistogramAction->isChecked())
		histogramPanel->setVisible(true);
	else
		histogramPanel->setVisible(false);
}

void MainWindow::closeImage()
{
    imageViewer->clearImageLabel();
    histogramPanel->clearHistogram();
    
    displayModeMenu->setEnabled(false);
}
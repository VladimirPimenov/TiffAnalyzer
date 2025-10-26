#include "../../include/mainWindow.h"

MainWindow::MainWindow():QMainWindow()
{
	createMenuBar();
	
	statusBar = new PixelStatusBar();
	this->setStatusBar(statusBar);
	
	createCentralPanel();
	
	createSpectralPanel();
	createImagePanel();
	
}

void MainWindow::createMenuBar()
{
	fileMenu = new QMenu("Файл");
	openImageAction = fileMenu->addAction("Открыть");
	saveImageAction = fileMenu->addAction("Сохранить");
	closeImageAction = fileMenu->addAction("Закрыть");
	exitAction = fileMenu->addAction("Выход",this, SLOT(close()));
	
	saveImageAction->setEnabled(false);
	closeImageAction->setEnabled(false);
	
	viewModeMenu = new QMenu("Отображение");
	grayscaleModeAction = viewModeMenu->addAction("Режим Grayscale");
	rgbModeAction = viewModeMenu->addAction("Режим RGB");
	
	viewModeMenu->setEnabled(false);
	
	showMenu = new QMenu("Вид");
	showSpectralAction = showMenu->addAction("Спектральная характеристика");
	showSpectralAction->setCheckable(true);
	showSpectralAction->setChecked(true);
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	connect(grayscaleModeAction, &QAction::triggered, this, &MainWindow::openGrayscale);
	connect(rgbModeAction, &QAction::triggered, this, &MainWindow::openRgb);
	
	connect(showSpectralAction, &QAction::triggered, this, &MainWindow::switchSpectralPanelVisible);
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(viewModeMenu);
	menuBar()->addMenu(showMenu);
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
	scrollArea->setAlignment(Qt::AlignCenter);
	
	imageViewer->linkPixelStatusBar(statusBar);
	imageViewer->linkSpectralPanel(spectralPanel);
	
	centralBox->insertWidget(0, scrollArea);
}

void MainWindow::createSpectralPanel()
{
    spectralPanel = new SpectralPanel();
    spectralPanel->setEnabled(false);
    
	centralBox->insertLayout(0, spectralPanel);
}

void MainWindow::openImage()
{
	std::string openImagePath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "TIFF (*.tif *.tiff)").toStdString();

	if(!openImagePath.empty())
	{
	    imageViewer->loadNewTIFF(openImagePath);
	
		saveImageAction->setEnabled(true);
		closeImageAction->setEnabled(true);
	
		viewModeMenu->setEnabled(true);
		
		spectralPanel->setEnabled(true);
	}
}

void MainWindow::saveImage()
{
    std::string saveFilePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "./", "BMP (*.bmp)").toStdString();

	if(!saveFilePath.empty())
	{
	    imageViewer->saveImageAsBmp(saveFilePath);
	}
}

void MainWindow::openGrayscale()
{
	imageViewer->loadGrayscaleTIFF();
}

void MainWindow::openRgb()
{
	imageViewer->loadRgbTIFF();
}

void MainWindow::switchSpectralPanelVisible()
{
    if(showSpectralAction->isChecked())
    	spectralPanel->setVisible(true);
	else
    	spectralPanel->setVisible(false);
}

void MainWindow::closeImage()
{
	if(imageViewer->hasImage())
	{
		saveImageAction->setEnabled(false);
		closeImageAction->setEnabled(false);
	
	    imageViewer->clearImageLabel();
    
    	viewModeMenu->setEnabled(false);
    	
    	spectralPanel->setEnabled(false);
	}
}
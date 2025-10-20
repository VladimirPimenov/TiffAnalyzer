#include "../../include/mainWindow.h"

MainWindow::MainWindow():QMainWindow()
{
	createMenuBar();
	
	statusBar = new PixelStatusBar();
	this->setStatusBar(statusBar);
	
	createCentralPanel();
	
	createContrastingPanel();
	createPixelPanel();
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
	showContrastingAction = showMenu->addAction("Панель контрастирования");
	showPixelStatAction = showMenu -> addAction("Характеристика пикселя");
	showContrastingAction->setCheckable(true);
	showContrastingAction->setChecked(true);
	showPixelStatAction->setCheckable(true);
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	connect(grayscaleModeAction, &QAction::triggered, this, &MainWindow::openGrayscale);
	connect(rgbModeAction, &QAction::triggered, this, &MainWindow::openRgb);
	
	connect(showContrastingAction, &QAction::triggered, this, &MainWindow::switchContrastingPanelVisible);
	connect(showPixelStatAction, &QAction::triggered, this, &MainWindow::switchPixelPanelVisible);
	
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
	
	imageViewer->linkPixelStatusBar(statusBar);
	imageViewer->linkContrastingPanel(contrastingPanel);
	imageViewer->linkPixelPanel(pixelPanel);
	
	centralBox->insertWidget(0, scrollArea);
}

void MainWindow::createContrastingPanel()
{	
	contrastingPanel = new ContrastingPanel();
	contrastingPanel->setEnabled(false);
	
	centralBox->insertLayout(0, contrastingPanel);
}

void MainWindow::createPixelPanel()
{
    pixelPanel = new PixelStatisticsPanel();
    
    centralBox->insertLayout(1, pixelPanel);
    
    pixelPanel->setVisible(false);
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
		
		contrastingPanel->setEnabled(true);
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

void MainWindow::switchContrastingPanelVisible()
{
    if(showContrastingAction->isChecked())
    	contrastingPanel->setVisible(true);
	else
    	contrastingPanel->setVisible(false);
}

void MainWindow::switchPixelPanelVisible()
{
    if(showPixelStatAction->isChecked())
        pixelPanel->setVisible(true);
    else
        pixelPanel->setVisible(false);
}

void MainWindow::closeImage()
{
	if(imageViewer->hasImage())
	{
		saveImageAction->setEnabled(false);
		closeImageAction->setEnabled(false);
	
	    imageViewer->clearImageLabel();
    
    	viewModeMenu->setEnabled(false);
    	
    	contrastingPanel->setEnabled(false);
	}
}
#include "../../include/mainWindow.h"

MainWindow::MainWindow():QMainWindow()
{
	createMenuBar();
	
	statusBar = new PixelStatusBar();
	this->setStatusBar(statusBar);
	
	createCentralPanel();
	
	createInstrumentsPanel();
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
	
	showMenu = new QMenu("Вид");
	showSpectralAction = showMenu->addAction("Панель инструментов");
	showSpectralAction->setCheckable(true);
	showSpectralAction->setChecked(true);
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	connect(showSpectralAction, &QAction::triggered, this, &MainWindow::switchSpectralPanelVisible);
	
	menuBar()->addMenu(fileMenu);
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
	imageViewer->linkInstrumentsPanel(instrumentsPanel);
	
	centralBox->insertWidget(0, scrollArea);
}

void MainWindow::createInstrumentsPanel()
{
    instrumentsPanel = new InstrumentsPanel();
    instrumentsPanel->setEnabled(false);
    
	centralBox->insertLayout(0, instrumentsPanel);
}

void MainWindow::openImage()
{
	std::string openImagePath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "TIFF (*.tif *.tiff)").toStdString();

	if(!openImagePath.empty())
	{
	    imageViewer->loadTIFF(openImagePath);
	
		saveImageAction->setEnabled(true);
		closeImageAction->setEnabled(true);
	
		instrumentsPanel->setEnabled(true);
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

void MainWindow::switchSpectralPanelVisible()
{
    if(showSpectralAction->isChecked())
    	instrumentsPanel->setVisible(true);
	else
    	instrumentsPanel->setVisible(false);
}

void MainWindow::closeImage()
{
	if(imageViewer->hasImage())
	{
		saveImageAction->setEnabled(false);
		closeImageAction->setEnabled(false);
	
	    imageViewer->clearImageLabel();
    
    	instrumentsPanel->setEnabled(false);
	}
}
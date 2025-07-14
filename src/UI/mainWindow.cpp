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
	
	viewModeMenu = new QMenu("Отображение");
	grayscaleModeAction = viewModeMenu->addAction("Режим Grayscale");
	rgbModeAction = viewModeMenu->addAction("Режим RGB");
	
	viewModeMenu->setEnabled(false);
	
	showMenu = new QMenu("Вид");
	showInstrumentsAction = showMenu->addAction("Панель инструментов");
	showInstrumentsAction->setCheckable(true);
	showInstrumentsAction->setChecked(true);
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	connect(grayscaleModeAction, &QAction::triggered, this, &MainWindow::openGrayscale);
	connect(rgbModeAction, &QAction::triggered, this, &MainWindow::openRgb);
	
	connect(showInstrumentsAction, &QAction::triggered, this, &MainWindow::switchInstrumentsPanelVisible);
	
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
	
	imageViewer->statusBar = statusBar;
	imageViewer->histrogram = histogramPanel;
	
	centralBox->insertWidget(0, scrollArea);
}

void MainWindow::createInstrumentsPanel()
{
	instrumentsBox = new QVBoxLayout();

    createHistogramPanel();
    
    createContrastingPanel();
    
    instrumentsBox->addStretch(1);
    
    centralBox->insertLayout(0, instrumentsBox);
}

void MainWindow::createContrastingPanel()
{
	contrastingBox = new QVBoxLayout();

	QLabel * text = new QLabel("Контрастирование");

	standartContrastingButton = new QPushButton("Контрастирование");
	histogramContrastingButton = new QPushButton("Контрастирование по гистограмме");
	resetContrastingButton = new QPushButton("Сбросить контрастирование");

	standartContrastingButton->setEnabled(false);
	histogramContrastingButton->setEnabled(false);
	resetContrastingButton->setEnabled(false);

    connect(standartContrastingButton, &QPushButton::clicked, this, &MainWindow::standartContrasting);
	connect(histogramContrastingButton, &QPushButton::clicked, this, &MainWindow::histogramContrasting);
	connect(resetContrastingButton, &QPushButton::clicked, this, &MainWindow::resetContrasting);
	
	contrastingBox->addWidget(text, Qt::AlignLeft);
	contrastingBox->addWidget(standartContrastingButton);
	contrastingBox->addWidget(histogramContrastingButton);
	contrastingBox->addWidget(resetContrastingButton);
	
	instrumentsBox->addLayout(contrastingBox);
}

void MainWindow::createHistogramPanel()
{
	histogramBox = new QVBoxLayout();
    histogramPanel = new HistogramPanel();
    
    QLabel * text = new QLabel("Гистограмма изображения");
    
    histogramBox->addWidget(text, Qt::AlignLeft);
    histogramBox->addWidget(histogramPanel);
    
    instrumentsBox->addLayout(histogramBox);
    
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
	std::string openImagePath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "TIFF (*.tif *.tiff)").toStdString();

	if(!openImagePath.empty())
	{
	    imageViewer->loadNewTIFF(openImagePath);
	
		saveImageAction->setEnabled(true);
		closeImageAction->setEnabled(true);
	
		viewModeMenu->setEnabled(true);
		standartContrastingButton->setEnabled(true);
		histogramContrastingButton->setEnabled(true);
		resetContrastingButton->setEnabled(true);
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

void MainWindow::standartContrasting()
{
    imageViewer->standartContrasting();
}

void MainWindow::histogramContrasting()
{
    imageViewer->histogramContrasting();
}

void MainWindow::resetContrasting()
{
    imageViewer->resetContrasting();
}

void MainWindow::switchInstrumentsPanelVisible()
{
    if(showInstrumentsAction->isChecked())
    {
	    histogramPanel->setVisible(true);
	    standartContrastingButton->setVisible(true);
    	histogramContrastingButton->setVisible(true);
    	resetContrastingButton->setVisible(true);
    }
	else
	{
	    histogramPanel->setVisible(false);
    	standartContrastingButton->setVisible(false);
    	histogramContrastingButton->setVisible(false);
    	resetContrastingButton->setVisible(false);
	}
}

void MainWindow::closeImage()
{
	if(imageViewer->hasImage())
	{
		saveImageAction->setEnabled(false);
		closeImageAction->setEnabled(false);
	
	    imageViewer->clearImageLabel();
		histogramPanel->clearHistogram();
    
    	viewModeMenu->setEnabled(false);
    	standartContrastingButton->setEnabled(false);
    	histogramContrastingButton->setEnabled(false);
    	resetContrastingButton->setEnabled(false);
	}
}
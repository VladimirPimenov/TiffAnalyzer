#include "../../include/mainWindow.h"

MainWindow::MainWindow(HttpClient * httpClient):QMainWindow()
{
	createMenuBar();
	
	calibrationWindow = new CalibrationWindow(this);
	snapshotLoadWindow = new SnapshotLoadWindow(this, httpClient);
	
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
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	showMenu = new QMenu("Вид");
	showSpectralAction = showMenu->addAction("Панель инструментов");
	showSpectralAction->setCheckable(true);
	showSpectralAction->setChecked(true);
	
	connect(showSpectralAction, &QAction::triggered, this, &MainWindow::switchSpectralPanelVisible);
	
	imageProcessingMenu = new QMenu("Обработка");
	calibrationAction = imageProcessingMenu->addAction("Калибровка");
	loadSnapshotAction = imageProcessingMenu->addAction("Загрузить данные снимка");
	
	connect(calibrationAction, &QAction::triggered, this, &MainWindow::openCalibrationWindow);
	connect(loadSnapshotAction, &QAction::triggered, this, &MainWindow::openShapshotLoadWindow);
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(showMenu);
	menuBar()->addMenu(imageProcessingMenu);
}

void MainWindow::createCentralPanel()
{
    centralWidget = new QWidget();
    
	this->setCentralWidget(centralWidget);
	
	centralBox = new QHBoxLayout(centralWidget);
}

void MainWindow::createImagePanel()
{
	imageViewer = new ImageLabel(statusBar, instrumentsPanel);
	scrollArea = new QScrollArea();
	
	imageViewer->setAlignment(Qt::AlignCenter);
	
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(imageViewer);
	scrollArea->setAlignment(Qt::AlignCenter);
	
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
	QString openImagePath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "TIFF (*.tif *.tiff)");

	if(openImagePath.isEmpty())
		return;

	qInfo().noquote() << "Открыто изображение " + openImagePath;
	
	imageViewer->loadTIFF(openImagePath);
	
	QString sppPath = openImagePath.mid(0, openImagePath.length() - 3) + "spp";
	loadImagePassport(sppPath);

	saveImageAction->setEnabled(true);
	closeImageAction->setEnabled(true);

	instrumentsPanel->setEnabled(true);
}

void MainWindow::loadImagePassport(QString sppPath)
{
    Spp spp = Spp(sppPath);
    
    if(!spp.isReaded)
    {
        qWarning().noquote() << "Не найден файл паспорта изображения";
        
        calibrationWindow->setDateTime(QDateTime::currentDateTime());
        snapshotLoadWindow->setLoadDateTime(QDateTime::currentDateTime());
        
        imageViewer->setWavescaleTable(new WavescaleTable(0));
        
        requestPassportPath();
    }
    else
    {
        qInfo().noquote() << "Загружен файл паспорта изображения " + sppPath; 
        
		WavescaleTable * waveTable = new WavescaleTable(spp.channelsCount);
		waveTable->loadFromSppFile(spp);
		
		imageViewer->setWavescaleTable(waveTable);
		
		calibrationWindow->setDateTime(spp.dateAcquired);
		snapshotLoadWindow->setLoadDateTime(spp.dateAcquired);
    }
    
}

void MainWindow::requestPassportPath()
{
    auto userAnswer = QMessageBox::question(this, "Выберите файл spp", "Файл .spp не найден. Выбрать путь вручную?",
                                            QMessageBox::Yes | QMessageBox::No);

    if(userAnswer == QMessageBox::Yes)
    {
        QString sppPath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "SPP (*.spp)");
        
        loadImagePassport(sppPath);
    }
}

void MainWindow::saveImage()
{
    QString saveImagePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "./", "Bmp (*.bmp)");

	if(saveImagePath.isEmpty())
		return;

	imageViewer->saveImageAsBmp(saveImagePath.toStdString());
	
	qInfo().noquote() << "Сохранено изображение " + saveImagePath;
}

void MainWindow::openCalibrationWindow()
{
    calibrationWindow->show();
}

void MainWindow::openShapshotLoadWindow()
{
    snapshotLoadWindow->show();
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
    	qInfo().noquote() << "Изображение закрыто";
    	
		saveImageAction->setEnabled(false);
		closeImageAction->setEnabled(false);
	
	    imageViewer->clearImageLabel();
    
    	instrumentsPanel->setEnabled(false);
    	
	}
}
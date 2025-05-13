#include "../include/mainWindow.h"

MainWindow::MainWindow():QMainWindow()
{
	createMenuBar();
}

void MainWindow::createMenuBar()
{
	fileMenu = new QMenu("Файл");
	
	openImageAction = fileMenu->addAction("Открыть");
	saveImageAction = fileMenu->addAction("Сохранить");
	closeImageAction = fileMenu->addAction("Закрыть");
	exitAction = fileMenu->addAction("Выход",this, SLOT(close()));
	
	connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);
	connect(saveImageAction, &QAction::triggered, this, &MainWindow::saveImage);
	connect(closeImageAction, &QAction::triggered, this, &MainWindow::closeImage);
	
	menuBar()->addMenu(fileMenu);
	
}

void MainWindow::callError(std::string errorText)
{
	QMessageBox errorWindow;
	errorWindow.setText(QString::fromStdString(errorText));
	errorWindow.setWindowTitle("BMPEditor - ERROR");
	errorWindow.exec();
}

void MainWindow::openImage()
{
	openImagePath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "TIFF (*.tiff)");
}
void MainWindow::saveImage()
{
	saveImagePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "./output.tiff", "TIFF (*.tiff)");
}
void MainWindow::closeImage(){}
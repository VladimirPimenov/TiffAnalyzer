#include "../../include/imageLabel.h"
#include <iostream>
#include <fstream>

ImageLabel::ImageLabel(): QLabel(){}

void ImageLabel::loadTIFF(std::string loadPath, int channelNumber)
{
	tiffLoadPath = loadPath;
	
	tiffImage.loadTiffMetadata(tiffLoadPath);
	
	openChannelSelectionWindow(tiffImage.channelsCount);
}

void ImageLabel::openChannelSelectionWindow(int channelsCount)
{
	channelSelectionWindow = new QDialog(this);

	channelSelectionWindow->setWindowTitle("Выберите канал");
	channelSelectionWindow->resize(500, channelSelectionWindow->width());	
	channelSelectionWindow->resize(50, channelSelectionWindow->height());	
	channelSelectionWindow->setWindowModality(Qt::WindowModality::WindowModal);
	
	okButton = new QPushButton();
	
	okButton->setText("Загрузить канал");
	connect(okButton, &QPushButton::clicked, this, &ImageLabel::channelSelectedEventHandler);
	
    channelsList = new QComboBox();
    
	for(int channelNumber = 1; channelNumber < channelsCount; channelNumber++)
	{
	    channelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	}
	
	widgetsBox = new QVBoxLayout(channelSelectionWindow);
	widgetsBox->addWidget(channelsList);
	widgetsBox->addWidget(okButton);
	
	channelSelectionWindow->show();
}

void ImageLabel::updateImage()
{
	image = new QImage(tiffImage.width, tiffImage.height, QImage::Format_RGB888);
	
	for(int y = 0; y < tiffImage.height; y++)
	{
		for(int x = 0; x < tiffImage.width; x++)
		{
			(*image).setPixel(x, y, qRgb(tiffImage.pixels[y][x], tiffImage.pixels[y][x], tiffImage.pixels[y][x]));
		}
	}
	
	setPixmap(QPixmap::fromImage(*image));
}

void ImageLabel::clearImageLabel()
{
    image = nullptr;
	this->clear();
}

void ImageLabel::channelSelectedEventHandler()
{
    int channel = channelsList->currentText().toInt();
    
    channelSelectionWindow->close();
    
	tiffImage.loadChannel(tiffLoadPath, channel - 1);
	updateImage();
}
#include "../include/imageLabel.h"
#include <iostream>
#include <fstream>

ImageLabel::ImageLabel(): QLabel(){}

void ImageLabel::loadTIFF(std::string loadPath, int channelNumber)
{
	tiffImage.loadTiffMetadata(loadPath);
	tiffImage.loadChannel(loadPath, 0);
	updateImage();
}

void ImageLabel::updateImage()
{
	image = new QImage(tiffImage.width, tiffImage.height, QImage::Format_RGB888);
	
	for(int y = 0; y < tiffImage.height; y++)
	{
		for(int x = 0; x < tiffImage.width; x++)
		{
			(*image).setPixel(x, y, qRgb(tiffImage.imageData[y][x].red, tiffImage.imageData[y][x].green, tiffImage.imageData[y][x].blue));
		}
	}
	setPixmap(QPixmap::fromImage(*image));

}

void ImageLabel::clearImageLabel()
{
    image = nullptr;
	this->clear();
}

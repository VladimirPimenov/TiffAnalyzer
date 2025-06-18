#include "../../include/imageLabel.h"
#include <iostream>

ImageLabel::ImageLabel(): QLabel()
{
    this->setMouseTracking(true);
    
    painter = new ImagePainter();
}

void ImageLabel::loadGrayscaleTIFF(std::string loadPath)
{
	tiffLoadPath = loadPath;
	
	tiffImage = new TIFF();
	tiffImage->loadTiffMetadata(tiffLoadPath);
	
	openGrayscaleSelectionWindow(tiffImage->channelsCount);
}

void ImageLabel::loadRgbTIFF(std::string loadPath)
{
	tiffLoadPath = loadPath;
	
	tiffImage->loadTiffMetadata(tiffLoadPath);
	
    openRgbSelectionWindow(tiffImage->channelsCount);
}

void ImageLabel::openGrayscaleSelectionWindow(int channelsCount)
{
	channelSelector = new ChannelSelectionWindow(this);
	channelSelector->createGrayscaleChannelSelector(channelsCount);
	
	channelSelector->setChannelSelectedEvent([this](){channelsSelectedEvent(); });
	
	channelSelector->show();
}

void ImageLabel::openRgbSelectionWindow(int channelsCount)
{
    channelSelector = new ChannelSelectionWindow(this);
    channelSelector->createRgbChannelSelector(channelsCount);
	
	channelSelector->setChannelSelectedEvent([this](){channelsSelectedEvent(); });
	
	channelSelector->show();
}

void ImageLabel::updateImage()
{
	image = new QImage(tiffImage->width, tiffImage->height, QImage::Format_RGB888);
	
	painter->paintImage(tiffImage, image);
	
	setPixmap(QPixmap::fromImage(*image));
	
	histrogram->updateHistogram(tiffImage);
}

void ImageLabel::clearImageLabel()
{
	this->clear();
    image = nullptr;
    
    tiffImage->~TIFF();
}

void ImageLabel::channelsSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    tiffImage->loadRgb(tiffLoadPath, channels);
    updateImage();
}

void ImageLabel::mouseMoveEvent(QMouseEvent * event)
{
	if(image != nullptr )
	{
		int x = event->pos().rx() - (this->width() - image->width()) / 2;
		int y = event->pos().ry() - (this->height() - image->height()) / 2;
		
		if(x >= 0 && y >= 0 && x < image->width() && y < image->height())
		{
			Pixel16bit pixel = tiffImage->pixels[y][x];
			
			Pixel16bit normalizedPixel = {qRed(image->pixel(x, y)), qGreen(image->pixel(x, y)), qBlue(image->pixel(x, y))};
			
			statusBar->updateInfo(x, y, pixel, normalizedPixel);
		}
	}
	else
	{
		statusBar->clearInfo();
	}
}
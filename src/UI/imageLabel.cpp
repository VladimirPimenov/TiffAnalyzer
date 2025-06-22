#include "../../include/imageLabel.h"
#include <iostream>
#include <cmath>

ImageLabel::ImageLabel(): QLabel()
{
    this->setMouseTracking(true);
    
    painter = new ImagePainter();
}

void ImageLabel::loadGrayscaleTIFF(std::string loadPath)
{
	tiffLoadPath = loadPath;
	
	image16bit = new TIFF();
	image16bit->loadTiffMetadata(tiffLoadPath);
	
	openGrayscaleSelectionWindow(image16bit->channelsCount);
}

void ImageLabel::loadRgbTIFF(std::string loadPath)
{
	tiffLoadPath = loadPath;
	
	image16bit->loadTiffMetadata(tiffLoadPath);
	
    openRgbSelectionWindow(image16bit->channelsCount);
}

void ImageLabel::openGrayscaleSelectionWindow(int channelsCount)
{
	channelSelector = new ChannelSelectionWindow(this);
	channelSelector->createGrayscaleChannelSelector(channelsCount);
	
	channelSelector->setChannelSelectedEvent([this](){ grayScaleSelectedEvent(); });
	
	channelSelector->show();
}

void ImageLabel::openRgbSelectionWindow(int channelsCount)
{
    channelSelector = new ChannelSelectionWindow(this);
    channelSelector->createRgbChannelSelector(channelsCount);
	
	channelSelector->setChannelSelectedEvent([this](){rgbSelectedEvent(); });
	
	channelSelector->show();
}

void ImageLabel::standartContrasting()
{
    contrastingWin = new ContrastingWindow(this);
    
    contrastingWin->setContrastingEvent([this](){ standartContrastingEvent(); });
    
    if(image16bit->isGrayscale)
    	contrastingWin->createGrayscaleContrastingWindow();
    else
		contrastingWin->createRgbContrastingWindow();		
    
    contrastingWin->show();
}

void ImageLabel::updateImage()
{
	image8bit = new QImage(image16bit->width, image16bit->height, QImage::Format_RGB888);
	
	painter->paintImage(image16bit, image8bit, minNormalizationPixel, maxNormalizationPixel);
	
	setPixmap(QPixmap::fromImage(*image8bit));
	
	histrogram->updateHistogram(image16bit);
}

void ImageLabel::clearImageLabel()
{
	this->clear();
    image8bit = nullptr;
    
    image16bit->~TIFF();
}

void ImageLabel::resetContrasting()
{
    minNormalizationPixel = Pixel16bit 
    {
    	image16bit->minPixelValue,
    	image16bit->minPixelValue, 
    	image16bit->minPixelValue
	};
    maxNormalizationPixel = Pixel16bit 
    {
    	image16bit->maxPixelValue, 
    	image16bit->maxPixelValue, 
    	image16bit->maxPixelValue
	};
}

void ImageLabel::grayScaleSelectedEvent()
{   
    int channel = channelSelector->getSelectedChannels().red;
    
    channelSelector->close();
    
    image16bit->loadGrayscale(tiffLoadPath, channel);
    
    resetContrasting();
    
    updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    image16bit->loadRgb(tiffLoadPath, channels);
    
    resetContrasting();
    
    updateImage();
}

void ImageLabel::standartContrastingEvent()
{
    minNormalizationPixel = contrastingWin->getMinPixelParameters();
    maxNormalizationPixel = contrastingWin->getMaxPixelParameters();
    
    contrastingWin->close();
    
    updateImage();
}

void ImageLabel::histogramContrasting()
{
    
}

void ImageLabel::mouseMoveEvent(QMouseEvent * event)
{
	if(image8bit != nullptr)
	{
		int x = event->pos().rx() - (this->width() - image8bit->width()) / 2;
		int y = event->pos().ry() - (this->height() - image8bit->height()) / 2;
		
		if(x >= 0 && y >= 0 && x < image8bit->width() && y < image8bit->height())
		{
			Pixel16bit pixel = image16bit->pixels[y][x];
			
			Pixel16bit normalizedPixel = {qRed(image8bit->pixel(x, y)), qGreen(image8bit->pixel(x, y)), qBlue(image8bit->pixel(x, y))};
			
			statusBar->updateInfo(x, y, pixel, normalizedPixel);
		}
	}
	else
	{
		statusBar->clearInfo();
	}
}
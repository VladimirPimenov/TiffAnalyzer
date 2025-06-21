#include "../../include/imageLabel.h"
#include <iostream>

ImageLabel::ImageLabel(): QLabel()
{
    this->setMouseTracking(true);
    
    painter = new ImagePainter();
    
    resetContrasting();
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
    
    if(tiffImage->isGrayscale)
    	contrastingWin->createGrayscaleContrastingWindow();
    else
		contrastingWin->createRgbContrastingWindow();		
    
    contrastingWin->show();
}

void ImageLabel::updateImage()
{
	image = new QImage(tiffImage->width, tiffImage->height, QImage::Format_RGB888);
	
	painter->paintImage(tiffImage, image, minNormalizationPixel, maxNormalizationPixel);
	
	setPixmap(QPixmap::fromImage(*image));
	
	histrogram->updateHistogram(tiffImage);
}

void ImageLabel::clearImageLabel()
{
	this->clear();
    image = nullptr;
    
    tiffImage->~TIFF();
}

void ImageLabel::resetContrasting()
{
    minNormalizationPixel = Pixel16bit {0, 0, 0};
    maxNormalizationPixel = Pixel16bit {255, 255, 255};
}

void ImageLabel::grayScaleSelectedEvent()
{   
    int channel = channelSelector->getSelectedChannels().red;
    
    channelSelector->close();
    
    tiffImage->loadGrayscale(tiffLoadPath, channel);
    
    resetContrasting();
    
    updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    tiffImage->loadRgb(tiffLoadPath, channels);
    
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
#include "../../include/imageLabel.h"
#include <iostream>
#include <cmath>

ImageLabel::ImageLabel(): QLabel()
{
    this->setMouseTracking(true);
    
    image8bit = new QImage();
    
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

void ImageLabel::histogramContrasting()
{
    contrastingWin = new ContrastingWindow(this);
    
    contrastingWin->setContrastingEvent([this](){ histogramContrastingEvent(); });
    
    contrastingWin->createHistogramContrastingWindow();
    
    contrastingWin->show();
}

void ImageLabel::resetContrasting()
{
    resetContrastingParams();
    
    updateImage(minNormalizationPixel.red, maxNormalizationPixel.red);
}

void ImageLabel::updateImage(uint16_t min16bitValue = 0, uint16_t max16bitValue = 0)
{
	image8bit = new QImage(image16bit->width, image16bit->height, QImage::Format_RGB888);
	
	painter->paintImage(image16bit, image8bit, minNormalizationPixel, maxNormalizationPixel);
	
	setPixmap(QPixmap::fromImage(*image8bit));
	
	histrogram->updateHistogram(image16bit, min16bitValue, max16bitValue);
}

void ImageLabel::clearImageLabel()
{
	this->clear();
    image8bit = new QImage();
    
    image16bit->~TIFF();
}

void ImageLabel::resetContrastingParams()
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

bool ImageLabel::hasImage()
{
    return !image8bit->isNull();
}

void ImageLabel::grayScaleSelectedEvent()
{   
    int channel = channelSelector->getSelectedChannels().red;
    
    channelSelector->close();
    
    image16bit->loadGrayscale(tiffLoadPath, channel);
    
    resetContrastingParams();
    
    updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    image16bit->loadRgb(tiffLoadPath, channels);
    
    resetContrastingParams();
    
    updateImage();
}

void ImageLabel::standartContrastingEvent()
{
    minNormalizationPixel = contrastingWin->getMinPixelParameters();
    maxNormalizationPixel = contrastingWin->getMaxPixelParameters();
    
    contrastingWin->close();
    
    updateImage();
}

void ImageLabel::histogramContrastingEvent()
{
    float histogramCuttingPercent = contrastingWin->getHistogramCuttingPercent();
    uint16_t histogramMaxValue = histrogram->getMaxPixel16Value();
    
    uint16_t min16bitValue = histogramCuttingPercent * histogramMaxValue;
    uint16_t max16bitValue = (1 - histogramCuttingPercent) * histogramMaxValue;
    
    minNormalizationPixel = Pixel16bit
    {
        (uint16_t)(min16bitValue),
        (uint16_t)(min16bitValue),
        (uint16_t)(min16bitValue)
    };
    maxNormalizationPixel = Pixel16bit
    {
        (uint16_t)(max16bitValue),
        (uint16_t)(max16bitValue),
        (uint16_t)(max16bitValue)
    };
    
    contrastingWin->close();
    
    updateImage(min16bitValue, max16bitValue);
}

void ImageLabel::mouseMoveEvent(QMouseEvent * event)
{
	if(hasImage())
	{
		int x = event->pos().rx() - (this->width() - image8bit->width()) / 2;
		int y = event->pos().ry() - (this->height() - image8bit->height()) / 2;
		
		if(x >= 0 && y >= 0 && x < image8bit->width() && y < image8bit->height())
		{
			Pixel16bit pixel = image16bit->pixels[y][x];
			
			Pixel16bit normalizedPixel = 
			{
				(uint16_t)qRed(image8bit->pixel(x, y)), 
				(uint16_t)qGreen(image8bit->pixel(x, y)), 
				(uint16_t)qBlue(image8bit->pixel(x, y))
			};
			
			statusBar->updateInfo(x, y, pixel, normalizedPixel);
		}
	}
	else
	{
		statusBar->clearInfo();
	}
}
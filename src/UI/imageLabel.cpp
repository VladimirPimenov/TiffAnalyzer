#include "../../include/imageLabel.h"

ImageLabel::ImageLabel(): QLabel(){}

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
	
	channelSelector->setChannelSelectedEvent([this](){grayscaleSelectedEvent(); });
	
	channelSelector->show();
}

void ImageLabel::openRgbSelectionWindow(int channelsCount)
{
    channelSelector = new ChannelSelectionWindow(this);
    channelSelector->createRgbChannelSelector(channelsCount);
	
	channelSelector->setChannelSelectedEvent([this](){rgbSelectedEvent(); });
	
	channelSelector->show();
}

void ImageLabel::updateImage()
{
	PixelsNormalizer::normalizePixelValues(tiffImage);

	image = new QImage(tiffImage->width, tiffImage->height, QImage::Format_RGB888);
	
	for(int y = 0; y < tiffImage->height; y++)
	{
		for(int x = 0; x < tiffImage->width; x++)
		{
			(*image).setPixel(x, y, qRgb(tiffImage->pixels[y][x].red, tiffImage->pixels[y][x].green, tiffImage->pixels[y][x].blue));
		}
	}
	
	setPixmap(QPixmap::fromImage(*image));
}

void ImageLabel::grayscaleSelectedEvent()
{
    int channel = channelSelector->getSelectedChannels().red;
    
    channelSelector->close();
    
	tiffImage->loadGrayscale(tiffLoadPath, channel);
	updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    tiffImage->loadRgb(tiffLoadPath, channels);
    updateImage();
}


void ImageLabel::clearImageLabel()
{
	this->clear();
    image = nullptr;
    
    tiffImage->~TIFF();
}
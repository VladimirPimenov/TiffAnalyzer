#include "../../include/imageLabel.h"
#include "../../include/sppReader.h"

#include <cmath>

ImageLabel::ImageLabel(): QLabel()
{
    this->setMouseTracking(true);
    
    image8bit = new QImage();
    
    painter = new ImagePainter();
    
    createContextMenu();
}

void ImageLabel::createContextMenu()
{
    contextMenu = new QMenu();
    
    QAction * channelsInfoAction = contextMenu->addAction("Данные каналов");
    
    connect(channelsInfoAction, &QAction::triggered, this, &ImageLabel::showChannelsInfo);
}

void ImageLabel::loadNewTIFF(std::string loadPath)
{
    tiffPath = loadPath;
    
    image16bit = new TIFF();
    image16bit->loadTiffMetadata(tiffPath);
    
    sppTable = new SppTable(image16bit->channelsCount, 3);
    std::string sppPath = tiffPath.substr(0, tiffPath.length() - 3) + "spp";
    sppTable->loadSppFromFile(sppPath);
    
    loadGrayscaleTIFF();
}

void ImageLabel::loadGrayscaleTIFF()
{
    openGrayscaleSelectionWindow(image16bit->channelsCount);
}

void ImageLabel::loadRgbTIFF()
{
    openRgbSelectionWindow(image16bit->channelsCount);
}

void ImageLabel::saveImageAsBmp(std::string savePath)
{
    BMP * bmp = new BMP();
    
    ImageConverter::convertQImageToBmp(image8bit, bmp);
    
    bmp->save(savePath);
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

void ImageLabel::showChannelsInfo()
{
    sppTable->show();
}

bool ImageLabel::hasImage()
{
    return !image8bit->isNull();
}

void ImageLabel::grayScaleSelectedEvent()
{   
    int channel = channelSelector->getSelectedChannels().red;
    
    channelSelector->close();
    
    image16bit->loadGrayscale(tiffPath, channel);
    
    resetContrastingParams();
    
    updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    image16bit->loadRgb(tiffPath, channels);
    
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
    float leftCuttingPersent = contrastingWin->getLeftCuttingPercent();
    float rightCuttingPersent = contrastingWin->getRightCuttingPercent();
    
    uint16_t min16bitValue = 0;
    uint16_t max16bitValue = 0;
    
    int leftCuttingCount = image8bit->width() * image8bit->height() * leftCuttingPersent;
    int rightCuttingCount = image8bit->width() * image8bit->height() * rightCuttingPersent;
    
    int currentCount = 0;
    for(int x = 0; x < 65535; x++)
    {
        currentCount += histrogram->getColumnValue(x);
        
        if(currentCount >= leftCuttingCount)
        {
            min16bitValue = x;
            break;
        }
    }
    
    currentCount = 0;
    for(int x = 65535; x > 0; x--)
    {
        currentCount += histrogram->getColumnValue(x);
        
        if(currentCount >= rightCuttingCount)
        {
            max16bitValue = x;
            break;
        }
    }
    
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

void ImageLabel::mouseReleaseEvent(QMouseEvent * event)
{
    if(hasImage() 
    && event->button() == Qt::RightButton)
    {
        QPoint mousePos = mapToGlobal(event->pos());
		contextMenu->move(mousePos.rx(), mousePos.ry());
        
        contextMenu->show();
    }
}
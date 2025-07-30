#include "../../include/imageLabel.h"
#include "../../include/sppReader.h"

#include <QMessageBox>
#include <QFileDialog>

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
    
    loadSppTable();
    
    RgbChannels defaultChannels = {55, 29, 14};
    float defaultLeftCuttingPercent = 2.0f;
    float defaultRightCuttingPercent = 2.0f;
    
    image16bit->loadRgb(tiffPath, defaultChannels);
    
    resetContrastingParams();
    histrogram->updateHistogram(image16bit);
    
    uint16_t min16bitValue = findMinContrasingValue(defaultLeftCuttingPercent);
    uint16_t max16bitValue = findMaxContrasingValue(defaultRightCuttingPercent);
    
    painter->setNormalization(min16bitValue, max16bitValue);
    histrogram->setCutting(min16bitValue, max16bitValue);
    
    updateImage();
}

void ImageLabel::loadSppTable()
{
    sppTable = new SppTable(image16bit->channelsCount, 3);
    std::string sppPath = tiffPath.substr(0, tiffPath.length() - 3) + "spp";
    sppTable->loadSppFromFile(sppPath);
    
    if(!sppTable->isSppReaded())
        requestSppFilePath();
}

void ImageLabel::requestSppFilePath()
{
    auto userAnswer = QMessageBox::question(this, "Выберите файл spp", "Файл .spp не найден. Выбрать путь вручную?",
                                            QMessageBox::Yes | QMessageBox::No);

    if(userAnswer == QMessageBox::Yes)
    {
        std::string sppPath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "SPP (*.spp)").toStdString();
        
        sppTable->loadSppFromFile(sppPath);
    }
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
    
    updateImage();
}

void ImageLabel::updateImage()
{
	image8bit = new QImage(image16bit->width, image16bit->height, QImage::Format_RGB888);
	
	painter->paintImage(image16bit, image8bit);
	
	setPixmap(QPixmap::fromImage(*image8bit));
	
	histrogram->updateHistogram(image16bit);
}

void ImageLabel::clearImageLabel()
{
	this->clear();
    image8bit = new QImage();
    
    image16bit->~TIFF();
}

void ImageLabel::resetContrastingParams()
{
    painter->setNormalization(
        image16bit->minPixelValue,
        image16bit->maxPixelValue);
        
    histrogram->setCutting(
        image16bit->minPixelValue, 
        image16bit->maxPixelValue);
}

uint16_t ImageLabel::findMinContrasingValue(float leftCuttingPercent)
{
    int leftCuttingCount = image16bit->width * image16bit->height * leftCuttingPercent / 100;
    
    int currentCount = 0;
    for(int x = 0; x < 65535; x++)
    {
        currentCount += histrogram->getColumnValue(x);
        
        if(currentCount >= leftCuttingCount)
        {
            return x;
        }
    }
}

uint16_t ImageLabel::findMaxContrasingValue(float rightCuttingPercent)
{
    int rightCuttingCount = image16bit->width * image16bit->height * rightCuttingPercent / 100;
    
    int currentCount = 0;
    for(int x = 65535; x > 0; x--)
    {
        currentCount += histrogram->getColumnValue(x);
        
        if(currentCount >= rightCuttingCount)
        {
            return x;
        }
    }
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
    painter->setNormalization(
        contrastingWin->getMinPixelParameters(), 
        contrastingWin->getMaxPixelParameters());
    
    contrastingWin->close();
    
    updateImage();
}

void ImageLabel::histogramContrastingEvent()
{
    float leftCuttingPercent = contrastingWin->getLeftCuttingPercent();
    float rightCuttingPercent = contrastingWin->getRightCuttingPercent();
    
    uint16_t min16bitValue = findMinContrasingValue(leftCuttingPercent);
    uint16_t max16bitValue = findMaxContrasingValue(rightCuttingPercent);
    
    painter->setNormalization(min16bitValue, max16bitValue);

    contrastingWin->close();
    
    histrogram->setCutting(min16bitValue, max16bitValue);
    
    updateImage();
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
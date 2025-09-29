#include <QMessageBox>
#include <QFileDialog>

#include <cmath>

#include <iostream>

#include "../../include/imageLabel.h"
#include "../../include/histogramContrastingCalculator.h"
#include "../../include/pixelGraphicsWindow.h"

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
    QAction * pointCharacteristicAction = contextMenu->addAction("Спектральная характеристика точки");
    
    connect(channelsInfoAction, &QAction::triggered, this, &ImageLabel::showChannelsInfo);
    connect(pointCharacteristicAction, &QAction::triggered, this, &ImageLabel::showPointCharacteristic);
}

void ImageLabel::loadNewTIFF(std::string tiffPath)
{
    image16bit = new TIFF();
    image16bit->loadTiffMetadata(tiffPath);
    
    RgbChannels defaultChannels = {55, 29, 14};
    float defaultLeftCuttingPercent = 2.0f;
    float defaultRightCuttingPercent = 2.0f;
    
    image16bit->loadRgb(tiffPath, defaultChannels);
    
    loadSppTable();
    
    resetContrastingParams();
    
    histogram->setImage(image16bit);
    histogram->updateHistogram();
    
    Pixel16bit minCuttingPixel = HistogramContrastingCalculator::findMinContrasingValue(
                                                                defaultLeftCuttingPercent,
                                                                image16bit->width,
                                                                image16bit->height,
                                                                histogram);
    Pixel16bit maxCuttingPixel = HistogramContrastingCalculator::findMaxContrasingValue(
                                                                defaultRightCuttingPercent,
                                                                image16bit->width,
                                                                image16bit->height,
                                                                histogram);
    
    painter->setNormalization(minCuttingPixel, maxCuttingPixel);
    histogram->setCutting(minCuttingPixel, maxCuttingPixel);
    
    updateImage();
}

void ImageLabel::loadSppTable()
{
    sppTable = new SppTable(image16bit->channelsCount, 3);
    std::string sppPath = image16bit->getFilePath().substr(0, image16bit->getFilePath().length() - 3) + "spp";
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
	
	histogram->updateHistogram();
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
        
    histogram->setCutting(
        { image16bit->minPixelValue, image16bit->minPixelValue, image16bit->minPixelValue },
        { image16bit->maxPixelValue, image16bit->maxPixelValue, image16bit->maxPixelValue});
}

void ImageLabel::showChannelsInfo()
{
    sppTable->show();
}

void ImageLabel::showPointCharacteristic()
{
    if(sppTable->isSppReaded())
    {
        QPoint pos = mapFromGlobal(contextMenu->pos());

        PixelReader * pixelReader = new PixelReader();
        uint16_t * pixelValues = pixelReader->readPixelBrightness(pos.rx(), pos.ry(), image16bit);
        double * waveLengthValues = sppTable->getWaveLengthValues();
        
        PixelGraphicsWindow * pixelWindow = new PixelGraphicsWindow();
        
        pixelWindow->paintPixelGraphics(pixelValues, waveLengthValues, image16bit->channelsCount);
        pixelWindow->show();
        
        delete[] pixelValues;
        delete[] waveLengthValues;
    }
    else
    {
        requestSppFilePath();
    }
    
}

bool ImageLabel::hasImage()
{
    return !image8bit->isNull();
}

void ImageLabel::grayScaleSelectedEvent()
{   
    int channel = channelSelector->getSelectedChannels().red;
    
    channelSelector->close();
    
    image16bit->loadGrayscale(image16bit->getFilePath(), channel);
    
    resetContrastingParams();
    
	histogram->setImage(image16bit);
    updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    image16bit->loadRgb(image16bit->getFilePath(), channels);
    
    resetContrastingParams();
    
	histogram->setImage(image16bit);
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
    
    Pixel16bit minCuttingPixel = HistogramContrastingCalculator::findMinContrasingValue(
                                                                leftCuttingPercent,
                                                                image16bit->width,
                                                                image16bit->height,
                                                                histogram);
    Pixel16bit maxCuttingPixel = HistogramContrastingCalculator::findMaxContrasingValue(
                                                                rightCuttingPercent,
                                                                image16bit->width,
                                                                image16bit->height,
                                                                histogram);
    
    contrastingWin->close();
    
    painter->setNormalization(minCuttingPixel, maxCuttingPixel);
    histogram->setCutting(minCuttingPixel, maxCuttingPixel);
    
    updateImage();
}

void ImageLabel::mouseMoveEvent(QMouseEvent * event)
{
	if(hasImage())
	{
        QPoint mousePos = mapFromGlobal(QCursor::pos());
        int x = mousePos.rx();
        int y = mousePos.ry();
		
		if(x >= 0 && y >= 0 && x < image8bit->width() && y < image8bit->height())
		{
			Pixel16bit pixel = image16bit->getPixel(x, y);
			
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
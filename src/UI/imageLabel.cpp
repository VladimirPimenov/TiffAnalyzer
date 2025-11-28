#include "../../include/imageLabel.h"

ImageLabel::ImageLabel(): QLabel()
{
    this->setMouseTracking(true);
    
    image8bit = new QImage();
    
    painter = new ImagePainter();
    histogramCalculator = new HistogramCalculator();
    
    createContextMenu();
}

void ImageLabel::createContextMenu()
{
    contextMenu = new QMenu();
    
    QAction * channelsInfoAction = contextMenu->addAction("Данные каналов");
    
    connect(channelsInfoAction, &QAction::triggered, this, &ImageLabel::showChannelsInfo);
}

void ImageLabel::loadTIFF(std::string tiffPath)
{
    image16bit = new Tiff();
    image16bit->loadTiffMetadata(tiffPath);
    
    this->setFixedSize(image16bit->width, image16bit->height);
    
    RgbChannels defaultChannels = {55, 29, 14};
    float defaultLeftCuttingPercent = 2.0f;
    float defaultRightCuttingPercent = 2.0f;
    
    image16bit->loadRgb(tiffPath, defaultChannels);
    
    loadWavescaleTable();
    
    resetContrastingParams();
    
    histogramCalculator->calculateColorsFrequency(image16bit);
    
    Pixel16bit minCuttingPixel = histogramCalculator->findMinContrasingValue(
                                                        defaultLeftCuttingPercent,
                                                        image16bit->width,
                                                        image16bit->height);
    Pixel16bit maxCuttingPixel = histogramCalculator->findMaxContrasingValue(
                                                        defaultRightCuttingPercent,
                                                        image16bit->width,
                                                        image16bit->height);
    
    painter->setNormalization(minCuttingPixel, maxCuttingPixel);
    instrumentsPanel->setHistogramCutting(minCuttingPixel, maxCuttingPixel);
    
    updateImage();
}

void ImageLabel::loadWavescaleTable()
{
    wavescaleTable = new WavescaleTable(image16bit->channelsCount, 3);
    std::string sppPath = image16bit->getFilePath().substr(0, image16bit->getFilePath().length() - 3) + "spp";
    wavescaleTable->loadFromSppFile(sppPath);
    
    if(!wavescaleTable->hasData())
    {
        qWarning().noquote() << "Не найден файл паспорта изображения";
        requestSppFilePath();
    }
    else
        qInfo().noquote() << QString::fromStdString("Загружен файл паспорта изображения " + sppPath); 
}

void ImageLabel::requestSppFilePath()
{
    auto userAnswer = QMessageBox::question(this, "Выберите файл spp", "Файл .spp не найден. Выбрать путь вручную?",
                                            QMessageBox::Yes | QMessageBox::No);

    if(userAnswer == QMessageBox::Yes)
    {
        std::string sppPath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "SPP (*.spp)").toStdString();
        
        wavescaleTable->loadFromSppFile(sppPath);
        
        qInfo().noquote() << QString::fromStdString("Загружен файл паспорта изображения " + sppPath); 
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

void ImageLabel::linkInstrumentsPanel(InstrumentsPanel * instrumentsPanel)
{
    this->instrumentsPanel = instrumentsPanel;
    
    instrumentsPanel->setGrayscaleSelectedEvent([this](){ loadGrayscaleTIFF(); });
    instrumentsPanel->setRgbSelectedEvent([this](){ loadRgbTIFF(); });
    instrumentsPanel->setStandartContrastingEvent([this](){ standartContrasting(); });
	instrumentsPanel->setHistogramContrastingEvent([this](){ histogramContrasting(); });
	instrumentsPanel->setResetContrastingEvent([this](){ resetContrasting(); });
	instrumentsPanel->setColorChangedEvent([this](){ updateHistogram(); });
}

void ImageLabel::linkPixelStatusBar(PixelStatusBar * statusBar)
{
    this->statusBar = statusBar;
}

void ImageLabel::saveImageAsBmp(std::string savePath)
{
    Bmp * bmp = new Bmp();
    
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
	
	updateHistogram();
}

void ImageLabel::updateHistogram()
{
    QColor selectedColor = instrumentsPanel->getHistogramSelectedColor();
    
	instrumentsPanel->paintHistogramGraphics(histogramCalculator->getColorFrequency(selectedColor));
}

void ImageLabel::clearImageLabel()
{
	this->clear();
    image8bit = new QImage();
    
    image16bit->~Tiff();
}

void ImageLabel::resetContrastingParams()
{
    painter->setNormalization(
        image16bit->minPixelValue,
        image16bit->maxPixelValue);
        
    instrumentsPanel->setHistogramCutting(
        { image16bit->minPixelValue, image16bit->minPixelValue, image16bit->minPixelValue},
        { image16bit->maxPixelValue, image16bit->maxPixelValue, image16bit->maxPixelValue});
        
    qInfo().noquote().nospace() << "Применено контрастирование в диапазоне " 
                                << image16bit->minPixelValue << ';' 
                                << image16bit->minPixelValue << ';' 
                                << image16bit->minPixelValue << ' '
                                << image16bit->maxPixelValue << ';' 
                                << image16bit->maxPixelValue << ';' 
                                << image16bit->maxPixelValue;
}

void ImageLabel::showChannelsInfo()
{
    wavescaleTable->show();
}

void ImageLabel::updatePixelGraphic(int x, int y, bool addNew = false)
{
    PixelReader * pixelReader = new PixelReader();
    uint16_t * pixelValues = pixelReader->readPixelBrightness(x, y, image16bit);
    double * waveLengthValues = wavescaleTable->getWaveLengthValues();
    
    if(addNew)
        instrumentsPanel->addPixelGraphic(pixelValues, waveLengthValues, image16bit->channelsCount, x, y);
    else
        instrumentsPanel->updateDynamicPixelGraphic(pixelValues, waveLengthValues, image16bit->channelsCount, x, y);
    
    delete[] pixelValues;
    delete[] waveLengthValues;
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
    
    histogramCalculator->calculateColorsFrequency(image16bit);
	
	qInfo().noquote() << "Изображение открыто в режиме Grayscale по каналу: " << channel;
	
    updateImage();
}

void ImageLabel::rgbSelectedEvent()
{   
    RgbChannels channels = channelSelector->getSelectedChannels();
    
    channelSelector->close();
    
    image16bit->loadRgb(image16bit->getFilePath(), channels);
    
    resetContrastingParams();
    
    histogramCalculator->calculateColorsFrequency(image16bit);
    
	qInfo().noquote().nospace() << "Изображение открыто в режиме RGB по каналам: " <<
	                    channels.red << ';' << channels.green << ';' << channels.blue;
    
    updateImage();
}

void ImageLabel::standartContrastingEvent()
{    
    Pixel16bit minCuttingPixel = contrastingWin->getMinPixelParameters();
    Pixel16bit maxCuttingPixel = contrastingWin->getMaxPixelParameters();
    
    contrastingWin->close();
    
    painter->setNormalization(minCuttingPixel, maxCuttingPixel);
    instrumentsPanel->setHistogramCutting(minCuttingPixel, maxCuttingPixel);
    
    qInfo().noquote().nospace() << "Применено контрастирование в диапазоне " 
                                << minCuttingPixel.red << ';' 
                                << minCuttingPixel.green << ';' 
                                << minCuttingPixel.blue << ' '
                                << maxCuttingPixel.red << ';' 
                                << maxCuttingPixel.green << ';' 
                                << maxCuttingPixel.blue;
    
    updateImage();
}

void ImageLabel::histogramContrastingEvent()
{
    float leftCuttingPercent = contrastingWin->getLeftCuttingPercent();
    float rightCuttingPercent = contrastingWin->getRightCuttingPercent();
    
    Pixel16bit minCuttingPixel = histogramCalculator->findMinContrasingValue(
                                                        leftCuttingPercent,
                                                        image16bit->width,
                                                        image16bit->height);
    Pixel16bit maxCuttingPixel = histogramCalculator->findMaxContrasingValue(
                                                        rightCuttingPercent,
                                                        image16bit->width,
                                                        image16bit->height);
    
    contrastingWin->close();
    
    painter->setNormalization(minCuttingPixel, maxCuttingPixel);
    instrumentsPanel->setHistogramCutting(minCuttingPixel, maxCuttingPixel);
    
    qInfo().noquote().nospace() << "Применено контрастирование в диапазоне " 
                                << minCuttingPixel.red << ';' 
                                << minCuttingPixel.green << ';' 
                                << minCuttingPixel.blue << ' '
                                << maxCuttingPixel.red << ';' 
                                << maxCuttingPixel.green << ';' 
                                << maxCuttingPixel.blue;
    
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
			
			if(wavescaleTable->hasData())
			    updatePixelGraphic(x, y);
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
    else if(hasImage() 
    && event->button() == Qt::LeftButton)
    {
        if(instrumentsPanel->isPixelSelecting())
        {
            QPoint mousePos = mapFromGlobal(QCursor::pos());
            int x = mousePos.rx();
            int y = mousePos.ry();
        
            if(x >= 0 && y >= 0 && x < image8bit->width() && y < image8bit->height())
            {
                updatePixelGraphic(x,y, true);
            } 
        }
        
    }
}
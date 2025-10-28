#include "../../../include/imageOptionsPanel.h"

ImageOptionsPanel::ImageOptionsPanel()
{
    histogramText = new QLabel("Гистограмма");
    optionsText = new QLabel("Инструменты");

    createChannelSelector();
    createHistogram();
    createOptionsTable();
    
    this->addStretch(1);
}

void ImageOptionsPanel::createChannelSelector()
{
    channelSelector = new QComboBox();
	channelSelector->addItems({"Красный канал", "Зелёный канал", "Синий канал"});

    this->addWidget(histogramText);
    this->addWidget(channelSelector);
    
    connect(channelSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ImageOptionsPanel::colorChangedEvent);
}

void ImageOptionsPanel::createHistogram()
{
    plot = new QCustomPlot();
	plot->setFixedSize(355, 355);
	plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(0, 10);
	
	histogram = new QCPBars(plot->xAxis, plot->yAxis);
	
	histogram->setPen(QPen(Qt::red));
	histogram->setBrush(Qt::red);
	
    plot->setInteractions(QCP::iSelectPlottables);
    plot->axisRect()->setRangeZoomAxes(plot->xAxis, NULL);
    plot->setSelectionRectMode(QCP::srmZoom);
	
	resetScaleButton = new QPushButton("Сбросить масштаб");
	resetScaleButton->setToolTip("Сбросить масштаб");
	
	connect(resetScaleButton, &QPushButton::clicked, this, &ImageOptionsPanel::resetScale);
	
	this->addWidget(plot);
	this->addWidget(resetScaleButton);
}

void ImageOptionsPanel::createOptionsTable()
{
    QVBoxLayout * optionsBox = new QVBoxLayout();

    optionsButtonsTable = new QGridLayout();

    grayscaleButton = new QPushButton("Режим Grayscale");
    rgbButton = new QPushButton("Режим RGB");
	standartContrastingButton = new QPushButton("Ручное контрастирование");
	histogramContrastingButton = new QPushButton("Контрастирование по гистограмме");
	resetContrastingButton = new QPushButton("Сбросить контрастирование");
	
	grayscaleButton->setToolTip("Режим Grayscale");
	rgbButton->setToolTip("Режим RGB");
	standartContrastingButton->setToolTip("Ручное контрастирование");
	histogramContrastingButton->setToolTip("Контрастирование по гистограмме");
	resetContrastingButton->setToolTip("Сбросить контрастирование");
	
    connect(grayscaleButton, &QPushButton::clicked, this, &ImageOptionsPanel::grayscaleSelectedEvent);
    connect(rgbButton, &QPushButton::clicked, this, &ImageOptionsPanel::rgbSelectedEvent);
    connect(standartContrastingButton, &QPushButton::clicked, this, &ImageOptionsPanel::standartContrastingEvent);
    connect(histogramContrastingButton, &QPushButton::clicked, this, &ImageOptionsPanel::histogramContrastingEvent);
    connect(resetContrastingButton, &QPushButton::clicked, this, &ImageOptionsPanel::resetContrastingEvent);
	
	optionsButtonsTable->addWidget(grayscaleButton, 0, 0);
	optionsButtonsTable->addWidget(rgbButton, 0, 1);
	optionsButtonsTable->addWidget(standartContrastingButton, 1, 0);
	optionsButtonsTable->addWidget(histogramContrastingButton, 1, 1);
	optionsButtonsTable->addWidget(resetContrastingButton, 2, 0);

    optionsBox->addWidget(optionsText);
    optionsBox->addLayout(optionsButtonsTable);
	
	this->addLayout(optionsBox);
}

void ImageOptionsPanel::paintImageHistogram(std::map<uint16_t, int> & colorFrequency)
{
    switchCutting();

    QVector<double> colorValues, frequency;
    int i = 0;
    
    for(auto it: colorFrequency)
    {
        double colorValue = it.first;
        double colorFrequency = it.second;
        
        if(colorValue < leftCuttingValue || colorValue > rightCuttingValue)
            continue;
        
        colorValues.push_back(colorValue);
        frequency.push_back(colorFrequency);
        
        i++;
    }
    
    plot->xAxis->setLabel("Яркость 16 бит");
    plot->yAxis->setLabel("Количество пикселей");
    
    plot->xAxis->setRange(0, 1);
    plot->yAxis->setRange(0, 1);
    
    histogram->setData(colorValues, frequency);
    
    plot->rescaleAxes();
    plot->replot();
}

void ImageOptionsPanel::setEnabled(bool isEnabled)
{
    channelSelector->setEnabled(isEnabled);
    
    grayscaleButton->setEnabled(isEnabled);
    rgbButton->setEnabled(isEnabled);
    standartContrastingButton->setEnabled(isEnabled);
    histogramContrastingButton->setEnabled(isEnabled);
    resetContrastingButton->setEnabled(isEnabled);
    
    resetScaleButton->setEnabled(isEnabled);
}

void ImageOptionsPanel::setVisible(bool isVisible)
{
    channelSelector->setVisible(isVisible);
    
    grayscaleButton->setVisible(isVisible);
    rgbButton->setVisible(isVisible);
    standartContrastingButton->setVisible(isVisible);
    histogramContrastingButton->setVisible(isVisible);
    resetContrastingButton->setVisible(isVisible);
    
    histogramText->setVisible(isVisible);
    optionsText->setVisible(isVisible);
    
    resetScaleButton->setVisible(isVisible);
    
    plot->setVisible(isVisible);
}

void ImageOptionsPanel::setCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues)
{
    this->leftCuttingValues = leftCuttingValues;
    this->rightCuttingValues = rightCuttingValues;
    
    switchCutting();
}

void ImageOptionsPanel::switchCutting()
{
    QColor currentColor = getChannelColor();

    if (currentColor == Qt::red)
	{
	    leftCuttingValue = leftCuttingValues.red;
	    rightCuttingValue = rightCuttingValues.red;
	}
	else if (currentColor == Qt::green)
	{
	    leftCuttingValue = leftCuttingValues.green;
	    rightCuttingValue = rightCuttingValues.green;
	}
	else if (currentColor == Qt::blue)
	{
	    leftCuttingValue = leftCuttingValues.blue;
	    rightCuttingValue = rightCuttingValues.blue;
	}
	else
	{
	    leftCuttingValue = leftCuttingValues.red;
	    rightCuttingValue = rightCuttingValues.red;
	}
}

QColor ImageOptionsPanel::getChannelColor()
{
    if (channelSelector->currentText() == "Красный канал")
		return Qt::red;
	else if (channelSelector->currentText() == "Зелёный канал")
		return Qt::green;
	else if (channelSelector->currentText() == "Синий канал")
		return Qt::blue;
	else
	    return Qt::gray;
}

void ImageOptionsPanel::setGrayscaleSelectedEvent(std::function<void()> eventHandler)
{
    grayscaleSelectedEventHandler = eventHandler;
}

void ImageOptionsPanel::setRgbSelectedEvent(std::function<void()> eventHandler)
{
    rgbSelectedEventHandler = eventHandler;
}

void ImageOptionsPanel::setStandartContrastingEvent(std::function<void()> eventHandler)
{
    standartContrastingEventHandler = eventHandler;
}

void ImageOptionsPanel::setHistogramContrastingEvent(std::function<void()> eventHandler)
{
    histogramContrastingEventHandler = eventHandler;
}

void ImageOptionsPanel::setResetContrastingEvent(std::function<void()> eventHandler)
{
    resetContrastingEventHandler = eventHandler;
}

void ImageOptionsPanel::setColorChangedEvent(std::function<void()> eventHandler)
{
    colorChangedEventHandler = eventHandler;
}

void ImageOptionsPanel::grayscaleSelectedEvent()
{
    grayscaleSelectedEventHandler();
}

void ImageOptionsPanel::rgbSelectedEvent()
{
    rgbSelectedEventHandler();
}

void ImageOptionsPanel::standartContrastingEvent()
{
    standartContrastingEventHandler();
}

void ImageOptionsPanel::histogramContrastingEvent()
{
    histogramContrastingEventHandler();
}

void ImageOptionsPanel::resetScale()
{
    plot->rescaleAxes();
    plot->replot();
}

void ImageOptionsPanel::resetContrastingEvent()
{
    resetContrastingEventHandler();
}

void ImageOptionsPanel::colorChangedEvent()
{
    QColor currentColor = getChannelColor();
    
    histogram->setPen(QPen(currentColor));
    histogram->setBrush(currentColor);
    
    switchCutting();
	    
    colorChangedEventHandler();
}
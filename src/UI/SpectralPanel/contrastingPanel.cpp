#include "../../../include/contrastingPanel.h"

ContrastingPanel::ContrastingPanel()
{
    histogramText = new QLabel("Гистограмма");
    contrastingText = new QLabel("Опции контрастирования");

    createChannelSelector();
    createHistogram();
    createContrastingOptions();
    
    this->addStretch(1);
}

void ContrastingPanel::createChannelSelector()
{
    channelSelector = new QComboBox();
	channelSelector->addItems({"Красный канал", "Зелёный канал", "Синий канал"});
	channelSelector->setFixedWidth(255);

    this->addWidget(histogramText);
    this->addWidget(channelSelector);
    
    connect(channelSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ContrastingPanel::colorChangedEvent);
}

void ContrastingPanel::createHistogram()
{
    plot = new QCustomPlot();
	plot->setFixedSize(700, 350);
	plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(0, 10);
	
	histogram = new QCPBars(plot->xAxis, plot->yAxis);
	
	histogram->setPen(QPen(Qt::red));
	histogram->setBrush(Qt::red);
	
    plot->setInteractions(QCP::iSelectPlottables);
    plot->axisRect()->setRangeZoomAxes(plot->xAxis, NULL);
    plot->setSelectionRectMode(QCP::srmZoom);
	
	resetScaleButton = new QPushButton("Сбросить масштаб");
	connect(resetScaleButton, &QPushButton::clicked, this, &ContrastingPanel::resetScale);
	
	this->addWidget(plot);
	this->addWidget(resetScaleButton);
}

void ContrastingPanel::createContrastingOptions()
{
    QVBoxLayout * contrastingOptions = new QVBoxLayout();

	standartContrastingButton = new QPushButton("Ручное контрастирование");
	histogramContrastingButton = new QPushButton("Контрастирование по гистограмме");
	resetContrastingButton = new QPushButton("Сбросить контрастирование");
	
	
	standartContrastingButton->setFixedWidth(255);
	histogramContrastingButton->setFixedWidth(255);
	resetContrastingButton->setFixedWidth(255);
	
    connect(standartContrastingButton, &QPushButton::clicked, this, &ContrastingPanel::standartContrastingEvent);
    connect(histogramContrastingButton, &QPushButton::clicked, this, &ContrastingPanel::histogramContrastingEvent);
    connect(resetContrastingButton, &QPushButton::clicked, this, &ContrastingPanel::resetContrastingEvent);

	contrastingOptions->addWidget(contrastingText);
	contrastingOptions->addWidget(standartContrastingButton);
	contrastingOptions->addWidget(histogramContrastingButton);
	contrastingOptions->addWidget(resetContrastingButton);
	
	this->addLayout(contrastingOptions);
}

void ContrastingPanel::paintImageHistogram(std::map<uint16_t, int> & colorFrequency)
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

void ContrastingPanel::setEnabled(bool isEnabled)
{
    channelSelector->setEnabled(isEnabled);
    
    standartContrastingButton->setEnabled(isEnabled);
    histogramContrastingButton->setEnabled(isEnabled);
    resetContrastingButton->setEnabled(isEnabled);
    
    resetScaleButton->setEnabled(isEnabled);
}

void ContrastingPanel::setVisible(bool isVisible)
{
    channelSelector->setVisible(isVisible);
    
    standartContrastingButton->setVisible(isVisible);
    histogramContrastingButton->setVisible(isVisible);
    resetContrastingButton->setVisible(isVisible);
    
    histogramText->setVisible(isVisible);
    contrastingText->setVisible(isVisible);
    
    resetScaleButton->setVisible(isVisible);
    
    plot->setVisible(isVisible);
}

void ContrastingPanel::setCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues)
{
    this->leftCuttingValues = leftCuttingValues;
    this->rightCuttingValues = rightCuttingValues;
    
    switchCutting();
}

void ContrastingPanel::switchCutting()
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

QColor ContrastingPanel::getChannelColor()
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

void ContrastingPanel::setStandartContrastingEvent(std::function<void()> eventHandler)
{
    standartContrastingEventHandler = eventHandler;
}

void ContrastingPanel::setHistogramContrastingEvent(std::function<void()> eventHandler)
{
    histogramContrastingEventHandler = eventHandler;
}

void ContrastingPanel::setResetContrastingEvent(std::function<void()> eventHandler)
{
    resetContrastingEventHandler = eventHandler;
}

void ContrastingPanel::setColorChangedEvent(std::function<void()> eventHandler)
{
    colorChangedEventHandler = eventHandler;
}

void ContrastingPanel::standartContrastingEvent()
{
    standartContrastingEventHandler();
}

void ContrastingPanel::histogramContrastingEvent()
{
    histogramContrastingEventHandler();
}

void ContrastingPanel::resetScale()
{
    plot->rescaleAxes();
    plot->replot();
}

void ContrastingPanel::resetContrastingEvent()
{
    resetContrastingEventHandler();
}

void ContrastingPanel::colorChangedEvent()
{
    QColor currentColor = getChannelColor();
    
    histogram->setPen(QPen(currentColor));
    histogram->setBrush(currentColor);
    
    switchCutting();
	    
    colorChangedEventHandler();
}
#include "../../include/contrastingPanel.h"

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
	plot->setFixedSize(350, 350);
	plot->xAxis->setRange(0, 1);
    plot->yAxis->setRange(0, 1);
	
	histogram = new QCPBars(plot->xAxis, plot->yAxis);
	
	histogram->setPen(QPen(Qt::red));
	histogram->setBrush(Qt::red);
	
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->axisRect()->setRangeDrag(Qt::Horizontal);
    plot->axisRect()->setRangeZoom(Qt::Horizontal);
    plot->axisRect()->setRangeZoomAxes(plot->xAxis, NULL);
    plot->setSelectionRectMode(QCP::srmZoom);
	
	this->addWidget(plot);
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
    
    histogram->setData(colorValues, frequency);
    
    plot->xAxis->setRange(0, 1);
    plot->yAxis->setRange(0, 1);
    
    plot->rescaleAxes();
    plot->replot();
}

void ContrastingPanel::setEnabled(bool isEnabled)
{
    if(!isEnabled)
    {
        channelSelector->setEnabled(false);
        
        standartContrastingButton->setEnabled(false);
        histogramContrastingButton->setEnabled(false);
        resetContrastingButton->setEnabled(false);
    }
    else
    {
        channelSelector->setEnabled(true);
        
        standartContrastingButton->setEnabled(true);
        histogramContrastingButton->setEnabled(true);
        resetContrastingButton->setEnabled(true);
    }
}

void ContrastingPanel::setVisible(bool isVisible)
{
    if(isVisible)
    {
        channelSelector->setVisible(true);
        
        standartContrastingButton->setVisible(true);
        histogramContrastingButton->setVisible(true);
        resetContrastingButton->setVisible(true);
        
        histogramText->setVisible(true);
        contrastingText->setVisible(true);
        
        plot->setVisible(true);
    }
    else
    {
        channelSelector->setVisible(false);
        
        standartContrastingButton->setVisible(false);
        histogramContrastingButton->setVisible(false);
        resetContrastingButton->setVisible(false);
        
        histogramText->setVisible(false);
        contrastingText->setVisible(false);
        
        plot->setVisible(false);
    }
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
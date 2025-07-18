#include "../../include/histogramPanel.h"
#include "../../include/histogramPainter.h"

HistogramPanel::HistogramPanel() : QWidget()
{
	this->setFixedWidth(345);

	panel = new QVBoxLayout(this);

	painter = new HistogramPainter();

	createChannelSelector();
	createHistogramPanel();
}

void HistogramPanel::createHistogramPanel()
{
	histogram = new QGraphicsView();
	histogram->setFixedSize(330, 330);
	
	panel->addWidget(histogram);
}

void HistogramPanel::createChannelSelector()
{
    channelSelector = new QComboBox();
	channelSelector->addItems({"Красный канал", "Зелёный канал", "Синий канал"});
	channelSelector->setFixedWidth(255);
	channelSelector->setEnabled(false);

	connect(channelSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HistogramPanel::changeColor);

	panel->addWidget(channelSelector);
}

void HistogramPanel::reloadHistogramScene()
{
	delete scene;
	
	scene = new QGraphicsScene();
	
	histogram->setScene(scene);
}

void HistogramPanel::updateHistogram(TIFF * image, uint16_t minValue, uint16_t maxValue)
{
	spectatedImage = image;
	this->minValue = minValue;
	this->maxValue = maxValue;

	reloadHistogramScene();
	
	QPen pen;
	
	if(!image->isGrayscale)
	{
		channelSelector->setEnabled(true);
		QColor paintColor = getChannelColor();
		pen.setColor(paintColor);
	}
	else
		pen.setColor(Qt::gray);

	painter->setHistogramCutting(minValue, maxValue);
	painter->paintHistogram(scene, spectatedImage, pen);
}

void HistogramPanel::changeColor()
{
    updateHistogram(spectatedImage, minValue, maxValue);
}

void HistogramPanel::clearHistogram()
{
	reloadHistogramScene();
	
	spectatedImage = nullptr;
	
	channelSelector->setEnabled(false);
}

QColor HistogramPanel::getChannelColor()
{
	if (channelSelector->currentText() == "Красный канал")
	{
		return Qt::red;
	}
	else if (channelSelector->currentText() == "Зелёный канал")
	{
		return Qt::green;
	}
	else if (channelSelector->currentText() == "Синий канал")
	{
		return Qt::blue;
	}
	else
	    return Qt::gray;
}

int HistogramPanel::getColumnValue(int x)
{
    return painter->getColumnValue(x);
}
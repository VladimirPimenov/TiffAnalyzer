#include "../../include/histogramPanel.h"
#include "../../include/histogramPainter.h"

HistogramPanel::HistogramPanel() : QWidget()
{
	this->setFixedWidth(360);

	panel = new QVBoxLayout(this);

	painter = new HistogramPainter();

	createChannelSelector();
	createHistogramPanel();
}

void HistogramPanel::createHistogramPanel()
{
	histogram = new QGraphicsView();
	histogram->setFixedSize(350, 350);
	
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

void HistogramPanel::setImage(TIFF * image)
{
    spectatedImage = image;

	reloadHistogramScene();
	
	painter->setImage(image);
}

void HistogramPanel::updateHistogram()
{
	reloadHistogramScene();
	
	QPen pen;
	
	if(!spectatedImage->isGrayscale)
	{
		channelSelector->setEnabled(true);
		QColor paintColor = getChannelColor();
		pen.setColor(paintColor);
	}
	else
		pen.setColor(Qt::gray);

	painter->paintHistogram(scene, pen);
}

void HistogramPanel::setCutting(Pixel16bit leftValues, Pixel16bit rightValues)
{
    painter->setHistogramCutting(leftValues, rightValues);
}

void HistogramPanel::changeColor()
{
    updateHistogram();
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

int HistogramPanel::getColumnRedValue(int x)
{
    return painter->getColumnRedValue(x);
}

int HistogramPanel::getColumnGreenValue(int x)
{
    return painter->getColumnGreenValue(x);
}

int HistogramPanel::getColumnBlueValue(int x)
{
    return painter->getColumnBlueValue(x);
}
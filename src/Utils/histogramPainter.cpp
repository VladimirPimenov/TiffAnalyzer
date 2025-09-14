#include "../../include/histogramPainter.h"

#include "../../include/normalizer.h"

std::string getExponencialView(double num)
{
    int tenMultiplier = 0;
    
    while(num >= 10)
    {
        num /= 10;
        tenMultiplier++;
    }
    return std::to_string(num).substr(0,3) + "E" + std::to_string(tenMultiplier);
}

int calculatePrettyAxisValue(int realMaxValue)
{
    int prettyValue = realMaxValue;
    
    while(true)
    {
        if(prettyValue % 4 == 0 && prettyValue % 5 == 0)
			return prettyValue;
			
		prettyValue++;
    }
}

HistogramPainter::HistogramPainter()
{
	axisOffset = 50;
	
	leftCuttingValues = { 0, 0, 0};
	rightCuttingValues = { 0, 0, 0};
}

void HistogramPainter::paintAxisX(QGraphicsScene * histogram)
{
	int prettyMaxPixelValue = calculatePrettyAxisValue(maxPixelValue);

	QPen pen = Qt::black;
	QBrush brush = Qt::black;
	
    histogram->addRect(axisOffset, 0, 265, 1, pen, brush);

	histogram->addRect(axisOffset + 255 / 4, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 255 / 2, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 255 * 3 / 4, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 255, 0, 1, -5, pen, brush);

	QGraphicsTextItem * x0 = histogram->addText("0");
	QGraphicsTextItem * x1 = histogram->addText(QString::fromStdString(std::to_string(prettyMaxPixelValue / 4)));
	QGraphicsTextItem * x2 = histogram->addText(QString::fromStdString(std::to_string(prettyMaxPixelValue / 2)));
	QGraphicsTextItem * x3 = histogram->addText(QString::fromStdString(std::to_string(prettyMaxPixelValue * 3 / 4)));
	QGraphicsTextItem * x4 = histogram->addText(QString::fromStdString(std::to_string(prettyMaxPixelValue)));
	
	x0->setPos(axisOffset - 15,0);
	x1->setPos(axisOffset + 50,0);
	x2->setPos(axisOffset + 110,0);
	x3->setPos(axisOffset + 175,0);
	x4->setPos(axisOffset + 235,0);
}

void HistogramPainter::paintAxisY(QGraphicsScene * histogram)
{
	int yOffset = 10;
	QPen pen = Qt::black;
	QBrush brush = Qt::black;

	histogram->addRect(axisOffset, 0, 1, -255, pen, brush);
	
	histogram->addRect(axisOffset, -255 / 4 + yOffset, 5, 1, pen, brush);
	histogram->addRect(axisOffset, -255 / 2 + yOffset, 5, 1, pen, brush);
	histogram->addRect(axisOffset, -255 * 3 / 4 + yOffset, 5, 1, pen, brush);
	histogram->addRect(axisOffset, -255 + yOffset, 5, 1, pen, brush);
	
	QGraphicsItem * y1 = histogram->addText(QString::fromStdString(getExponencialView(maxPixelCount / 4)));
	QGraphicsItem * y2 = histogram->addText(QString::fromStdString(getExponencialView(maxPixelCount / 2)));
	QGraphicsItem * y3 = histogram->addText(QString::fromStdString(getExponencialView(maxPixelCount * 3 / 4)));
	QGraphicsItem * y4 = histogram->addText(QString::fromStdString(getExponencialView(maxPixelCount)));

	y1->setPos(0, -64);
	y2->setPos(0, -128);
	y3->setPos(0, -191);
	y4->setPos(0, -255);
}

void HistogramPainter::paintHistogram(QGraphicsScene * histogram, QPen usingPen)
{
	paintAxisX(histogram);
	paintAxisY(histogram);
	
	QColor usingColor = usingPen.color();
	
	if(usingColor == Qt::red || usingColor == Qt::gray)
	{
	    paintHistogramGraphics(histogram, usingPen, redFrequency, leftCuttingValues.red, rightCuttingValues.red);
	}
	else if(usingColor == Qt::green)
	{
		paintHistogramGraphics(histogram, usingPen, greenFrequency, leftCuttingValues.green, rightCuttingValues.green);
	}
	else if(usingColor == Qt::blue)
	{
		paintHistogramGraphics(histogram, usingPen, blueFrequency, leftCuttingValues.blue, rightCuttingValues.blue);
	}
}

void HistogramPainter::paintHistogramGraphics(QGraphicsScene * histogram, QPen usingPen, std::map<uint16_t, int> colorsFrequency, uint16_t leftCuttingValue, uint16_t rightCuttingValue)
{
	int x, y, scaledX, scaledY;

    for (auto it = colorsFrequency.begin(); it != colorsFrequency.end(); it++)
	{
		x = it->first;
		y = it->second;
		
		scaledX = Normalizer::minMaxNormalization(x, 0, maxPixelValue, 0, 255);
		scaledY = Normalizer::minMaxNormalization(y, 0, maxPixelCount, 0, 255);
		
		if(isNeedCutting() && (x < leftCuttingValue || x > rightCuttingValue))
			continue;
		histogram->addLine(scaledX + axisOffset, 0, scaledX + axisOffset, -scaledY, usingPen);
	}
}

void HistogramPainter::setImage(TIFF * image)
{
	calculateColorsFrequency(image);
}

void HistogramPainter::calculateColorsFrequency(TIFF * image)
{
	redFrequency.clear();
	greenFrequency.clear();
	blueFrequency.clear();

	uint16_t redValue;
	uint16_t greenValue;
	uint16_t blueValue;
	
	Pixel16bit pixel;
	
	maxPixelCount = 0;
	maxPixelValue = 0;

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pixel = image->getPixel(x, y);

			redValue = pixel.red;
			greenValue = pixel.green;
			blueValue = pixel.blue;

			updateColorFrequency(redFrequency, redValue);
			updateColorFrequency(greenFrequency, greenValue);
			updateColorFrequency(blueFrequency, blueValue);
		}
	}
}

void HistogramPainter::updateColorFrequency(std::map<uint16_t, int> & colorFrequency, uint16_t colorValue)
{
    if(colorFrequency.count(colorValue))
	{
		colorFrequency[colorValue]++;
		
		maxPixelCount = std::max(maxPixelCount, colorFrequency[colorValue]);
	}
	else
		colorFrequency[colorValue] = 1;
		
	if(colorValue > maxPixelValue)
		maxPixelValue = colorValue;
}

void HistogramPainter::setHistogramCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues)
{
    this->leftCuttingValues = leftCuttingValues;
    this->rightCuttingValues = rightCuttingValues;
}

bool HistogramPainter::isNeedCutting()
{
    if(rightCuttingValues.red != 0 || rightCuttingValues.green != 0 || rightCuttingValues.blue != 0)
		return true;
	return false;
}

int HistogramPainter::getColumnRedValue(int x)
{
	if(x > maxPixelValue)
		return 0;
		
    return redFrequency[x];
}

int HistogramPainter::getColumnGreenValue(int x)
{
	if(x > maxPixelValue)
		return 0;
		
    return greenFrequency[x];
}

int HistogramPainter::getColumnBlueValue(int x)
{
	if(x > maxPixelValue)
		return 0;
		
    return blueFrequency[x];
}
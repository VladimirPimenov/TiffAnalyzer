#include "../../include/histogramPainter.h"
#include "../../include/histogramPanel.h"

float findScale(float max)
{
	float scale = 1;
	
    while(max > 255)
    {
        max /= 1.5f;
        scale *= 1.5f;
    }
    return scale;
}

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
	
	minCuttingValue = 0;
	maxCuttingValue = 0;
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

void HistogramPainter::paintHistogram(QGraphicsScene * histogram, TIFF * image, QPen usingPen)
{
	calculateColorsFrequency(image, usingPen);
	
	XScale = findScale(maxPixelValue);
	paintAxisX(histogram);
	
    Yscale = findScale(maxPixelCount);
	paintAxisY(histogram);
	
	int x, y;
    for (auto it = colorsFrequency.begin(); it != colorsFrequency.end(); it++)
	{
		x = it->first;
		y = it->second;
		
		if(x != 0)
			if(isNeedCutting() && (x < minCuttingValue || x > maxCuttingValue))
				continue;
			histogram->addLine(axisOffset + x/XScale, 0, axisOffset + x/XScale, -y/Yscale, usingPen);
	}
}

void HistogramPainter::calculateColorsFrequency(TIFF * image, QPen usingPen)
{
	colorsFrequency.clear();

	QColor usingColor = usingPen.color();
	uint16_t colorValue;
	
	Pixel16bit pixel;
	
	maxPixelCount = 0;
	maxPixelValue = 0;

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pixel = image->pixels[y][x];

			if (usingColor == Qt::red)
			{
				colorValue = pixel.red;
			}
			else if (usingColor == Qt::green)
			{
				colorValue = pixel.green;
			}
			else if (usingColor == Qt::blue)
			{
				colorValue = pixel.blue;
			}
			else
			{
			    colorValue = pixel.red;
			}

			if (colorsFrequency.count(colorValue))
			{
				colorsFrequency[colorValue]++;
				
				maxPixelCount = std::max(maxPixelCount, colorsFrequency[colorValue]);
			}
			else
				colorsFrequency[colorValue] = 1;
			
			if(colorValue > maxPixelValue)
				maxPixelValue = colorValue;
		}
	}
}

void HistogramPainter::setHistogramCutting(uint16_t minCuttingValue, uint16_t maxCuttingValue)
{
    this->minCuttingValue = minCuttingValue;
    this->maxCuttingValue = maxCuttingValue;
}

bool HistogramPainter::isNeedCutting()
{
    if(maxCuttingValue != 0)
		return true;
	return false;
}

int HistogramPainter::getColumnValue(int x)
{
	if(x > maxPixelValue)
		return 0;
		
    return colorsFrequency[x];
}
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

HistogramPainter::HistogramPainter()
{
	axisOffset = 50;
	
	minCuttingValue = 0;
	maxCuttingValue = 0;
}

void HistogramPainter::paintAxisX(QGraphicsScene * histogram)
{
	QPen pen = Qt::black;
	QBrush brush = Qt::black;
	
    histogram->addRect(axisOffset, 0, 260, 1, pen, brush);

	histogram->addRect(axisOffset + 50, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 100, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 150, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 200, 0, 1, -5, pen, brush);
	histogram->addRect(axisOffset + 255, 0, 1, -5, pen, brush);

	QGraphicsTextItem * x0 = histogram->addText("0");
	QGraphicsTextItem * x14 = histogram->addText(QString::fromStdString(std::to_string(maxPixelValue / 4)));
	QGraphicsTextItem * xHalf = histogram->addText(QString::fromStdString(std::to_string(maxPixelValue / 2)));
	QGraphicsTextItem * x34 = histogram->addText(QString::fromStdString(std::to_string(3 * maxPixelValue / 4)));
	QGraphicsTextItem * xMax = histogram->addText(QString::fromStdString(std::to_string(maxPixelValue)));
	
	x0->setPos(axisOffset + 0,0);
	x14->setPos(axisOffset + 64 - 10,0);
	xHalf->setPos(axisOffset + 127 - 10,0);
	x34->setPos(axisOffset + 191 - 10,0);
	xMax->setPos(axisOffset + 255 - 10,0);
}

void HistogramPainter::paintAxisY(QGraphicsScene * histogram)
{
	int scaledMaxY = -maxPixelCount/Yscale;
	
	QPen pen = Qt::black;
	QBrush brush = Qt::black;

	histogram->addRect(axisOffset, 0, 1, scaledMaxY, pen, brush);
	
	histogram->addRect(axisOffset, scaledMaxY, 5, 1, pen, brush);
	histogram->addRect(axisOffset, scaledMaxY / 2, 5, 1, pen, brush);
	
	QGraphicsItem * yMax = histogram->addText(QString::fromStdString(getExponencialView(maxPixelCount)));
	QGraphicsItem * yMaxHalf = histogram->addText(QString::fromStdString(getExponencialView(maxPixelCount / 2)));
	
	yMax->setPos(0, scaledMaxY - 6);
	yMaxHalf->setPos(0, scaledMaxY / 2 - 6);
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
	
	colorsFrequency.clear();
}

void HistogramPainter::calculateColorsFrequency(TIFF * image, QPen usingPen)
{
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

uint16_t HistogramPainter::getMaxPixelValue()
{
    return maxPixelValue;
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
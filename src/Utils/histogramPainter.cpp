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
	QGraphicsTextItem * x50 = histogram->addText("50");
	QGraphicsTextItem * x100 = histogram->addText("100");
	QGraphicsTextItem * x150 = histogram->addText("150");
	QGraphicsTextItem * x200 = histogram->addText("200");
	QGraphicsTextItem * x255 = histogram->addText("255");
	
	x0->setPos(axisOffset + 0,0);
	x50->setPos(axisOffset + 50 - 10,0);
	x100->setPos(axisOffset + 100 - 10,0);
	x150->setPos(axisOffset + 150 - 10,0);
	x200->setPos(axisOffset + 200 - 10,0);
	x255->setPos(axisOffset + 255 - 10,0);
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

void HistogramPainter::paintHistogram(QGraphicsScene * histogram, QImage * image, QPen usingPen)
{
	calculateColorsFrequency(image, usingPen);
	
    Yscale = findScale(maxPixelCount);
	paintAxisX(histogram);
	paintAxisY(histogram);
	
	int x, y;
    for (auto it = colorsFrequency.begin(); it != colorsFrequency.end(); it++)
	{
		x = it->first;
		y = it->second;
		
		if(x != 0)
			histogram->addLine(axisOffset + x, 0, axisOffset + x, -y/Yscale, usingPen);
	}
	
	colorsFrequency.clear();
}

void HistogramPainter::calculateColorsFrequency(QImage * image, QPen usingPen)
{
	QColor usingColor = usingPen.color();
	int colorValue;
	
	QRgb pixel;
	maxPixelCount = 0;

	for (int x = 0; x < image->width(); x++)
	{
		for (int y = 0; y < image->height(); y++)
		{
			pixel = image->pixel(x, y);

			if (usingColor == Qt::red)
			{
				colorValue = qRed(pixel);
			}
			else if (usingColor == Qt::green)
			{
				colorValue = qGreen(pixel);
			}
			else if (usingColor == Qt::blue)
			{
				colorValue = qBlue(pixel);
			}
			else
			{
			    colorValue = qGray(pixel);
			}

			if (colorsFrequency.count(colorValue))
			{
				colorsFrequency[colorValue]++;
				
				maxPixelCount = std::max(maxPixelCount, colorsFrequency[colorValue]);
			}
			else
			{
				colorsFrequency[colorValue] = 1;
			}
		}
	}
}
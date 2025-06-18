#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QImage>
#include <QPen>
#include <QColor>
#include <QString>

#include <map>
#include <string>

class HistogramPainter
{
public:
	HistogramPainter();
	
	void paintHistogram(QGraphicsScene * histogram, QImage * image, QPen usingPen);
	
private:
	int axisOffset;
    int maxPixelCount;
	float Yscale;
	
	std::map<int, int> colorsFrequency;
	
	void paintAxisX(QGraphicsScene * histogram);
	void paintAxisY(QGraphicsScene * histogram);
	
	void calculateColorsFrequency(QImage * image, QPen usingPen);
};
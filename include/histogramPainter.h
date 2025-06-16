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

class HistogramPanel;

class HistogramPainter
{
public:
    HistogramPainter(HistogramPanel * histogram);
    
	void paintHistogram(QImage * image, QPen usingPen);
	
private:
    HistogramPanel * paintedHistogram;
    
	int axisOffset;
    int maxPixelCount;
	float Yscale;
	
	std::map<int, int> colorsFrequency;
	
	void paintAxisX();
	void paintAxisY();
	
	void calculateColorsFrequency(QImage * image, QPen usingPen);
};
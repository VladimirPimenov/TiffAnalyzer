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

#include "tiff.h"
#include "rgb.h"

class HistogramPainter
{
public:
	HistogramPainter();
	
	void paintHistogram(QGraphicsScene * histogram, TIFF * image, QPen usingPen);
	
	void setHistogramCutting(uint16_t minCuttingValue, uint16_t maxCuttingValue);
	
	uint16_t getMaxPixelValue();
private:
	int axisOffset;
	float XScale;
	float Yscale;
	
    int maxPixelCount;
    uint16_t maxPixelValue;

    uint16_t minCuttingValue;
    uint16_t maxCuttingValue;
    
	std::map<uint16_t, int> colorsFrequency;
	
	void paintAxisX(QGraphicsScene * histogram);
	void paintAxisY(QGraphicsScene * histogram);
	
	void calculateColorsFrequency(TIFF * image, QPen usingPen);
	
	bool isNeedCutting();
};
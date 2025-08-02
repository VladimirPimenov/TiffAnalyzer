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
	
	void setImage(TIFF * image);
	
	void paintHistogram(QGraphicsScene * histogram, QPen usingPen);
	
	void setHistogramCutting(uint16_t minCuttingValue, uint16_t maxCuttingValue);
	
	int getColumnValue(int x);
	
private:
	int axisOffset;
	float XScale;
	float Yscale;
	
    int maxPixelCount;
    uint16_t maxPixelValue;

    uint16_t minCuttingValue;
    uint16_t maxCuttingValue;
    
	std::map<uint16_t, int> redFrequency;
	std::map<uint16_t, int> greenFrequency;
	std::map<uint16_t, int> blueFrequency;
	
	void paintAxisX(QGraphicsScene * histogram);
	void paintAxisY(QGraphicsScene * histogram);
	void paintHistogramGraphics(QGraphicsScene * histogram, std::map<uint16_t, int> colorsFrequency, QPen pen);
	
	void calculateColorsFrequency(TIFF * image);
	void updateColorFrequency(std::map<uint16_t, int> & colorsFrequency, uint16_t colorValue);
	
	bool isNeedCutting();
};
#pragma once

#include <QColor>

#include <map>

#include "tiff.h"
#include "rgb.h"

class HistogramCalculator
{
public:
	void calculateColorsFrequency(TIFF * image);
    
    std::map<uint16_t, int> & getColorFrequency(QColor color);
    
    Pixel16bit findMinContrasingValue(float leftCuttingPercent, int width, int height);
	Pixel16bit findMaxContrasingValue(float rightCuttingPersent, int width, int height);
private:
    std::map<uint16_t, int> redFrequency;
    std::map<uint16_t, int> greenFrequency;
    std::map<uint16_t, int> blueFrequency;
    
    void HistogramCalculator::updateColorFrequency(std::map<uint16_t, int> & colorFrequency, uint16_t colorValue);
};
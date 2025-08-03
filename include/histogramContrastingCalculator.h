#pragma once

#include "rgb.h"

#include "histogramPanel.h"

class HistogramContrastingCalculator
{
public:
    static Pixel16bit findMinContrasingValue(float leftCuttingPercent, int width, int height, HistogramPanel * histogram);
	static Pixel16bit findMaxContrasingValue(float rightCuttingPersent, int width, int height, HistogramPanel * histogram);
};
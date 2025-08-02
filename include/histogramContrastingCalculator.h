#pragma once

#include "rgb.h"

#include "histogramPanel.h"

class HistogramContrastingCalculator
{
public:
    static uint16_t findMinContrasingValue(float leftCuttingPercent, int width, int height, HistogramPanel * histogram);
	static uint16_t findMaxContrasingValue(float rightCuttingPersent, int width, int height, HistogramPanel * histogram);
};
#include "../../include/histogramContrastingCalculator.h"

uint16_t HistogramContrastingCalculator::findMinContrasingValue(float leftCuttingPercent, int width, int height, HistogramPanel * histogram)
{
    int leftCuttingCount = width * height * leftCuttingPercent / 100;
    
    int currentCount = 0;
    for(int x = 0; x < 65535; x++)
    {
        currentCount += histogram->getColumnValue(x);
        
        if(currentCount >= leftCuttingCount)
        {
            return x;
        }
    }
}

uint16_t HistogramContrastingCalculator::findMaxContrasingValue(float rightCuttingPercent, int width, int height, HistogramPanel * histogram)
{
    int rightCuttingCount = width * height * rightCuttingPercent / 100;
    
    int currentCount = 0;
    for(int x = 65535; x > 0; x--)
    {
        currentCount += histogram->getColumnValue(x);
        
        if(currentCount >= rightCuttingCount)
        {
            return x;
        }
    }
}
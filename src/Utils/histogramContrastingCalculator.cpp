#include "../../include/histogramContrastingCalculator.h"

Pixel16bit HistogramContrastingCalculator::findMinContrasingValue(float leftCuttingPercent, int width, int height, HistogramPanel * histogram)
{
    int leftCuttingCount = width * height * leftCuttingPercent / 100;
    
    Pixel16bit minContrastingPixel;
    
    int redCurrentCount = 0;
    int greenCurrentCount = 0;
    int blueCurrentCount = 0;
    bool isCalculatedRed = false;
    bool isCalculatedGreen = false;
    bool isCalculatedBlue = false;
    
    for(int x = 0; x < 65535; x++)
    {
        if(isCalculatedRed && isCalculatedGreen && isCalculatedBlue)
                return minContrastingPixel;
    
        redCurrentCount += histogram->getColumnRedValue(x);
        greenCurrentCount += histogram->getColumnGreenValue(x);
        blueCurrentCount += histogram->getColumnBlueValue(x);
        
        if(!isCalculatedRed && redCurrentCount >= leftCuttingCount)
        {
            minContrastingPixel.red = x;
            
            isCalculatedRed = true;
        }
            
        if(!isCalculatedGreen && greenCurrentCount >= leftCuttingCount)
        {
            minContrastingPixel.green = x;
            
            isCalculatedGreen = true;
        }
            
        if(!isCalculatedBlue && blueCurrentCount >= leftCuttingCount)
        {
            minContrastingPixel.blue = x;

            isCalculatedBlue = true;
        }
    }
}

Pixel16bit HistogramContrastingCalculator::findMaxContrasingValue(float rightCuttingPercent, int width, int height, HistogramPanel * histogram)
{
    int rightCuttingCount = width * height * rightCuttingPercent / 100;
    
    Pixel16bit maxContrastingPixel;
    
    int redCurrentCount = 0;
    int greenCurrentCount = 0;
    int blueCurrentCount = 0;
    bool isCalculatedRed = false;
    bool isCalculatedGreen = false;
    bool isCalculatedBlue = false;
    
    for(int x = 65535; x > 0; x--)
    {
        if(isCalculatedRed && isCalculatedGreen && isCalculatedBlue)
                return maxContrastingPixel;
    
        redCurrentCount += histogram->getColumnRedValue(x);
        greenCurrentCount += histogram->getColumnGreenValue(x);
        blueCurrentCount += histogram->getColumnBlueValue(x);
        
        if(!isCalculatedRed && redCurrentCount >= rightCuttingCount)
        {
            maxContrastingPixel.red = x;
            
            isCalculatedRed = true;
        }
            
        if(!isCalculatedGreen && greenCurrentCount >= rightCuttingCount)
        {
            maxContrastingPixel.green = x;
            
            isCalculatedGreen = true;
        }
            
            
        if(!isCalculatedBlue && blueCurrentCount >= rightCuttingCount)
        {
            maxContrastingPixel.blue = x;
            
            isCalculatedBlue = true;
        }
    }
}
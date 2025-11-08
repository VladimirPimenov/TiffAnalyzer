#include "../../include/histogramCalculator.h"

void HistogramCalculator::calculateColorsFrequency(TIFF * image)
{
	redFrequency.clear();
	greenFrequency.clear();
	blueFrequency.clear();

	uint16_t redValue;
	uint16_t greenValue;
	uint16_t blueValue;
	
	Pixel16bit pixel;

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pixel = image->getPixel(x, y);

			redValue = pixel.red;
			greenValue = pixel.green;
			blueValue = pixel.blue;

			updateColorFrequency(redFrequency, redValue);
			updateColorFrequency(greenFrequency, greenValue);
			updateColorFrequency(blueFrequency, blueValue);
		}
	}
}

std::map<uint16_t, int> & HistogramCalculator::getColorFrequency(QColor color)
{
    if(color == Qt::red)
        return redFrequency;
    else if(color == Qt::green)
        return greenFrequency;
    else if(color == Qt::blue)
        return blueFrequency;
    else
        return redFrequency;
}

void HistogramCalculator::updateColorFrequency(std::map<uint16_t, int> & colorFrequency, uint16_t colorValue)
{
    if(colorFrequency.count(colorValue))
		colorFrequency[colorValue]++;
	else
		colorFrequency[colorValue] = 1;
}

Pixel16bit HistogramCalculator::findMinContrasingValue(float leftCuttingPercent, int width, int height)
{
    int leftCuttingCount = width * height * leftCuttingPercent / 100;
    
    Pixel16bit minContrastingPixel;
    
    int redCurrentCount = 0;
    int greenCurrentCount = 0;
    int blueCurrentCount = 0;
    bool isCalculatedRed = false;
    bool isCalculatedGreen = false;
    bool isCalculatedBlue = false;
    
    for(int x = 0; x < MAX_PIXEL_16BIT_VALUE; x++)
    {
        if(isCalculatedRed && isCalculatedGreen && isCalculatedBlue)
                return minContrastingPixel;
    
        redCurrentCount += redFrequency[x];
        greenCurrentCount += greenFrequency[x];
        blueCurrentCount += blueFrequency[x];
        
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
    return Pixel16bit {0, 0, 0};
}

Pixel16bit HistogramCalculator::findMaxContrasingValue(float rightCuttingPercent, int width, int height)
{
    int rightCuttingCount = width * height * rightCuttingPercent / 100;
    
    Pixel16bit maxContrastingPixel;
    
    int redCurrentCount = 0;
    int greenCurrentCount = 0;
    int blueCurrentCount = 0;
    bool isCalculatedRed = false;
    bool isCalculatedGreen = false;
    bool isCalculatedBlue = false;
    
    for(int x = MAX_PIXEL_16BIT_VALUE; x > 0; x--)
    {
        if(isCalculatedRed && isCalculatedGreen && isCalculatedBlue)
                return maxContrastingPixel;
    
        redCurrentCount += redFrequency[x];
        greenCurrentCount += greenFrequency[x];
        blueCurrentCount += blueFrequency[x];
        
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
    return Pixel16bit {MAX_PIXEL_16BIT_VALUE, MAX_PIXEL_16BIT_VALUE, MAX_PIXEL_16BIT_VALUE};
}
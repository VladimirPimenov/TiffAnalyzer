#include "../../include/imagePainter.h"
#include <iostream>

uint16_t minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX, uint16_t a, uint16_t b)
{
    /* 
    Формула minMax-нормализации в диапазоне [a; b]:
    x' = (x - min(x)) * (b - a) / (max(x) - min(x)) + a
    */
    return ((x - minX) * (b - a)) / (maxX - minX) + a;
}

void ImagePainter::paintImage(TIFF * sourceTiff, QImage * image, Pixel16bit minNormalizationPixel, Pixel16bit maxNormalizationPixel)
{
    findMinMaxPixelValues(sourceTiff);
    
    uint16_t minRedPixelValue = minNormalizationPixel.red;
    uint16_t maxRedPixelValue = maxNormalizationPixel.red;
    uint16_t minGreenPixelValue = minNormalizationPixel.green;
    uint16_t maxGreenPixelValue = maxNormalizationPixel.green;
    uint16_t minBluePixelValue = minNormalizationPixel.blue;
    uint16_t maxBluePixelValue = maxNormalizationPixel.blue;
    
    for(int y = 0; y < image->height(); y++)
    {
        for(int x = 0; x < image->width(); x++)
        {
            uint16_t normalizedRed = minMaxNormalization(sourceTiff->pixels[y][x].red, 
                                                    minPixelValue, maxPixelValue, 
                                                    minRedPixelValue, maxRedPixelValue);
            uint16_t normalizedGreen = minMaxNormalization(sourceTiff->pixels[y][x].green, 
                                                    minPixelValue, maxPixelValue, 
                                                    minGreenPixelValue, maxGreenPixelValue);
            uint16_t normalizedBlue = minMaxNormalization(sourceTiff->pixels[y][x].blue, 
                                                    minPixelValue, maxPixelValue, 
                                                    minBluePixelValue, maxBluePixelValue);
            
			image->setPixel(x, y, qRgb(normalizedRed, normalizedGreen, normalizedBlue));
        }
    }
}

void ImagePainter::findMinMaxPixelValues(TIFF * tiff)
{
    minPixelValue = 0;
    maxPixelValue = 0;
    
    for(int y = 0; y < tiff->height; y++)
    {
        for(int x = 0; x < tiff->width; x++)
        {
            if(tiff->pixels[y][x].red > maxPixelValue)
                maxPixelValue = tiff->pixels[y][x].red;
            if(tiff->pixels[y][x].green > maxPixelValue)
                maxPixelValue = tiff->pixels[y][x].green;
            if(tiff->pixels[y][x].blue > maxPixelValue)
                maxPixelValue = tiff->pixels[y][x].blue;
                
            if(tiff->pixels[y][x].red < minPixelValue)
                minPixelValue = tiff->pixels[y][x].red;
            if(tiff->pixels[y][x].green < minPixelValue)
                minPixelValue = tiff->pixels[y][x].green;
            if(tiff->pixels[y][x].blue < minPixelValue)
                minPixelValue = tiff->pixels[y][x].blue;
        }
    }
}
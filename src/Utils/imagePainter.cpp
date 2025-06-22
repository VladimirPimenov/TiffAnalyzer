#include "../../include/imagePainter.h"
#include <iostream>

int minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX, uint16_t a, uint16_t b)
{
    /* 
    Формула minMax-нормализации в диапазоне [a; b]:
    x' = (x - min(x)) * (b - a) / (max(x) - min(x)) + a
    */
    return (b - a) * ((x - minX) / (double)(maxX - minX)) + a;
}

void ImagePainter::paintImage(TIFF * image16bit, QImage * image8bit, Pixel16bit minNormalizationPixel, Pixel16bit maxNormalizationPixel)
{   
    uint16_t minRedPixelValue = minNormalizationPixel.red;
    uint16_t maxRedPixelValue = maxNormalizationPixel.red;
    uint16_t minGreenPixelValue = minNormalizationPixel.green;
    uint16_t maxGreenPixelValue = maxNormalizationPixel.green;
    uint16_t minBluePixelValue = minNormalizationPixel.blue;
    uint16_t maxBluePixelValue = maxNormalizationPixel.blue;
    
    for(int y = 0; y < image16bit->height; y++)
    {
        for(int x = 0; x < image16bit->width; x++)
        {
            int normalizedRed8bit = minMaxNormalization(image16bit->pixels[y][x].red, 
                                                        minRedPixelValue, maxRedPixelValue, 
                                                        0, 255);
            int normalizedGreen8bit = minMaxNormalization(image16bit->pixels[y][x].green, 
                                                        minGreenPixelValue, maxGreenPixelValue, 
                                                        0, 255);
            int normalizedBlue8bit = minMaxNormalization(image16bit->pixels[y][x].blue, 
                                                        minBluePixelValue, maxBluePixelValue, 
                                                        0, 255);
            
			image8bit->setPixel(x, y, qRgb(normalizedRed8bit, normalizedGreen8bit, normalizedBlue8bit));
        }
    }
}
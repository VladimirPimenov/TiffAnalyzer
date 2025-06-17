#include "../../include/imagePainter.h"
#include <iostream>

uint16_t minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX)
{
    /* 
    Формула minMax-нормализации в диапазоне [a; b]:
    x' = (x - min(x)) * (b - a) / (max(x) - min(x)) + a
    */
    return ((x - minX) * 255) / (maxX - minX);
}

void ImagePainter::paintImage(TIFF * sourceTiff, QImage * image)
{
    findMinMaxPixelValues(sourceTiff);
    
    for(int y = 0; y < image->height(); y++)
    {
        for(int x = 0; x < image->width(); x++)
        {
            uint normalizedRed = minMaxNormalization(sourceTiff->pixels[y][x].red, minPixelValue, maxPixelValue);
            uint normalizedGreen = minMaxNormalization(sourceTiff->pixels[y][x].green, minPixelValue, maxPixelValue);
            uint normalizedBlue = minMaxNormalization(sourceTiff->pixels[y][x].blue, minPixelValue, maxPixelValue);
            
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
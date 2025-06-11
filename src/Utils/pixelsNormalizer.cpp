#include "../../include/pixelsNormalizer.h"

uint16_t minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX)
{
    /* 
    Формула minMax-нормализации в диапазоне [a; b]:
    x' = (x - min(x)) * (b - a) / (max(x) - min(x)) + a
    */
    return ((x - minX) * 255) / (maxX - minX);
}

void PixelsNormalizer::normalizePixelValues(TIFF * tiff)
{
    uint16_t minPixelValue = 0;
    uint16_t maxPixelValue = 0;
    
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
    
    for(int y = 0; y < tiff->height; y++)
    {
        for(int x = 0; x < tiff->width; x++)
        {
            tiff->pixels[y][x].red = minMaxNormalization(tiff->pixels[y][x].red, minPixelValue, maxPixelValue);
            tiff->pixels[y][x].green = minMaxNormalization(tiff->pixels[y][x].green, minPixelValue, maxPixelValue);
            tiff->pixels[y][x].blue = minMaxNormalization(tiff->pixels[y][x].blue, minPixelValue, maxPixelValue);
        }
    }
}
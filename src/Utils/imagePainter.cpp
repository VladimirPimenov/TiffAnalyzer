#include "../../include/imagePainter.h"
#include "../../include/normalizer.h"

ImagePainter::ImagePainter()
{
    minNormalizationPixel = {0, 0, 0};
    maxNormalizationPixel = {MAX_PIXEL_16BIT_VALUE, MAX_PIXEL_16BIT_VALUE, MAX_PIXEL_16BIT_VALUE};
}

int correctTo8bitRange(int pixelValue)
{
    int corrected = pixelValue;
    
    if(corrected > (int)MAX_PIXEL_8BIT_VALUE)
        corrected = (int)MAX_PIXEL_8BIT_VALUE;
    if(corrected < 0)
        corrected = 0;
    
    return corrected;
}

void ImagePainter::paintImage(TIFF * image16bit, QImage * image8bit)
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
            int normalizedRed8bit = Normalizer::minMaxNormalization(image16bit->getPixel(x,y).red, 
                                                                        minRedPixelValue, maxRedPixelValue, 
                                                                        0, 255);
            int normalizedGreen8bit = Normalizer::minMaxNormalization(image16bit->getPixel(x,y).green, 
                                                                        minGreenPixelValue, maxGreenPixelValue, 
                                                                        0, 255);
            int normalizedBlue8bit = Normalizer::minMaxNormalization(image16bit->getPixel(x,y).blue, 
                                                                        minBluePixelValue, maxBluePixelValue, 
                                                                        0, 255);
                                                                                                                                                                                    
            normalizedRed8bit = correctTo8bitRange(normalizedRed8bit);
            normalizedGreen8bit = correctTo8bitRange(normalizedGreen8bit);
            normalizedBlue8bit = correctTo8bitRange(normalizedBlue8bit);
                                                                                                                                                                                                                                                       
			image8bit->setPixel(x, y, qRgb(normalizedRed8bit, normalizedGreen8bit, normalizedBlue8bit));
        }
    }
}

void ImagePainter::setNormalization(uint16_t minNormalizationValue, uint16_t maxNormalizationValue)
{
    minNormalizationPixel = 
    {
        minNormalizationValue, 
        minNormalizationValue,
        minNormalizationValue
    };
    maxNormalizationPixel = 
    {
        maxNormalizationValue,
        maxNormalizationValue,
        maxNormalizationValue
    };
}

void ImagePainter::setNormalization(Pixel16bit minNormalizationPixel, Pixel16bit maxNormalizationPixel)
{
    this->minNormalizationPixel = minNormalizationPixel;
    this->maxNormalizationPixel = maxNormalizationPixel;
}
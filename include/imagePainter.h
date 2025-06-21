#pragma once

#include <QImage>

#include "tiff.h"

class ImagePainter
{
public:
    void paintImage(TIFF * sourceTiff, QImage * image, Pixel16bit minNormalizationPixel, Pixel16bit maxNormalizationPixel);
    
private:
    uint16_t minPixelValue;
    uint16_t maxPixelValue;
    
    void findMinMaxPixelValues(TIFF * tiff);
};
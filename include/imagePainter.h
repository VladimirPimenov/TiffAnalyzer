#pragma once

#include <QImage>

#include "tiff.h"

class ImagePainter
{
public:
    void paintImage(TIFF * sourceTiff, QImage * image, uint16_t minNormalizationValue, uint16_t maxNormalizationValue);
    
private:
    uint16_t minPixelValue;
    uint16_t maxPixelValue;
    
    void findMinMaxPixelValues(TIFF * tiff);
};
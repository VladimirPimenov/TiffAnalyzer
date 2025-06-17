#pragma once

#include <QImage>

#include "tiff.h"

class ImagePainter
{
public:
    void paintImage(TIFF * sourceTiff, QImage * image);
    
private:
    uint16_t minPixelValue;
    uint16_t maxPixelValue;
    
    void findMinMaxPixelValues(TIFF * tiff);
};
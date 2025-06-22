#pragma once

#include <QImage>

#include "tiff.h"

class ImagePainter
{
public:
    void paintImage(TIFF * image16bit, QImage * image8bit, Pixel16bit minNormalizationPixel, Pixel16bit maxNormalizationPixel);
};
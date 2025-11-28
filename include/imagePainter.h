#pragma once

#include <QImage>

#include "tiff.h"
#include "rgb.h"

class ImagePainter
{
public:
    ImagePainter();

    void paintImage(Tiff * image16bit, QImage * image8bit);

    void setNormalization(uint16_t minNormalizationValue, uint16_t maxNormalizationValue);
    void setNormalization(Pixel16bit minNormalizationPixel, Pixel16bit maxNormalizationPixel);

private:
    Pixel16bit minNormalizationPixel;
	Pixel16bit maxNormalizationPixel;
};
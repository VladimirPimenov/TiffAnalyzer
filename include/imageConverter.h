#pragma once

#include <QImage>

#include "bmp.h"

static class ImageConverter
{
public:
    static void convertQImageToBmp(QImage * image, BMP * bmp);
};
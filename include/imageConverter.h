#pragma once

#include <QImage>

#include "bmp.h"

class ImageConverter
{
public:
    static void convertQImageToBmp(QImage * image, Bmp * bmp);
};
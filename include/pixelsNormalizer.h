#pragma once

#include "tiff.h"

static class PixelsNormalizer
{
public:
    static void normalizePixelValues(TIFF * tiff);
};
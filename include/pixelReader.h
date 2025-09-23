#include "tiff.h"
#include "rgb.h"

class PixelReader
{
public:
    static uint16_t * readPixelBrightness(int x, int y, TIFF * sourceTiff);
};
#include "../../include/imageConverter.h"

int calculateNullBytesCount(int width)
{
    int bytesCount = width * 3;
    if(bytesCount % 4 == 0)
        return 0;
        
    int nullBytesCount = 0;
    
    while(bytesCount % 4 != 0)
    {
        nullBytesCount++;
        bytesCount++;
    }
    
    return nullBytesCount;
}

void ImageConverter::convertQImageToBmp(QImage * image, BMP * bmp)
{
    int nullBytesCount = calculateNullBytesCount(image->width());
    bmp->nullBytesCount = nullBytesCount;

    bmp->bmpHeader.type = 0x4d42;
    bmp->bmpHeader.reserved = 0;
    bmp->bmpHeader.offset = sizeof(BITMAPFILEHEADER) + 40;
    bmp->bmpHeader.fileSize = (image->width() * 3 + nullBytesCount) * image->height() + bmp->bmpHeader.offset;
    
    bmp->bmpInfo.headerSize = 40;
    bmp->bmpInfo.width = image->width();
    bmp->bmpInfo.height = image->height();
    bmp->bmpInfo.planes = 1;
    bmp->bmpInfo.bitsPerPixel = 8 * sizeof(Pixel8bit);
    
    bmp->pixels = new Pixel8bit *[image->height()];
    Pixel8bit pixel;
    
    for(int row = 0; row < image->height(); row++)
    {
        bmp->pixels[row] = new Pixel8bit[image->width()];
        
        for(int col = 0; col < image->width(); col++)
        {
            pixel.red = (uint8_t)(qRed(image->pixel(col, row)));
            pixel.green = (uint8_t)(qGreen(image->pixel(col, row)));
            pixel.blue = (uint8_t)(qBlue(image->pixel(col, row)));
            
            bmp->pixels[row][col] = pixel;
        }
    }
    
}
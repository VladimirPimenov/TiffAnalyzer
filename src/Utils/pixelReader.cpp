#include <fstream>

#include "../../include/pixelReader.h"

uint16_t * PixelReader::readPixelBrightness(int x, int y, Tiff * sourceTiff)
{
    uint32_t * stripOffsets = sourceTiff->getStripOffsets();
    
    std::ifstream tiff;
    tiff.open(sourceTiff->getFilePath(), std::ios::binary);
    
    if(!tiff.is_open())
        return nullptr;
    
    uint16_t * pixelBrightness = new uint16_t [sourceTiff->channelsCount];
    uint16_t * rowWithAllChannels = new uint16_t[sourceTiff->width * sourceTiff->channelsCount];
    
    tiff.seekg(stripOffsets[y], std::ios::beg);
    tiff.read((char *)rowWithAllChannels, sourceTiff->width * sourceTiff->channelsCount * (sourceTiff->bitsPerSample / 8)); 
    
    for(int channel = 0; channel < sourceTiff->channelsCount; channel++)
    {
        pixelBrightness[channel] = rowWithAllChannels[x * sourceTiff->channelsCount + channel];
    }
    
    tiff.close();
    
    delete[] rowWithAllChannels;
    
    
    return pixelBrightness;
}
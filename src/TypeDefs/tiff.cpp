#include "../../include/tiff.h"

uint16_t getMinPixelValue(uint16_t currentMin, Pixel16bit pixel)
{
    if(pixel.red < currentMin)
        return pixel.red;
    if(pixel.green < currentMin)
        return pixel.green;
    if(pixel.blue < currentMin)
       return pixel.blue;
       
    return currentMin;
}

uint16_t getMaxPixelValue(uint16_t currentMax, Pixel16bit pixel)
{
    if(pixel.red > currentMax)
        return pixel.red;
    if(pixel.green > currentMax)
        return pixel.green;
    if(pixel.blue > currentMax)
        return pixel.blue;
    
    return currentMax;
}

void TIFF::loadTiffMetadata(std::string loadFilePath)
{
    std::ifstream tiff;
    tiff.open(loadFilePath, std::ios::binary);
    
    if(tiff.is_open())
    {
        tiff.read((char *)(&tiffHeader), sizeof(TIFFFILEHEADER));
        tiff.seekg(tiffHeader.offset, std::ios::beg);
        
        readIFD(tiff);
        
        tiff.close();
    }
}

void TIFF::readIFD(std::ifstream & tiff)
{
    IFD * ifd = new IFD();
    this->ifd = ifd;
    
    tiff.read((char *)(&ifd->entriesCount), sizeof(ifd->entriesCount));
            
    for(uint16_t entryNum = 0; entryNum < ifd->entriesCount; entryNum++)
    {
        readEntry(tiff);
    }
    
}

void TIFF::readEntry(std::ifstream & tiff)
{
    Entry entry;

    tiff.read((char *)(&entry), sizeof(Entry));
    
    if(entry.tag == 256)
    {
        width = entry.value;
    }
    else if(entry.tag == 257)
    {
        height = entry.value;
    }
    else if(entry.tag == 277)
    {
        channelsCount = entry.value;
        
    }
    else if(entry.tag == 273)
    {
        stripOffsets = new uint32_t[height];
        
        uint32_t offsetToStripOffsets = entry.value;
        
        std::ios::pos_type stripOffsetsPosition = tiff.tellg();
        
        tiff.seekg(offsetToStripOffsets, std::ios::beg);
        tiff.read((char *)stripOffsets, height * sizeof(uint32_t));  
        
        tiff.seekg(stripOffsetsPosition, std::ios::beg);
    }
    else if(entry.tag == 278)
    {
        rowsPerStrip = entry.value;
    }
    else if(entry.tag == 258)
    {
        bitsPerSample = entry.value;
    }
    
    ifd->entries.push_back(entry);
}

void TIFF::loadGrayscale(std::string loadFilePath, int channel)
{   
    loadRgb(loadFilePath, RgbChannels {channel, channel, channel});
    
    isGrayscale = true;
}

void TIFF::loadRgb(std::string loadFilePath, RgbChannels channels)
{
    minPixelValue = 0;
    maxPixelValue = 0;

    std::ifstream tiff;
    tiff.open(loadFilePath, std::ios::binary);
    
    if(tiff.is_open())
    {
        filePath = loadFilePath;
    
        pixels = new Pixel16bit *[height];
        uint16_t * rowWithAllChannels = new uint16_t[width * channelsCount];
        
        for(int y = 0; y < height; y++)
        {
            pixels[y] = new Pixel16bit[width];
            
            tiff.seekg(stripOffsets[y], std::ios::beg);
            tiff.read((char *)rowWithAllChannels, width * channelsCount * (bitsPerSample / 8)); 
            
            for(int x = 0; x < width; x++)
            {
                pixels[y][x].red = rowWithAllChannels[x * channelsCount + channels.red];
                pixels[y][x].green = rowWithAllChannels[x * channelsCount + channels.green];
                pixels[y][x].blue = rowWithAllChannels[x * channelsCount + channels.blue];
                
                minPixelValue = getMinPixelValue(minPixelValue, pixels[y][x]);
                maxPixelValue = getMaxPixelValue(maxPixelValue, pixels[y][x]);
            }
        }
        
        delete[] rowWithAllChannels;
       
        tiff.close();
    }
    
    isGrayscale = false;
}

Pixel16bit TIFF::getPixel(int x, int y)
{
    return pixels[y][x];
}

uint32_t * TIFF::getStripOffsets()
{
    return stripOffsets;
}

std::string TIFF::getFilePath()
{
    return filePath;
}

TIFF::~TIFF()
{
    for(int y = 0; y < height; y++)
    {
        delete[] pixels[y];
    }
    delete[] pixels;
}
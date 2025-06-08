#include <fstream>
#include <iostream>

#include "../include/tiff.h"

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

void TIFF::loadChannel(std::string loadFilePath, int channelNumber)
{
    int offsetToChannelPixels = width * channelNumber;

    std::ifstream tiff;
    tiff.open(loadFilePath, std::ios::binary);
    
    if(tiff.is_open())
    {
        pixels = new uint16_t *[height];
        uint16_t * rowWithAllChannels = new uint16_t[width * channelsCount];
        
        for(int y = 0; y < height; y++)
        {
            pixels[y] = new uint16_t[width];
            
            tiff.seekg(stripOffsets[y], std::ios::beg);
            tiff.read((char *)rowWithAllChannels, width * channelsCount * (bitsPerSample / 8)); 
            
            for(int x = 0; x < width; x++)
            {
                pixels[y][x] = rowWithAllChannels[x + offsetToChannelPixels];
            }
        }
        
        delete[] rowWithAllChannels;
       
        tiff.close();
        
        normalizePixelValues();
    }
}

uint16_t minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX)
{
    /* 
    Формула minMax-нормализации в диапазоне [a; b]:
    x' = (x - min(x)) * (b - a) / (max(x) - min(x)) + a
    */
    return ((x - minX) * 255) / (maxX - minX);
}

void TIFF::normalizePixelValues()
{
    uint16_t minPixelValue = 0;
    uint16_t maxPixelValue = 0;
    
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(pixels[y][x] > maxPixelValue)
                maxPixelValue = pixels[y][x];
                
            if(pixels[y][x] < minPixelValue)
                minPixelValue = pixels[y][x];
        }
    }
    
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            pixels[y][x] = minMaxNormalization(pixels[y][x], minPixelValue, maxPixelValue);
        }
    }
}

TIFF::~TIFF()
{
    for(int y = 0; y < height; y++)
    {
        delete[] pixels[y];
    }
    delete[] pixels;
}
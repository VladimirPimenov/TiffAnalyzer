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
        imageData = new Pixel *[height];

        for(int y = 0; y < height; y++)
        {
            imageData[y] = new Pixel[width];
            
            Pixel * rowWithAllChannels = new Pixel[width * channelsCount];
            
            tiff.seekg(stripOffsets[y], std::ios::beg);
            tiff.read((char *)rowWithAllChannels, width * channelsCount * (bitsPerSample / 8)); 
            
            for(int x = 0; x < width; x++)
            {
                imageData[y][x] = rowWithAllChannels[x + offsetToChannelPixels];
            }
        }
       
        tiff.close();
    }
}

TIFF::~TIFF()
{
    for(int y = 0; y < height; y++)
    {
        delete[] imageData[y];
    }
    delete[] imageData;
}
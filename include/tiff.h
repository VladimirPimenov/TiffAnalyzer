#pragma once

#include <string>
#include <vector>

#include "rgb.h"

struct TIFFFILEHEADER
{
    uint16_t byteOrder;
    uint16_t idetificator;
    uint32_t offset;
};

struct Entry
{
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t value;
};

struct IFD
{
    uint16_t entriesCount;
    std::vector<Entry> entries;
};

class TIFF
{   
public:   
    int width;
    int height;
    int channelsCount = 124;
    
    bool isGrayscale;
    
    Pixel16bit ** pixels;
    
    void loadTiffMetadata(std::string loadFilePath);
    
    void loadRgb(std::string loadFilePath, RgbChannels channels);
    void loadGrayscale(std::string loadFilePath, int channel);
    
    ~TIFF();
    
private:
    TIFFFILEHEADER tiffHeader;
    IFD * ifd;
    
    uint32_t * stripOffsets;
    uint32_t rowsPerStrip;
    uint16_t bitsPerSample;
    
    void readIFD(std::ifstream & tiff);
    void readEntry(std::ifstream & tiff);
};
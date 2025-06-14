#pragma once

#include <string>
#include <vector>

#include "rgb.h"

#pragma pack(push, 2)

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

#pragma pack(pop)

class TIFF
{   
public:   
    int width;
    int height;
    int channelsCount = 124;
    
    Pixel16bit ** pixels;
    
    void loadTiffMetadata(std::string loadFilePath);
    void loadGrayscale(std::string loadFilePath, int channelNumber);
    void loadRgb(std::string loadFilePath, RgbChannels channels);
    
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
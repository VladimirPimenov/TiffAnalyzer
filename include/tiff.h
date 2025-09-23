#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <string>

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
    uint16_t bitsPerSample;
    
    uint16_t minPixelValue;
    uint16_t maxPixelValue;
    
    bool isGrayscale;
    
    void loadTiffMetadata(std::string loadFilePath);
    
    void loadRgb(std::string loadFilePath, RgbChannels channels);
    void loadGrayscale(std::string loadFilePath, int channel);
    
    Pixel16bit getPixel(int x, int y);
    
    uint32_t * getStripOffsets();
    std::string getFilePath();
    
    ~TIFF();
    
private:
    TIFFFILEHEADER tiffHeader;
    IFD * ifd;
    
    uint32_t * stripOffsets;
    uint32_t rowsPerStrip;
    
    Pixel16bit ** pixels;
    
    std::string filePath;
    
    void readIFD(std::ifstream & tiff);
    void readEntry(std::ifstream & tiff);
};
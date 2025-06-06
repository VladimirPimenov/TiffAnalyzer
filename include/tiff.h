#include <string>
#include <vector>

#pragma pack(push, 2)

struct Pixel
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

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
    
    Pixel ** imageData;
    
    void loadTiffMetadata(std::string loadFilePath);
    void loadChannel(std::string loadFilePath, int channelNumber);
    
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
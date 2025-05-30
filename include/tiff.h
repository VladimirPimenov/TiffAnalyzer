#include <string>
#include <vector>

#pragma pack(push, 2)

struct Pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
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
    uint32_t nextIFDoffset;
};

#pragma pack(pop)

class TIFF
{
public:
    TIFFFILEHEADER tiffHeader;
    IFD * ifd;
    
public:   
    int width;
    int height;
    int channelsCount = 0;
    
    void loadTiffMetadata(std::string loadFilePath);
};
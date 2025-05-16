#include <string>

#pragma pack(push, 2)

struct TIFFFILEHEADER
{
    unsigned char byteOrder[2];
    unsigned short indetificator;
    unsigned int offset;
};

#pragma pack(pop)

class TIFF
{
public:
    TIFFFILEHEADER tiffHeader;
    
    void load(std::string loadFilePath);
};
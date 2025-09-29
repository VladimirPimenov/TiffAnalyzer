#pragma once

#include <string>
#include <fstream>

#include "rgb.h"

#pragma pack(push, 2)

struct BMPFILEHEADER
{
	uint16_t type;
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t offset;
};
struct BMPINFOHEADER
{
	uint32_t headerSize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitsPerPixel;
};
#pragma pack(pop)

class BMP
{
public:
	BMPFILEHEADER bmpHeader;
	BMPINFOHEADER bmpInfo;
	
	int nullBytesCount;
	uint8_t nullByte = 0;

	Pixel8bit ** pixels;

	void save(std::string saveFilePath);
	
	~BMP();
};


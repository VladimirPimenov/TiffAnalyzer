#include "../../include/bmp.h"

void Bmp::save(std::string saveFilePath)
{
	std::ofstream saveFile(saveFilePath, std::ios::binary);
	
	if(saveFile.is_open())
	{
		saveFile.write((char *)(&bmpHeader), sizeof(BmpFileHeader));
		saveFile.write((char *)(&bmpInfo), sizeof(BmpInfoHeader));
		saveFile.seekp(bmpHeader.offset, std::ios::beg);
		
		Pixel8bit pixel;
		
		for(int row = bmpInfo.height - 1; row >= 0 ; row--) // в bmp строки хранятся снизу вверх
		{
			for(uint32_t col = 0; col < bmpInfo.width; col++)
			{
				pixel = pixels[row][col];
				
				// в bmp пиксели хранятся в BGR
				saveFile.write((char *)&pixel.blue, sizeof(Pixel8bit) / 3);
				saveFile.write((char *)&pixel.green, sizeof(Pixel8bit) / 3);
				saveFile.write((char *)&pixel.red, sizeof(Pixel8bit) / 3);
			}
			
			for(int nullByteNum = 0; nullByteNum < nullBytesCount; nullByteNum++)
			{
				saveFile.write((char *)&nullByte,std::ios::cur);
			}
		}
		saveFile.close();
	}
}

Bmp::~Bmp()
{
	for(uint32_t i = 0; i < bmpInfo.height; i++)
	{
		delete[] pixels[i];
	}
	delete[] pixels;
}
#include <fstream>

#include "../include/tiff.h"

void TIFF::load(std::string loadFilePath)
{
    std::ifstream tiff(loadFilePath, std::ios::binary);
    
    if(tiff.is_open())
    {
        tiff.read((char *)(&tiffHeader), sizeof(TIFFFILEHEADER));
    
        tiff.close();
    }
}
#include <fstream>
#include <iostream>

#include "../include/tiff.h"

void readIFD(IFD * ifd, std::ifstream & file);

void TIFF::loadTiffMetadata(std::string loadFilePath)
{
    std::ifstream tiff;
    tiff.open(loadFilePath, std::ios::binary);
    
    if(tiff.is_open())
    {
        tiff.read((char *)(&tiffHeader), sizeof(TIFFFILEHEADER));
        tiff.seekg(tiffHeader.offset, std::ios::beg);
        
        IFD * ifd = new IFD();
        readIFD(ifd, tiff);
        this->ifd = ifd;
        
        tiff.close();
    }
}

void readIFD(IFD * ifd, std::ifstream & file)
{
    file.read((char *)(&ifd->entriesCount), sizeof(ifd->entriesCount));
            
    for(uint16_t entryNum = 0; entryNum < ifd->entriesCount; entryNum++)
    {
        Entry entry;
        file.read((char *)(&entry), sizeof(Entry));
        
        ifd->entries.push_back(entry);
    }
}
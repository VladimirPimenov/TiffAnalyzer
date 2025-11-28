#pragma once

#include <string>
#include <map>
#include <fstream>

#include "xmlTagReader.h"

class SppTableReader
{
public:
    static void readSppData(std::string filePath, std::map<int, std::map<std::string, float>> & sppData);
    
private:
    static void readWaveLenBlock(std::ifstream & sppFile, std::map<int, std::map<std::string, float>> & sppData);
};
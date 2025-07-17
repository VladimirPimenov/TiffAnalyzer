#pragma once

#include <string>
#include <map>
#include <fstream>

class SppReader
{
public:
    static void readSppData(std::string filePath, std::map<int, std::map<std::string, float>> & sppData);
    
private:
    static void readWaveLenBlock(std::ifstream & sppFile, std::map<int, std::map<std::string, float>> & sppData);
    
    static std::string readTag(std::string line);
    static float readTagValue(std::string line);
};
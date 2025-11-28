#include "../../include/sppTableReader.h"

void SppTableReader::readSppData(std::string filePath, std::map<int, std::map<std::string, float>> & sppData)
{
    std::ifstream spp;
    spp.open(filePath, std::ios::binary);
    
    if(spp.is_open())
    {
        std::string line;
        
        while(std::getline(spp, line))
        {
            if(line.find("<WaveLength>") != -1)
                readWaveLenBlock(spp, sppData);
        }        
    
        spp.close();
    }
}

void SppTableReader::readWaveLenBlock(std::ifstream & sppFile, std::map<int, std::map<std::string, float>> & sppData)
{
    std::string line;
    
    int channelNum = 0;
    std::map<std::string, float> block;
    
    std::string tag;
    float tagValue;
    
    std::getline(sppFile, line);
    
    while(line.find("</WaveLength>") == -1)
    {
        tag = readTag(line);
        tagValue = readTagValue(line);
        
        if(tag == "ChannelNumber")
            channelNum = (int)tagValue;
        else
            block[tag] = tagValue;
        
        std::getline(sppFile, line);
    }
    
    sppData[channelNum] = block;
    block.clear();
}

std::string SppTableReader::readTag(std::string line)
{
    std::string tag = "";
    
    bool isTagReading = false;

    for(char symb : line)
    { 
        if(symb == '>')
            break;
            
        if(isTagReading)
            tag += symb;
          
        if(symb == '<')
            isTagReading = true;
        
    }
    return tag;
}

float SppTableReader::readTagValue(std::string line)
{
    float tagValue = 0.0f;
    
    std::string tagValueString = "";
    bool isValueReading = false;
    
    for(char symb : line)
    {
        if(symb == '/')
            break;
        
        if(isValueReading)
            tagValueString += symb;
        
        if(symb == '>')
            isValueReading = true;
    }
    
    tagValueString = tagValueString.substr(0, tagValueString.length() - 1);
    
    tagValue = std::stof(tagValueString);
    
    return tagValue;
}
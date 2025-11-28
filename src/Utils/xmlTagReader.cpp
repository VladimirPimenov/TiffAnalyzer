#include "../../include/xmlTagReader.h"

std::string XmlTagReader::readTag(std::string line)
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

std::string XmlTagReader::readTagValue(std::string line)
{    
    std::string tagValue = "";
    bool isValueReading = false;
    
    for(char symb : line)
    {
        if(symb == '/')
            break;
        
        if(isValueReading)
            tagValue += symb;
        
        if(symb == '>')
            isValueReading = true;
    }
    
    tagValue = tagValue.substr(0, tagValue.length() - 1);
    
    return tagValue;
}
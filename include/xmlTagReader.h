#pragma once

#include <string>

class XmlTagReader
{
public:
    static std::string readTag(std::string line);
    static std::string readTagValue(std::string line);
};
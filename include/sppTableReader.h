#pragma once

#include <map>

#include <QString>
#include <QFile>
#include <QXmlStreamReader>

class SppTableReader
{
public:
    static void readSppData(QString filePath, std::map<unsigned, std::map<QString, double>> & sppData);
};
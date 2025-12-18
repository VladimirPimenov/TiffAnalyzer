#pragma once

#include <QString>
#include <QStringList>

#include <QFile>
#include <QXmlStreamReader>

#include <array>

class Kml
{
public:
    std::array<double, 4> latitudes;
    std::array<double, 4> longitudes;

    Kml(QString loadPath);
    
    void loadKml(QString loadPath);
    
private:
    void parseStringToCoordinates(QString string);
};